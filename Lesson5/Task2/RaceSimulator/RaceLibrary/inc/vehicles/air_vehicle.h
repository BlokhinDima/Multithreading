#pragma once

#include "vehicle.h"
#include "vehicles_models.h"

namespace vehicles
{
	class AirVehicle : public Vehicle
	{
	public:
		AirVehicle(vehicles_models::VehiclesModels model, int speed) 
			: Vehicle(model, VehicleType::AIR, speed) {}
		virtual ~AirVehicle() {}
		double calculateTravelTime(double distance) const override;

	protected:
		double calculateReducedDistance(double distance) const;
		virtual double getReductonFactor(double distance) const = 0;
	};
}