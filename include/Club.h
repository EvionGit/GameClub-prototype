#ifndef CLUB_HANDLER_HEADER_H
#define CLUB_HANDLER_HEADER_H

#include "Base.h"
#include "Subscribers/SubscriberBase.h"
#include "Observer/EventDispatcher.h"
#include "Table.h"

#include <deque>
#include <map>
#include <set>
#include <string>

class Club : protected SubscriberBase, public EventDispatcher
{
private:
	uint32_t places;
	uint32_t time_start;
	uint32_t time_stop;
	uint32_t price;

	bool is_kicked;

	std::vector<std::shared_ptr<Table>> tables;
	
	std::set<std::string> clients;
	std::map<std::string, uint32_t> client_x_table;
	std::deque<std::string> client_q;

public:
	Club(uint32_t places, uint32_t time_start, uint32_t time_stop, uint32_t price);
	

	/* ID 0 handler */
	void close_club_handler(const Event& ev);

	/* ID 100 handler */
	void open_club_handler(const Event& ev);

	/* ID 1 handler */
	void client_came_handler(const Event& ev);

	/* ID 2 handler */
	void client_sat_handler(const Event& ev);

	/* ID 3 handler */
	void client_waiting_handler(const Event& ev);

	/* ID 4 handler */
	void client_left_handler(const Event& ev);


	/* ID 11 handler */
	void client_must_leave_handler(const Event& ev);

	/* ID 12 handler */
	void client_must_sit_down_handler(const Event& ev);

	/* ID 13 handler */
	void error_handler(const Event& ev);

private:
	void print_event_msg(const Event& ev);
	void get_tables_profit();
	void kick_clients();
	
	
};

#endif 
