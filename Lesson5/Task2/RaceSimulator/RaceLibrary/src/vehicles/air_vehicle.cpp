#include "vehicle.h"
#include "air_vehicle.h"

namespace vehicles
{
	double AirVehicle::calculateTravelTime(double distance) const
	{
		return calculateReducedDistance(distance) / speed;
	}

	double AirVehicle::calculateReducedDistance(double distance) const
	{
		return (1 - getReductonFactor(distance)) * distance;
	}
}
