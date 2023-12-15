#pragma once

#include "vehicle.h"
#include "vehicles_models.h"

namespace vehicles_factory
{
	vehicles::Vehicle* createVehicle(const vehicles_models::VehiclesModels model);
	void deleteVehicle(vehicles::Vehicle* vehicle);
}