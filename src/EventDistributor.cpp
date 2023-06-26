#include "EventDistributor.h"


EventDistributor::EventDistributor(std::queue<Event>& event_q) : event_queue(event_q)
{}

void EventDistributor::call_events()
{
	while(!event_queue.empty())
	{
		call(event_queue.front());
		event_queue.pop();
	}
}