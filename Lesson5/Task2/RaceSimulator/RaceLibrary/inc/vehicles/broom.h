#pragma once

#include "air_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class Broom : public AirVehicle
	{
	public:
		Broom() : AirVehicle(vehicles_models::VehiclesModels::BROOM, 20) {}
		virtual ~Broom() {}

	private:
		double getReductonFactor(double distance) const override;
	};
}