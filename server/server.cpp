#include "../httplib/httplib.h"
#include "serverfunc.h"

#include <iostream>
#include <thread>
#include <atomic>
#include <string>


int main() {
    httplib::Server svr;

    std::atomic<bool> stop_server(false);

    std::cout << "Server is started at http://localhost:8080\n";

    std::thread console_thread([&]() {
        std::cout << "Enter 'STOP' to stop the server: ";

        std::string input;
        while (!stop_server) {
            std::getline(std::cin, input);
            if (input == "STOP") {
                svr.stop();          
                stop_server = true;   
            }
        }
    });

    svr.Post("/command", handle_request);

    svr.listen("0.0.0.0", 8080);
    
    console_thread.join();
    std::cout << "The server is stopped!\n";

    return 0;
}