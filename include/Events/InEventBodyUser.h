#ifndef INCOMING_EVENT_BODY_USER_HEADER_H
#define INCOMING_EVENT_BODY_USER_HEADER_H

#include "IncomingEvent.h"
#include <regex>

class InEventBodyUser : public InEvent
{
public:
	InEventBodyUser(std::string id);

	virtual bool get_params(const std::string& event_body, std::vector<std::string>& params) override;
};

#endif

