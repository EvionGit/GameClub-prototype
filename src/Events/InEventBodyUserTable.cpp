#include "Events/InEventBodyUserTable.h"


InEventBodyUserTable::InEventBodyUserTable(std::string id, uint32_t tables_count)
	: InEvent(id), tables_count(tables_count) {}


bool InEventBodyUserTable::get_params(const std::string& event_body, std::vector<std::string>& params)
{
	std::regex user_x_table_regex("([0-9a-z_\\-]+)\\s([1-9]\\d*)");
	std::cmatch result;

	if (!std::regex_match(event_body.c_str(), result, user_x_table_regex))
	{
		return false;
	}

	for (int i = 1; i < result.size(); i++)
		params.push_back(result[i]);

	if (std::strtoul(result[2].str().c_str(), 0, 0) > tables_count)
		return false;

	return true;

};