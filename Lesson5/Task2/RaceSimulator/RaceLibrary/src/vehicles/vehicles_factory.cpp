#include <string>

#include "vehicles_factory.h"
#include "vehicles_models.h"
#include "vehicle.h"
#include "camel.h"
#include "racing_camel.h"
#include "centaur.h"
#include "all_terrain_boots.h"
#include "magic_carpet.h"
#include "eagle.h"
#include "broom.h"
#include "simulator_exception.h"

namespace vehicles_factory
{
	vehicles::Vehicle* createVehicle(const vehicles_models::VehiclesModels model)
	{
		switch (model)
		{
		case vehicles_models::VehiclesModels::CAMEL:
			return new vehicles::Camel();

		case vehicles_models::VehiclesModels::RACING_CAMEL:
			return new vehicles::RacingCamel();

		case vehicles_models::VehiclesModels::CENTAUR:
			return new vehicles::Centaur();

		case vehicles_models::VehiclesModels::ALL_TERRAIN_BOOTS:
			return new vehicles::AllTerrainBoots();

		case vehicles_models::VehiclesModels::MAGIC_CARPET:
			return new vehicles::MagicCarpet();

		case vehicles_models::VehiclesModels::EAGLE:
			return new vehicles::Eagle();

		case vehicles_models::VehiclesModels::BROOM:
			return new vehicles::Broom();

		default:
			throw simulator_exceptions::SimulatorException("Undefined vehicle type!");
		}
	}

	void deleteVehicle(vehicles::Vehicle* vehicle)
	{
		if (vehicle)
		{
			delete vehicle;
			vehicle = nullptr;
		}
	}
}