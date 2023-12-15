#pragma once

#include "race.h"
#include "vehicle.h"

namespace races
{
	class AirRace : public Race
	{
	public:
		AirRace() : Race("Air Race") {}
		virtual ~AirRace() {}
		bool isVehicleCompatible(const vehicles::Vehicle* vehicle) const override;
	};
}