#ifndef OUTCOMING_EVENT_BODY_USER_TABLE_HEADER_H
#define OUTCOMING_EVENT_BODY_USER_TABLE_HEADER_H

#include "OutcomingEvent.h"


class OutEventBodyUserTable : public OutEvent
{
public:
	OutEventBodyUserTable(std::string id) : OutEvent(id) {};

};

#endif
