#ifndef INPUT_FILE_PARSER_HEADER_H
#define INPUT_FILE_PARSER_HEADER_H

#include "InputParser.h"
#include <fstream>

class FileParser : public InputParser
{
private:
	std::ifstream file_log;

public:
	FileParser(std::string file_name);

	virtual bool get_line(std::string& line) override;
};

#endif