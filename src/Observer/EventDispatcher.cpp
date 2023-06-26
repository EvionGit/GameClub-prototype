#include "Observer/EventDispatcher.h"



void EventDispatcher::call(const Event& ev)
{
	std::vector<std::shared_ptr<SubscriberBase>> subs_vec = subs[ev.id];
	for (auto it = subs_vec.begin(); it != subs_vec.end(); it++)
		it->get()->invoke(ev);

}

