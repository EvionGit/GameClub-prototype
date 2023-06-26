#include "Events/Event.h"


Event::Event(std::string id, std::string hhmm, std::vector<std::string>&& body)
{
	this->id = id;
	this->hhmm = hhmm;
	this->body = body;
	
}