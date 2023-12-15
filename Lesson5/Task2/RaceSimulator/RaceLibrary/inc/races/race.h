#pragma once

#include <string>

#include "vehicle.h"
#include "vehicles_factory.h"
#include "vehicles_models.h"

namespace races
{
	struct LeadershipListEntry
	{
		std::string vehicle_name{};
		double race_score{};
	};

	class Race
	{
	public:
		Race(const std::string& name = "Mixed Race");
		virtual ~Race();
		const std::string& getName() const { return name; }
		void setDistance(double distance);
		double getDistance() const { return distance; } 
		int getParticipantsNumber() const { return participants_number; }
		void registerVehicle(const vehicles_models::VehiclesModels model);
		const vehicles::Vehicle** getRegisteredVehicles() { return registered_vehicles; }
		const LeadershipListEntry* calculateRaceLeaderhsipTable();

	protected:
		const int MINIMUM_PARTICIPANTS = 2;
		const std::string name;
		double distance = 0;
		int participants_number = 0;
		int vehicles_storage_size = MINIMUM_PARTICIPANTS;
		const vehicles::Vehicle** registered_vehicles = nullptr;
		LeadershipListEntry* leadership_list = nullptr;

		void deleteLeadershipList();
		const vehicles::Vehicle** createVehiclesStorage(int size);
		void deleteVehiclesStorage(const vehicles::Vehicle** storage);
		void deleteVehicles();
		bool isVehicleRegistered(const vehicles::Vehicle* vehicle) const;
		virtual bool isVehicleCompatible(const vehicles::Vehicle* vehicle) const;
		void addVehicleToStorage(const vehicles::Vehicle* vehicle);
		void sortVehiclesByTravelTime();
		void createLeadershipList();
	};
}
