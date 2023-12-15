#pragma once

#include "ground_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class RacingCamel : public GroundVehicle
	{
	public:
		RacingCamel() : GroundVehicle(vehicles_models::VehiclesModels::RACING_CAMEL, 40, 10) {}
		virtual ~RacingCamel() {}

	private:
		double calculateRecoveryTime(double distance) const override;
	};
}