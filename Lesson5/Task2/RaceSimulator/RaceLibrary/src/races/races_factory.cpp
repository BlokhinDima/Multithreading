#include <stdexcept>

#include "races_factory.h"
#include "race.h"
#include "air_race.h"
#include "ground_race.h"
#include "simulator_exception.h"

namespace races_factory
{
	races::Race* createRace(const RacesTypes type)
	{
		switch (type)
		{
		case RacesTypes::MIXED_RACE:
			return new races::Race();

		case RacesTypes::GROUND_RACE:
			return new races::GroundRace();

		case RacesTypes::AIR_RACE:
			return new races::AirRace();

		default:
			throw simulator_exceptions::SimulatorException("Undefined race type!");
		}
	}

	void deleteRace(races::Race* race)
	{
		if (race)
		{
			delete race;
			race = nullptr;
		}
	}
}