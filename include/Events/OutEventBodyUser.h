#ifndef OUTCOMING_EVENT_BODY_USER_HEADER_H
#define OUTCOMING_EVENT_BODY_USER_HEADER_H

#include "OutcomingEvent.h"


class OutEventBodyUser : public OutEvent
{
public:
	OutEventBodyUser(std::string id) : OutEvent(id) {};

};

#endif

