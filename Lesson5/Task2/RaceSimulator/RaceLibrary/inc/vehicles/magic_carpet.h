#pragma once

#include "air_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class MagicCarpet : public AirVehicle
	{
	public:
		MagicCarpet() : AirVehicle(vehicles_models::VehiclesModels::MAGIC_CARPET, 10) {}
		virtual ~MagicCarpet() {}

	private:
		double getReductonFactor(double distance) const override;
	};
}