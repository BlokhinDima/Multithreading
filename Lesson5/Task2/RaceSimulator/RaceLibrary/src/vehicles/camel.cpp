#include "camel.h"

namespace vehicles
{
	double Camel::calculateRecoveryTime(double distance) const
	{
		const double first_stop_time = 5;
		const double other_stops_time = 8;
		const int stops_number = calculateStopsNumber(distance);

		if (stops_number < 1)
			return 0;

		return first_stop_time + (stops_number - 1) * other_stops_time;
	}
}
