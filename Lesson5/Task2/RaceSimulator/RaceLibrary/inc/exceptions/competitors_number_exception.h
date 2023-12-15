#pragma once

#include <string>
#include <stdexcept>

namespace simulator_exceptions
{
	class CompetitiorsNumberException : public std::domain_error
	{
	public:
		CompetitiorsNumberException(
			std::string message="It is impossible to start the race with less than 2 competitors!"
		) : std::domain_error(message) {}
	};
}