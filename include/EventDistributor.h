#ifndef EVENT_DISTRIBUTOR_OBSERVER_HEADER_H
#define EVENT_DISTRIBUTOR_OBSERVER_HEADER_H

#include "Observer/EventDispatcher.h"
#include <queue>


class EventDistributor : public EventDispatcher
{
private:
	std::queue<Event>& event_queue;

public:
	EventDistributor(std::queue<Event>& event_q);
	void call_events();
};

#endif 
