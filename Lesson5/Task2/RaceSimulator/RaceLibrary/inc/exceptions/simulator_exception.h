#pragma once

#include <string>
#include <stdexcept>

namespace simulator_exceptions
{
	class SimulatorException : public std::domain_error
	{
	public:
		SimulatorException(std::string message) : std::domain_error(message) {}
	};
}