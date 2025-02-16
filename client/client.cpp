#include "../httplib/httplib.h"
#include "clientfunc.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <map>
#include <stdexcept>

using namespace std::chrono_literals;

int main() {
    const std::map<std::string, std::string> commands = {
        {"-c", "echo"},
        {"-e", "calculate"}
    };

    std::cout << "Welcome to the Calculator Client!\n";
    std::cout << "Available commands:\n";
    std::cout << "  -c <word>   — Echo back the word\n";
    std::cout << "  -e <expr>   — Evaluate expression (e.g., \"2 + 2\")\n";
    std::cout << "  exit        — Exit the client\n\n";

    while(true) {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        if(input.empty()) continue;

        if(input == "exit") {
            std::cout << "Goodbye!\n";
            return 0;
        }

        size_t space_pos = input.find(' ');
        if(space_pos == std::string::npos || space_pos == 0) {
            std::cerr << "Invalid command format. Use: <command> <argument>\n";
            continue;
        }

        std::string cmd = input.substr(0, space_pos);
        std::string arg = input.substr(space_pos + 1);

        if(!commands.count(cmd)) {
            std::cerr << "Unknown command: " << cmd << "\n";
            continue;
        }

        const int max_attempts = 3;
        const int delays[] = {0, 5, 10}; 
        bool success = false;

        for(int attempt = 0; attempt < max_attempts && !success; ++attempt) {
            if(attempt > 0) {
                attempt_reconnect(delays[attempt]);
            }

            httplib::Client client("http://localhost:8080");
            client.set_connection_timeout(3); 
            client.set_read_timeout(5);       

            std::cout << "Attempt " << (attempt + 1) << "/" << max_attempts << "...\n";
            success = try_connect(client, input);

            if(success) break;

            if(attempt == max_attempts - 1) {
                std::cerr << "\nServer is unavailable after " << max_attempts 
                         << " attempts. Please try again later.\n";
                return 1;
            }
        }
    }

    return 0;
}