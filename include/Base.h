#ifndef BASE_DEFINITION_FUNC_HEADER_H
#define BASE_DEFINITION_FUNC_HEADER_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>



uint32_t to_minutes(std::string hhmm);
std::string to_hhmm(uint32_t time);

void printer(std::string str);


#endif