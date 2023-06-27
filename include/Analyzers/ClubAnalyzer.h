#ifndef CLUB_ANALYZER_HEADER_H
#define CLUB_ANALYZER_HEADER_H

#include "Analyzer.h"
#include "../Events/Event.h"
#include "../Events/IncomingEvent.h"
#include <queue>

class ClubAnalyzer : public Analyzer
{
private:
	std::queue<Event> event_q;
	uint32_t tables_amount;
	uint32_t start_time;
	uint32_t end_time;
	uint32_t price;

	InEvent& open_ev;
	InEvent& close_ev;

private:
	bool parse_config();

public:
	ClubAnalyzer(InputParser& parser, InEvent& open, InEvent& close);
	virtual bool analyze() override;

	void get_config(uint32_t& tab_count, uint32_t& start_t, uint32_t& end_t,uint32_t& price);
	std::queue<Event>&& get_event_queue();
};

#endif
