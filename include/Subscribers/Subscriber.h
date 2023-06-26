#ifndef SUBSCRIBER_UNIT_HEADER_H
#define SUBSCRIBER_UNIT_HEADER_H

#include "SubscriberBase.h"
#include "Events/Event.h"


template <class T>
class Subscriber : public SubscriberBase
{
public:
	std::string ev_id;
	T* obj;
	void (T::* handler)(const Event& ev);

	Subscriber(std::string ev_id, T* obj, void(T::* handler)(const Event& ev))
	{
		this->ev_id = ev_id;
		this->obj = obj;
		this->handler = handler;
	}


	virtual void invoke(const Event& ev) override { (this->obj->*handler)(ev); }



};






#endif