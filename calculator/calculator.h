#pragma once

#include <sstream>
#include <string>
#include <cstring>
#include <stack>
#include <cmath>
#include <stdexcept>
#include <algorithm>

class Calculator
{
private:
    std::string infix; 
    std::string postfix;

    std::stack<char> OpStack;
    std::stack<double> NumStack;

    int Priority(const char op);
    double MakeCount(const double x1, const double x2, const char op);
    void ValidateExpression();
    void ToPostfix();

public:
    Calculator(const std::string& _infix);
    double Calculate();
};