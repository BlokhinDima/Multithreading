#pragma once

#include "ground_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class Camel : public GroundVehicle
	{
	public:
		Camel() : GroundVehicle(vehicles_models::VehiclesModels::CAMEL, 10, 30) {}
		virtual ~Camel() {}

	private:
		double calculateRecoveryTime(double distance) const override;
	};
}