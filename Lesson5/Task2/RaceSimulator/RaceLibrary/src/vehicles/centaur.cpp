#include "centaur.h"

namespace vehicles
{
	double Centaur::calculateRecoveryTime(double distance) const
	{
		double stops_time = 2;
		int stops_number = calculateStopsNumber(distance);
		return stops_time * stops_number;
	}
}
