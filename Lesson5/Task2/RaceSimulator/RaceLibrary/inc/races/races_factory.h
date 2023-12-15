#pragma once

#include "race.h"

namespace races_factory
{
	enum class RacesTypes
	{
		GROUND_RACE = 0,
		AIR_RACE,
		MIXED_RACE
	};

	races::Race* createRace(const RacesTypes type);
	void deleteRace(races::Race* race);
}