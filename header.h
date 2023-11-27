#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <curl/curl.h>
#include "json.hpp"

bool isNumber(std::string str);
float getUserInput(std::string prompt);

#endif