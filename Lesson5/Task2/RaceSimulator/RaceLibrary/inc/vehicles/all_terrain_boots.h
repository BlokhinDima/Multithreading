#pragma once

#include "ground_vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class AllTerrainBoots : public GroundVehicle
	{
	public:
		AllTerrainBoots() 
			: GroundVehicle(vehicles_models::VehiclesModels::ALL_TERRAIN_BOOTS, 6, 60) {}
		virtual ~AllTerrainBoots() {}

	private:
		double calculateRecoveryTime(double distance) const override;
	};
}