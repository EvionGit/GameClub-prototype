#ifndef BASE_INPUT_PARSER_HEADER_H
#define BASE_INPUT_PARSER_HEADER_H

#include <string>

class InputParser
{
public:
	virtual bool get_line(std::string& line) = 0;
};

#endif
