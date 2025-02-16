#include "calculator.h"

int Calculator::Priority(const char op)
{
    switch(op)
    {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        case '(':
        case ')': return 0;
        default: 
            throw std::runtime_error("Invalid operator: " + std::string(1, op));
    }
}

double Calculator::MakeCount(double x1, double x2, char op)
{
    switch(op)
    {
        case '+': return x1 + x2;
        case '-': return x1 - x2;
        case '*': return x1 * x2;
        case '/': 
            if(x2 == 0) throw std::runtime_error("Division by zero");
            return x1 / x2;
        case '^': return pow(x1, x2);
        default: 
            throw std::runtime_error("Unknown operator: " + std::string(1, op));
    }
}

void Calculator::ValidateExpression()
{
    int bracketBalance = 0;
    for(char c : infix)
    {
        if(c == '(') bracketBalance++;
        if(c == ')') bracketBalance--;
        if(bracketBalance < 0)
            throw std::runtime_error("Mismatched parentheses");
        
        if(!isdigit(c) && !strchr("+-*/^() .", c))
            throw std::runtime_error("Invalid character: " + std::string(1, c));
    }
    if(bracketBalance != 0)
        throw std::runtime_error("Mismatched parentheses");
}

void Calculator::ToPostfix()
{
    std::string str = "(" + infix + ")";
    postfix.clear();

    for(size_t i = 0; i < str.size(); ++i)
    {
        if(str[i] == ' ') continue;

        if(isdigit(str[i]) || str[i] == '.')
        {
            while(isdigit(str[i]) || str[i] == '.' || str[i] == 'e' || str[i] == 'E')
                postfix += str[i++];
            postfix += ' ';
            --i;
            continue;
        }

        if(str[i] == '(')
        {
            OpStack.push('(');
        }
        else if(str[i] == ')')
        {
            while(!OpStack.empty() && OpStack.top() != '(')
            {
                postfix += OpStack.top();
                postfix += ' ';
                OpStack.pop();
            }
            OpStack.pop(); 
        }
        else if(strchr("+-*/^", str[i]))
        {
            while(!OpStack.empty() && Priority(OpStack.top()) >= Priority(str[i]))
            {
                postfix += OpStack.top();
                postfix += ' ';
                OpStack.pop();
            }
            OpStack.push(str[i]);
        }
        else
        {
            throw std::runtime_error("Invalid character: " + std::string(1, str[i]));
        }
    }
}

Calculator::Calculator(const std::string& _infix) : infix(_infix)
{
    infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
    
    ValidateExpression();
    ToPostfix();
}

double Calculator::Calculate()
{
    std::istringstream iss(postfix);
    std::string token;
    
    while(iss >> token)
    {
        if(isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1])))
        {
            NumStack.push(std::stod(token));
            continue;
        }

        if(NumStack.size() < 2)
            throw std::runtime_error("Not enough operands for operator " + token);

        double x2 = NumStack.top();
        NumStack.pop();
        double x1 = NumStack.top();
        NumStack.pop();

        NumStack.push(MakeCount(x1, x2, token[0]));
    }

    if(NumStack.size() != 1)
        throw std::runtime_error("Invalid expression structure");

    double result = NumStack.top();
    NumStack.pop();
    return result;
}