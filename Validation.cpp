#include "header.h"

using std::string;

bool isNumber(string str) 
{
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c) || c == '.';
    });
}

float getUserInput(string prompt)
{
    try {
        std::cout << prompt;
        string inputStr {};
        std::cin >> inputStr;

        if (!isNumber(inputStr)) {
            throw std::invalid_argument("Not a number. ");
        }

        float input = std::stof(inputStr);
        return input;

    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return 0;
}