#include "../../include/Events/OutcomingEvent.h"

std::map<std::string, OutEvent*> OutEvent::outcoming_events_map;

OutEvent::OutEvent(std::string id) :EventPattern(id)
{
	OutEvent::outcoming_events_map[id] = this;
}

std::map<std::string, OutEvent*>& OutEvent::get_outcoming_events()
{ 
	return OutEvent::outcoming_events_map;
}
