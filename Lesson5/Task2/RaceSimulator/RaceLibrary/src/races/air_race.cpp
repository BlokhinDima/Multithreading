#include "air_race.h"
#include "vehicle.h"

bool races::AirRace::isVehicleCompatible(const vehicles::Vehicle* vehicle) const
{
	return vehicle->getType() == vehicles::VehicleType::AIR;
}
