#ifndef EVENT_UNIT_HEADER_H
#define EVENT_UNIT_HEADER_H

#include <vector> 
#include <string>

struct Event
{
	
	std::string id;
	std::string hhmm;
	std::vector<std::string> body;

	Event(std::string id, std::string hhmm, std::vector<std::string>&& body);
	
};

#endif