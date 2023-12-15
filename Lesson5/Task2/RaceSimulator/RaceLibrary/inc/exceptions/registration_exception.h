#pragma once

#include <string>
#include <stdexcept>

namespace simulator_exceptions
{
	class RegistrationException : public std::domain_error
	{
	public:
		RegistrationException(std::string message) : std::domain_error(message) {}
	};
}