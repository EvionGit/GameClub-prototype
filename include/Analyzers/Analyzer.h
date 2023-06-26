#ifndef BASE_ANALYZER_HEADER_H
#define BASE_ANALYZER_HEADER_H

#include "InputParsers/InputParser.h"

class Analyzer
{
protected:
	InputParser& parser;

protected:
	Analyzer(InputParser& parser);

public:
	virtual bool analyze() = 0;
};

#endif