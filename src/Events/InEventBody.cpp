#include "../../include/Events/InEventBody.h"

InEventBody::InEventBody(std::string id) : InEvent(id) {}

bool InEventBody::get_params(const std::string& event_body, std::vector<std::string>& params)
{
	std::regex user_name_regex("(.*)");
	std::cmatch result;

	if (!std::regex_match(event_body.c_str(), result, user_name_regex))
	{
		return false;
	}

	for (int i = 1; i < result.size(); i++)
		params.push_back(result[i]);

	return true;

};
