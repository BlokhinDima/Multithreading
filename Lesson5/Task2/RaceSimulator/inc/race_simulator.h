#pragma once

#include "race.h"
#include "vehicles_models.h"
#include "races_factory.h"

namespace race_simulators 
{

	enum SimulatorStatus
	{
		OK,
		ERROR
	};

	class RaceSimulator
	{
	public:
		~RaceSimulator();
		int run();

	private:
		races::Race* race = nullptr;
		const races::LeadershipListEntry* leadership_list = nullptr;

		int getParticipantsNumber() const;
		void processRaceTypeSelection();
		void setRaceType(races_factory::RacesTypes type);
		void processDistanceInput();
		void setRaceDistance(double distance);
		void simulateRace();
		void printRaceInfo() const;
		void processVehiclesRegistration();
		void registerVehicles();
		void registerVehicle(const vehicles_models::VehiclesModels model);
		void printLeadershipTable() const;
		void printRacesMenu() const;
		void printVehiclesRegistrationMenu() const;
		void printEndMenu() const;
		bool askForRestart() const;
		int handleInput() const;
		void printWrongOptionMessage() const;
	};
}
