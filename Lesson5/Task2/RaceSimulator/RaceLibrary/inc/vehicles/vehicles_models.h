#pragma once

namespace vehicles_models
{
	enum class VehiclesModels
	{
		CAMEL = 0,
		RACING_CAMEL,
		CENTAUR,
		ALL_TERRAIN_BOOTS,
		MAGIC_CARPET,
		EAGLE,
		BROOM,
		VEHICLE_COUNT,
	};

	const char* vehicleToString(const VehiclesModels model);
}