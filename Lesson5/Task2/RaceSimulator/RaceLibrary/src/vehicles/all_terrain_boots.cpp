#include "all_terrain_boots.h"

namespace vehicles
{
	double AllTerrainBoots::calculateRecoveryTime(double distance) const
	{
		double first_stop_time = 10;
		double other_stops_time = 5;
		int stops_number = calculateStopsNumber(distance);

		if (stops_number == 0)
			return 0;

		return first_stop_time + (stops_number - 1) * other_stops_time;
	}
}
