#include "InputParsers/FileParser.h"

FileParser::FileParser(std::string file_name)
{
	file_log.open(file_name);

}

bool FileParser::get_line(std::string& line)
{
	if (!file_log.is_open())
		return false;

	if (!std::getline(file_log, line))
		return false;

	return true;
}