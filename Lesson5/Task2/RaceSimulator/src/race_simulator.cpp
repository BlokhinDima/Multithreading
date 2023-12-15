#include <iostream>
#include <climits>

#include "race_simulator.h"
#include "race.h"
#include "races_factory.h"
#include "vehicle.h"
#include "vehicles_factory.h"

#include "simulator_exception.h"
#include "registration_exception.h"
#include "distance_value_exception.h"

namespace race_simulators
{
	RaceSimulator::~RaceSimulator()
	{
		races_factory::deleteRace(race);
	}

	int RaceSimulator::run()
	{
		std::cout << "Welcome to race simulator!" << std::endl;

		for (;;)
		{
			processRaceTypeSelection();
			processDistanceInput();
			processVehiclesRegistration();
			simulateRace();
			printLeadershipTable();
			bool choice = askForRestart();
			if (choice)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		return OK;
	}

	void RaceSimulator::processRaceTypeSelection()
	{
		try
		{
			std::cout << std::endl << "Select race type: ";
			printRacesMenu();
			int race_type = handleInput();
			setRaceType(static_cast<races_factory::RacesTypes>(race_type - 1));
		}
		catch (const simulator_exceptions::SimulatorException& ex)
		{
			race = nullptr;
			std::cout << std::endl << ex.what() << std::endl;
			processRaceTypeSelection();
		}
	}

	void RaceSimulator::setRaceType(races_factory::RacesTypes type)
	{
		races_factory::deleteRace(race);
		race = races_factory::createRace(type);
	}

	void RaceSimulator::processDistanceInput()
	{
		try
		{
			std::cout << std::endl << "Enter race distance (must be positive). ";
			double distance = handleInput();
			setRaceDistance(distance);
		}
		catch (const simulator_exceptions::DistanceValueException& ex)
		{
			std::cout << std::endl << ex.what() << std::endl;
			processDistanceInput();
		}
	}

	void RaceSimulator::setRaceDistance(double distance)
	{
		race->setDistance(distance);
	}

	void RaceSimulator::processVehiclesRegistration()
	{
		for (;;)
		{
			const int participants_number = getParticipantsNumber();
			std::cout << std::endl
				<< "At least 2 vehicles must be registered to start race. "
				<< "Participants registered: " << participants_number << std::endl;

			std::cout << "1. Register vehicle" << std::endl;
			if (participants_number >= 2)
			{
				std::cout << "2. Start race" << std::endl;
			}

			int input = handleInput();
			if (input == 1)
			{
				registerVehicles();
			}
			else if (input == 2 && participants_number >= 2)
			{
				break;
			}
			else
			{
				printWrongOptionMessage();
			}
		}
	}

	void RaceSimulator::registerVehicles()
	{
		try
		{
			for (;;)
			{
				std::cout << std::endl
					<< "Select vehicle model or enter 0 to end registration: ";
				printVehiclesRegistrationMenu();
				int input = handleInput();

				if (input == 0) { break; }

				registerVehicle(
					static_cast<vehicles_models::VehiclesModels>(input - 1)
				);
				printRaceInfo();
			}
		}
		catch (const simulator_exceptions::RegistrationException& ex)
		{
			std::cout << std::endl << ex.what() << std::endl;
			registerVehicles();
		}
		catch (const simulator_exceptions::SimulatorException& ex)
		{
			std::cout << std::endl << ex.what() << std::endl;
			registerVehicles();
		}
	}

	void RaceSimulator::registerVehicle(vehicles_models::VehiclesModels model)
	{
		race->registerVehicle(model);
		const char* vehicle_name = vehicles_models::vehicleToString(model);
		std::cout << std::endl << vehicle_name << " registered!" << std::endl;
	}

	void RaceSimulator::simulateRace()
	{
		leadership_list = race->calculateRaceLeaderhsipTable();
	}

	void RaceSimulator::printRaceInfo() const
	{
		std::cout << race->getName() << ". Distance: " << race->getDistance() << std::endl;

		std::cout << "Registered vehicles: ";
		const vehicles::Vehicle** registered_vehicles = race->getRegisteredVehicles();
		int vehicles_number = getParticipantsNumber();
		for (int i = 0; i < vehicles_number; ++i)
		{
			std::cout << registered_vehicles[i]->getName();
			if (i != vehicles_number - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}

	int RaceSimulator::getParticipantsNumber() const
	{
		if (race)
		{
			return race->getParticipantsNumber();
		}
		return 0;
	}

	bool RaceSimulator::askForRestart() const
	{
		int choice = 0;
		for (;;)
		{
			std::cout << std::endl << "Do you want to start new race?";
			printEndMenu();
			choice = handleInput();
			if (choice == 1)
			{
				return true;
			}
			else if (choice == 2)
			{
				return false;
			}
			else
			{
				printWrongOptionMessage();
			}
		}
	}

	void RaceSimulator::printLeadershipTable() const
	{
		std::cout << std::endl << "Race result: " << std::endl;
		const int vehicles_number = getParticipantsNumber();

		for (int i = 0; i < vehicles_number; ++i)
		{
			races::LeadershipListEntry entry = leadership_list[i];
			std::cout << (i + 1) << ". "
				<< entry.vehicle_name << ". "
				<< "Result: " << entry.race_score
				<< std::endl;
		}
	}

	void RaceSimulator::printRacesMenu() const
	{
		std::cout << std::endl;
		std::cout << "1. Ground vehicles race" << std::endl;
		std::cout << "2. Air vehicles race" << std::endl;
		std::cout << "3. Mixed vehicles race" << std::endl;
	}

	void RaceSimulator::printVehiclesRegistrationMenu() const
	{
		std::cout << std::endl;
		std::cout << "1. Camel" << std::endl;
		std::cout << "2. Racing Camel" << std::endl;
		std::cout << "3. Centaur" << std::endl;
		std::cout << "4. All Terrian Boots" << std::endl;
		std::cout << "5. Magic Carpet" << std::endl;
		std::cout << "6. Eagle" << std::endl;
		std::cout << "7. Broom" << std::endl;
		std::cout << "0. End registration" << std::endl;
	}
	 
	void RaceSimulator::printEndMenu() const
	{
		std::cout << std::endl;
		std::cout << "1. Start new race" << std::endl;
		std::cout << "2. Quit" << std::endl;
	}

	int RaceSimulator::handleInput() const
	{
		int choice = 0;
		std::cout << "Enter value: ";
		std::cin >> choice;
		while (std::cin.fail())
		{
			std::cout << std::endl << "Wrong input! Try again." << std::endl;
			std::cout << "Enter value: ";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cin >> choice;
		}
		return choice;
	}

	void RaceSimulator::printWrongOptionMessage() const
	{
		std::cout << std::endl << "Wrong option! Try again." << std::endl;
	}
}