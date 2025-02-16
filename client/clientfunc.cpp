#include "clientfunc.h"

bool try_connect(httplib::Client &client, const std::string &input)
{
    try {
        auto res = client.Post("/command", input, "text/plain");
        
        if (res && res->status == 200) {
            std::cout << "Result: " << res->body << "\n";
            return true;
        }
        
        std::cerr << "Server error: " 
                 << (res ? std::to_string(res->status) + " - " + res->body : "Connection failed") 
                 << "\n";
    } 
    catch (const std::exception& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
    }
    return false;
}

void attempt_reconnect(int delay)
{
    if(delay > 0) {
        std::cout << "Waiting " << delay << " seconds before retry...\n";
        std::this_thread::sleep_for(std::chrono::seconds(delay));
    }
}
