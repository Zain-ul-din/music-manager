#pragma once

#include <functional>
#include <vector>

template <
	class RETURN_TYPE,
	class... PARAMS
>
class Event
{
public:
	void operator += (std::function<RETURN_TYPE(PARAMS...)>);
	void invoke(PARAMS&...);
private:
	std::vector <std::function<RETURN_TYPE(PARAMS...)>>  events;
};

template <
	class RETURN_TYPE,
	class... PARAMS
>
void Event<RETURN_TYPE, PARAMS...>::invoke(PARAMS&... params)
{
	if (events.empty())	return;
	for (auto e : events)	e(params...);
}

template <
	class RETURN_TYPE,
	class... PARAMS
>
void Event<RETURN_TYPE, PARAMS...>::operator += (std::function<RETURN_TYPE(PARAMS...)> func)
{	events.push_back(func);	}



