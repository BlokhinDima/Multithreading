#include "vehicles_models.h"

namespace vehicles_models
{
	const char* vehicleToString(vehicles_models::VehiclesModels model)
	{
		const char* vehicleNames[] =
		{
			"Camel",
			"Racing Camel",
			"Centaur",
			"All Terrain Boots",
			"Magic Carpet",
			"Eagle",
			"Broom"
		};

		return vehicleNames[static_cast<int>(model)];
	}
}