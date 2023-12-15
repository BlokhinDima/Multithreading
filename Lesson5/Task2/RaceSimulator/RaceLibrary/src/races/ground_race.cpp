#include "vehicle.h"
#include "ground_race.h"

bool races::GroundRace::isVehicleCompatible(const vehicles::Vehicle* vehicle) const
{
	return vehicle->getType() == vehicles::VehicleType::GROUND;
}
