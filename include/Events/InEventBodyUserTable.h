#ifndef INCOMING_EVENT_BODY_USER_TABLE_HEADER_H
#define INCOMING_EVENT_BODY_USER_TABLE_HEADER_H

#include "IncomingEvent.h"
#include <regex>

class InEventBodyUserTable : public InEvent
{
private:
	uint32_t tables_count;

public:
	InEventBodyUserTable(std::string id, uint32_t tables_count);

	virtual bool get_params(const std::string& event_body, std::vector<std::string>& params) override;
};


#endif 

