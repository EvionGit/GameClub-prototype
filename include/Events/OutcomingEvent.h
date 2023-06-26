#ifndef OUTCOMING_EVENT_HEADER_H
#define OUTCOMING_EVENT_HEADER_H

#include "EventPattern.h"

class OutEvent : public EventPattern
{
private:
	static std::map<std::string, OutEvent*> outcoming_events_map;

protected:
	OutEvent(std::string id);

public:
	static std::map<std::string, OutEvent*>& get_outcoming_events();

};



#endif