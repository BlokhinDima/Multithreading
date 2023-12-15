#pragma once

#include "vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class GroundVehicle : public Vehicle
	{
	public:
		GroundVehicle(vehicles_models::VehiclesModels model, int speed, int move_time_until_rest)
			: Vehicle(model, VehicleType::GROUND, speed), move_time_until_rest(move_time_until_rest) {}
		virtual ~GroundVehicle() {}
		double calculateTravelTime(double distance) const override;

	protected:
		int move_time_until_rest{};
		virtual double calculateRecoveryTime(double distance) const = 0;
		int calculateStopsNumber(double distance) const;
	};
}