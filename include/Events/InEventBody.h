#ifndef INCOMING_EVENT_BODY_HEADER_H
#define INCOMING_EVENT_BODY_HEADER_H

#include "IncomingEvent.h"
#include <regex>

class InEventBody : public InEvent
{
public:
	InEventBody(std::string id);

	virtual bool get_params(const std::string& event_body, std::vector<std::string>& params) override;
};

#endif

