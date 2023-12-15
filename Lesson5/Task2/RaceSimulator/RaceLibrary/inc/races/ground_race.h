#pragma once

#include "race.h"
#include "vehicle.h"

namespace races
{
	class GroundRace : public Race
	{
	public:
		GroundRace() : Race("Ground Race") {}
		~GroundRace() {}
		bool isVehicleCompatible(const vehicles::Vehicle* vehicle) const override;
	};
}