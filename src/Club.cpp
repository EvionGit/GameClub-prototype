#include "Club.h"

Club::Club(uint32_t places, uint32_t time_start, uint32_t time_stop, uint32_t price)
{
	this->places = places;
	this->time_start = time_start;
	this->time_stop = time_stop;
	this->price = price;

	this->is_kicked = false;

	tables.reserve(this->places);
	for (uint32_t i = 0; i < places; i++)
		tables.push_back(std::shared_ptr<Table>(new Table(this->price)));


}

void Club::close_club_handler(const Event& ev)
{
	if (!is_kicked)
		kick_clients();

	printer(to_hhmm(time_stop));
	get_tables_profit();

}

void Club::kick_clients()
{
	auto it = clients.begin();
	while ((it = clients.begin()) != clients.end())
		call(Event("11", to_hhmm(time_stop), std::vector<std::string>{*it}));

	is_kicked = true;
}

void Club::open_club_handler(const Event& ev)
{
	printer(to_hhmm(time_start));
}

void Club::client_came_handler(const Event& ev)
{
	if (!is_kicked && to_minutes(ev.hhmm) > time_stop)
		kick_clients();

	print_event_msg(ev);

	const std::string& client_name = ev.body[0];

	if (to_minutes(ev.hhmm) < time_start)
		call(Event("13", ev.hhmm, std::vector<std::string>{"NotOpenYet"}));

	else if (clients.find(client_name) != clients.end())
		call(Event("13", ev.hhmm, std::vector<std::string>{"YouShallNotPass"}));

	else
		clients.insert(client_name);

}

void Club::client_sat_handler(const Event& ev)
{
	if (!is_kicked && to_minutes(ev.hhmm) > time_stop)
		kick_clients();

	print_event_msg(ev);

	const std::string& client_name = ev.body[0];
	const std::string& place = ev.body[1];
	int32_t index_place = atoi(place.c_str()) - 1;


	if (clients.find(client_name) == clients.end())
		call(Event("13", ev.hhmm, std::vector<std::string>{"ClientUnknown"}));

	else if (!tables[index_place]->take(to_minutes(ev.hhmm)))
		call(Event("13", ev.hhmm, std::vector<std::string>{"PlaceIsBusy"}));

	else
		client_x_table[client_name] = index_place;

}

void Club::client_waiting_handler(const Event& ev) 
{
	if (!is_kicked && to_minutes(ev.hhmm) > time_stop)
		kick_clients();

	print_event_msg(ev);

	const std::string& client_name = ev.body[0];

	if (clients.find(client_name) == clients.end())
		call(Event("13", ev.hhmm, std::vector<std::string>{"ClientUnknown"}));

	else if (client_x_table.size() < places)
		call(Event("13", ev.hhmm, std::vector<std::string>{"ICanWaitNoLonger"}));

	else if (client_q.size() >= places)
		call(Event("11", ev.hhmm, std::vector<std::string>{client_name}));

	else
		client_q.push_back(client_name);
}

void Club::client_left_handler(const Event& ev) 
{
	if (!is_kicked && to_minutes(ev.hhmm) > time_stop)
		kick_clients();

	print_event_msg(ev);

	const std::string& client_name = ev.body[0];

	if (clients.find(client_name) == clients.end())
		call(Event("13", ev.hhmm, std::vector<std::string>{"ClientUnknown"}));

	else
	{
		/* if client is sitting at the table */
		if(tables[client_x_table[client_name]]->leave(to_minutes(ev.hhmm)))
		{
			std::string leaving_place = std::to_string(client_x_table[client_name]+1);
			client_x_table.erase(client_name);

			call(Event("12", ev.hhmm, std::vector<std::string>{client_name, leaving_place}));
		}
		
		
		clients.erase(client_name);
	}
}

void Club::client_must_leave_handler(const Event& ev)
{

	print_event_msg(ev);

	const std::string& client_name = ev.body[0];
	
	/* if client sitting at a table*/
	if(client_x_table.find(client_name) != client_x_table.end())
	{
		tables[client_x_table[client_name]]->leave(to_minutes(ev.hhmm));
		client_x_table.erase(client_name);
	}
	else
	{
		/* if client in queue - erase it */
		for (auto it = client_q.begin(); it != client_q.end(); it++)
		{
			if (*it != client_name)
				continue;

			client_q.erase(it);
			break;
		}
	}
	

	/* erase from clients */
	clients.erase(client_name);

}

void Club::client_must_sit_down_handler(const Event& ev)
{
	if (client_q.empty())
		return;

	print_event_msg(ev);

	std::string client_name = client_q.front();
	const std::string& place = ev.body[1];
	int32_t index_place = atoi(place.c_str())-1;

	client_q.pop_front();


	tables[index_place]->take(to_minutes(ev.hhmm));
	client_x_table[client_name] = index_place;

}

void Club::error_handler(const Event& ev)
{
	print_event_msg(ev);
}

void Club::print_event_msg(const Event& ev)
{
	std::string event_str = ev.hhmm + " " + ev.id;
	for (auto it = ev.body.begin(); it != ev.body.end(); it++)
		event_str += " " + *it;

	printer(event_str);
}

void Club::get_tables_profit()
{
	for(uint32_t i = 0; i < places; i++)
	{
		std::string profit = std::move(std::to_string(tables[i]->get_profit()));
		std::string total_time = std::move(to_hhmm(tables[i]->get_total_time()));
		
		printer(std::to_string(i + 1) + " " + profit + " " + total_time);
	}
}