#include "Analyzers/ClubAnalyzer.h"
#include "Events/IncomingEvent.h"
#include "Base.h"
#include <regex>
#include <map>

ClubAnalyzer::ClubAnalyzer(InputParser& parser, InEvent& open, InEvent& close) : Analyzer(parser),
open_ev(open), close_ev(close)											
{
	this->tables_amount = 0;
	this->start_time = 0;
	this->end_time = 0;
	this->price = 0;
}

bool ClubAnalyzer::parse_config()
{
	
	std::string line;
	std::cmatch result;


	/* string representation of REGEX patterns */
	std::string num_pattern = "([1-9]\\d*)";
	std::string time_pattern = "([0-1]\\d:[0-5]\\d|[2][0-3]:[0-5]\\d)";

	/* REGEX-obj */
	std::regex num_regex(num_pattern);
	std::regex time_regex(time_pattern + "\\s" + time_pattern);


	parser.get_line(line);
	if (!std::regex_match(line.c_str(), result, num_regex))
	{
		printf("%s\n", line.c_str());
		return false;
	}
	this->tables_amount = std::strtoul(result[1].str().c_str(), 0, 0);


	parser.get_line(line);
	if (!std::regex_match(line.c_str(), result, time_regex))
	{
		printf("%s\n", line.c_str());
		return false;
	}
	this->start_time = to_minutes(result[1].str());
	this->end_time = to_minutes(result[2].str());


	parser.get_line(line);
	if (!std::regex_match(line.c_str(), result, num_regex))
	{
		printf("%s\n", line.c_str());
		return false;
	}
	this->price = std::strtoul(result[1].str().c_str(), 0, 0);

	return true;
}

bool ClubAnalyzer::analyze()
{

	if (!tables_amount)
		return false;

	/* string representation of REGEX patterns */
	std::string num_pattern = "([1-9]\\d*)";
	std::string time_pattern = "([0-1]\\d:[0-5]\\d|[2][0-3]:[0-5]\\d)";
	std::string event_body_pattern = "(.+)";

	/* REGEX-obj */
	std::regex num_regex(num_pattern);
	std::regex time_regex(time_pattern + "\\s" + time_pattern);
	std::regex event_regex(time_pattern + "\\s" + num_pattern + "\\s" + event_body_pattern);

	std::string line;
	std::cmatch result;
	uint32_t last_timestamp = 0;


	/* get all defined InEvents */
	std::map<std::string, InEvent*> event_map = InEvent::get_incoming_events();

	/* OPEN event */
	event_q.push(Event(open_ev.get_id(), to_hhmm(start_time), std::move(std::vector<std::string>())));
	
	while (parser.get_line(line)) 
	{
		if (!std::regex_match(line.c_str(), result, event_regex))
		{
			printf("%s\n", line.c_str());
			return false;
		}

		std::string e_time = result[1];
		std::string e_id = result[2];
		std::string e_body = result[3];
		

		/* check definition for event ID */
		auto it = event_map.begin();
		if ((it = event_map.find(e_id)) == event_map.end())
		{
			printf("%s", line.c_str());
			return false;
		}

		/* check and split BODY-params */
		std::vector<std::string> event_params;
		if (!it->second->get_params(e_body, event_params))
		{
			printf("%s\n", line.c_str());
			return false;
		}

		/* create Event obj */
		Event e(e_id, e_time, std::move(event_params));

		/* check timestamps*/
		uint32_t e_time_minuntes = to_minutes(e.hhmm);
		if (last_timestamp > e_time_minuntes)
		{
			printf("%s\n", line.c_str());
			return false;
		}


		last_timestamp = e_time_minuntes;
		event_q.push(e);

	}

	/* CLOSE event */
	event_q.push(Event(close_ev.get_id(), to_hhmm(end_time), std::move(std::vector<std::string>())));
}

void ClubAnalyzer::get_config(uint32_t& tab_count, uint32_t& start_t, uint32_t& end_t, uint32_t& price)
{
	if (!tables_amount)
		this->parse_config();

	tab_count = this->tables_amount;
	start_t = this->start_time;
	end_t = this->end_time;
	price = this->price;
}

std::queue<Event>&& ClubAnalyzer::get_event_queue()
{
	return std::move(event_q);
}