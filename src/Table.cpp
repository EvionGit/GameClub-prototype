#include "../include/Table.h"
#include <cmath>

Table::Table(uint32_t price) : profit(0),total_time(0),placement_time(0),is_taken(false)
{
	this->price = price;
}

bool Table::take(uint32_t time)
{
	if (is_taken)
		return false;

	placement_time = time;
	is_taken = true;
	return true;
}

bool Table::leave(uint32_t time)
{
	if (!is_taken)
		return false;

	uint32_t bill = static_cast<uint32_t>(std::ceil(static_cast<float>(time - placement_time) / 60));
	profit += bill * price;
	total_time += time - placement_time;

	is_taken = false;
	return true;
}
uint64_t Table::get_profit()
{
	return profit;
}

uint32_t Table::get_total_time()
{
	return total_time;
}
