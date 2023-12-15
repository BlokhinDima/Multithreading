#pragma once

#include <string>

#include "vehicles_models.h"

namespace vehicles 
{
	enum class VehicleType
	{
		UNKNOWN,
		GROUND,
		AIR,
	};

	class Vehicle
	{
	public:
		Vehicle(vehicles_models::VehiclesModels model, VehicleType type=VehicleType::UNKNOWN, int speed=1)
			: model(model), vehicle_type(type), speed(speed) {}
		virtual ~Vehicle() {}
		const char* getName() const { return vehicles_models::vehicleToString(model); }
		const VehicleType getType() const { return vehicle_type; }
		virtual double calculateTravelTime(double distance) const = 0;

	protected:
		const VehicleType vehicle_type;
		const vehicles_models::VehiclesModels model;
		unsigned int speed;
	};
}
