#ifndef INCOMING_EVENT_HEADER_H
#define INCOMING_EVENT_HEADER_H

#include "EventPattern.h"
#include <vector>

class InEvent : public EventPattern
{
private:
	static std::map<std::string, InEvent*> incoming_events_map;

protected:
	InEvent(std::string id);

public:
	virtual bool get_params(const std::string& event_body,std::vector<std::string>& params) = 0;
	static std::map<std::string, InEvent*>& get_incoming_events();

};


#endif
