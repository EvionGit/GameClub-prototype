#ifndef EVENT_PATTERN_BASE_HEADER_H
#define EVENT_PATTERN_BASE_HEADER_H

#include <map>
#include <string>


class EventPattern
{
private:
	static std::map<std::string, EventPattern*> events_map;

protected:
	std::string id;

protected:
	EventPattern(std::string id);

public:
	static std::map<std::string, EventPattern*>& get_events();
	std::string get_id();


};


#endif