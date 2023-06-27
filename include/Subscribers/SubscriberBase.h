#ifndef EVENT_SUBSCRIBER_BASE_HEADER_H
#define EVENT_SUBSCRIBER_BASE_HEADER_H

#include <string>
#include "../Events/Event.h"

class SubscriberBase
{
protected:
	SubscriberBase();

public:
	virtual void invoke(const Event& ev);
};

#endif
