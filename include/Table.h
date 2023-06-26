#ifndef CLUB_TABLE_HEADER_H
#define CLUB_TABLE_HEADER_H

#include <stdint.h>

class Table
{
private:
	uint64_t profit;
	uint32_t total_time;

	uint32_t price;
	uint32_t placement_time;
	bool is_taken;

public:
	Table(uint32_t price);
	bool take(uint32_t time);
	bool leave(uint32_t time);
	uint64_t get_profit();
	uint32_t get_total_time();
};

#endif