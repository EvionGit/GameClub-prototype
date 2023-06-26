#ifndef OUTCOMING_EVENT_BODY_ERROR_HEADER_H
#define OUTCOMING_EVENT_BODY_ERROR_HEADER_H

#include "OutcomingEvent.h"


class OutEventBodyError : public OutEvent
{
public:
	OutEventBodyError(std::string id) : OutEvent(id) {};

};

#endif
