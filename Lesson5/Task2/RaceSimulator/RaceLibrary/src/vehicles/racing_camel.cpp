#include "racing_camel.h"

namespace vehicles
{
	double RacingCamel::calculateRecoveryTime(double distance) const
	{
		const double first_stop_time = 5;
		const double second_stop_time = 6.5;
		const double other_stops_time = 8;
		const int stops_number = calculateStopsNumber(distance);

		if (stops_number < 1)
			return 0;

		if (stops_number == 1)
			return first_stop_time;

		return first_stop_time + second_stop_time + (stops_number - 2) * other_stops_time;
	}
}