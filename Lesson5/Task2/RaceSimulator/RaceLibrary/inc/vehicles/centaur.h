#pragma once

#include "ground_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class Centaur : public GroundVehicle
	{
	public:
		Centaur() : GroundVehicle(vehicles_models::VehiclesModels::CENTAUR, 15, 8) {}
		virtual ~Centaur() {}

	private:
		double calculateRecoveryTime(double distance) const override;
	};
}