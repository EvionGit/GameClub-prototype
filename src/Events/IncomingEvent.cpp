#include "../../include/Events/IncomingEvent.h"

std::map<std::string, InEvent*> InEvent::incoming_events_map;

InEvent::InEvent(std::string id) :EventPattern(id)
{
	InEvent::incoming_events_map[id] = this;
}

std::map<std::string, InEvent*>& InEvent::get_incoming_events()
{ 
	return InEvent::incoming_events_map;
}
