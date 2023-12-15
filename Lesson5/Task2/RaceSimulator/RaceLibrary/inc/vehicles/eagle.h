#pragma once

#include "air_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class Eagle : public AirVehicle
	{
	public:
		Eagle() : AirVehicle(vehicles_models::VehiclesModels::EAGLE, 8) {}
		virtual ~Eagle() {}

	private:
		double getReductonFactor(double distance) const override;
	};
}