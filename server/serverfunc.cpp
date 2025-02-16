#include "serverfunc.h"

void handle_request(const httplib::Request &req, httplib::Response &res)
{
    std::string command = req.body;
    try {
        if (command.rfind("-c ", 0) == 0) { 
            std::string word = command.substr(3);
            res.set_content(word, "text/plain");
        } 
        else if (command.rfind("-e ", 0) == 0) { 
            std::string input_expr = command.substr(3);

            Calculator expr(input_expr);
            double result = expr.Calculate();

            res.set_content(std::to_string(result), "text/plain");
        } 
        else {
            throw std::runtime_error("Invalid command");
        }
    } catch (const std::exception &e) {
        res.status = 400;
        res.set_content(e.what(), "text/plain");
    }
}