#include "Base.h"


uint32_t to_minutes(std::string hhmm)
{
	uint32_t h = hhmm[0] == '0' ? std::strtoul(hhmm.substr(1, 1).c_str(), 0, 0) : std::strtoul(hhmm.substr(0, 2).c_str(), 0, 0);
	uint32_t m = std::strtoul(hhmm.substr(3, 2).c_str(), 0, 0);
	return h * 60 + m;
}

std::string to_hhmm(uint32_t time)
{
	uint32_t h = time / 60;
	uint32_t m = time - h * 60;

	std::string hh = h < 10 ? "0" + std::to_string(h) : std::to_string(h);
	std::string mm = m < 10 ? "0" + std::to_string(m) : std::to_string(m);

	return hh + ":" + mm;
}

void printer(std::string str)
{
	printf("%s\n",str.c_str());
}