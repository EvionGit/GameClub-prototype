#ifndef EVENT_DISPATCHER_BASE_HEADER_H
#define EVENT_DISPATCHER_BASE_HEADER_H


#include <vector>
#include <string>
#include <map>
#include "Subscribers/Subscriber.h"
#include "Events/EventPattern.h"
#include "Events/Event.h"
#include <memory>

class EventDispatcher
{
protected:
	std::map<std::string, std::vector<std::shared_ptr<SubscriberBase>>> subs;

public:
	template <typename T>
	void add_sub(EventPattern& event_patt, T* obj, void(T::* handler)(const Event& ev))
	{
		std::string event_id = event_patt.get_id();

		std::shared_ptr<Subscriber<T>> newsub(new Subscriber<T>(event_id, obj, handler));
		subs[event_id].push_back(newsub);

	}

	void call(const Event& ev);


};


#endif 
