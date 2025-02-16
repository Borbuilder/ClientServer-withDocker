#pragma once

#include "../httplib/httplib.h"
#include "../calculator/calculator.h"

#include <string>
#include <stdexcept>

void handle_request(const httplib::Request &req, httplib::Response &res);