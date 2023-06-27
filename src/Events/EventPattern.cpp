#include "../../include/Events/EventPattern.h"


std::map<std::string, EventPattern*> EventPattern::events_map;

EventPattern::EventPattern(std::string id) :id(id)
{
	EventPattern::events_map[id] = this;
}

std::map<std::string, EventPattern*>& EventPattern::get_events()
{ 
	return EventPattern::events_map;
}

std::string EventPattern::get_id()
{
	return this->id;
}
