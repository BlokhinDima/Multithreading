#include "race.h"
#include "vehicle.h"
#include "vehicles_factory.h"

#include "distance_value_exception.h"
#include "competitors_number_exception.h"
#include "registration_exception.h"

namespace races
{
	Race::Race(const std::string& name) : name(name)
	{
		registered_vehicles = createVehiclesStorage(vehicles_storage_size);
	}

	Race::~Race()
	{
		deleteLeadershipList();
		deleteVehicles();
		deleteVehiclesStorage(registered_vehicles);
	}

	void Race::deleteLeadershipList()
	{
		if (leadership_list)
		{
			delete[] leadership_list;
			leadership_list = nullptr;
		}
	}

	void Race::deleteVehiclesStorage(const vehicles::Vehicle** storage)
	{
		if (storage)
		{
			delete[] storage;
			storage = nullptr;
		}
	}

	void Race::deleteVehicles()
	{
		if (registered_vehicles)
		{
			for (int i = 0; i < participants_number; ++i)
			{
				delete registered_vehicles[i];
			}
		}
	}

	void Race::setDistance(double distance)
	{
		if (distance <= 0)
		{
			throw simulator_exceptions::DistanceValueException();
		}
		this->distance = distance;
	}

	void Race::registerVehicle(const vehicles_models::VehiclesModels model)
	{
		vehicles::Vehicle* vehicle = vehicles_factory::createVehicle(model);

		if (isVehicleRegistered(vehicle))
		{
			vehicles_factory::deleteVehicle(vehicle);
			throw simulator_exceptions::RegistrationException(
				"This type of vehicle already registred!"
			);
		}

		if (!isVehicleCompatible(vehicle))
		{
			vehicles_factory::deleteVehicle(vehicle);
			throw simulator_exceptions::RegistrationException(
				"Attemp to registrate incompatible vehicle type!"
			);
		}

		addVehicleToStorage(vehicle);
	}

	bool Race::isVehicleRegistered(const vehicles::Vehicle* vehicle) const
	{
		for (int i = 0; i < participants_number; ++i)
		{
			if (registered_vehicles[i]->getName() == vehicle->getName())
			{
				return true;
			}
		}
		return false;
	}

	bool Race::isVehicleCompatible(const vehicles::Vehicle* vehicle) const
	{
		return true;
	}

	void Race::addVehicleToStorage(const vehicles::Vehicle* vehicle)
	{
		const int new_participants_number = participants_number + 1;

		if (new_participants_number > vehicles_storage_size)
		{
			const int new_storage_size = vehicles_storage_size * 2;
			const vehicles::Vehicle** new_storage = createVehiclesStorage(new_storage_size);

			for (int i = 0; i < new_participants_number - 1; ++i)
			{
				new_storage[i] = registered_vehicles[i];
			}
			new_storage[new_participants_number - 1] = vehicle;

			deleteVehiclesStorage(registered_vehicles);
			registered_vehicles = new_storage;
			vehicles_storage_size = new_storage_size;
		}
		else
		{
			registered_vehicles[new_participants_number - 1] = vehicle;
		}

		participants_number += 1;
	}

	const vehicles::Vehicle** Race::createVehiclesStorage(int size)
	{
		return new const vehicles::Vehicle*[size];
	}

	const LeadershipListEntry* Race::calculateRaceLeaderhsipTable()
	{
		if (participants_number < MINIMUM_PARTICIPANTS)
		{
			throw simulator_exceptions::CompetitiorsNumberException();
		}
		sortVehiclesByTravelTime();
		createLeadershipList();
		return leadership_list;
	}

	void Race::sortVehiclesByTravelTime()
	{
		bool swapped = false;

		for (int i = 0; i < participants_number - 1; ++i)
		{
			swapped = false;

			for (int j = 0; j < participants_number - i - 1; ++j)
			{
				double current_vehicle_score = registered_vehicles[j]->calculateTravelTime(distance);
				double next_vehicle_score = registered_vehicles[j + 1]->calculateTravelTime(distance);

				if (current_vehicle_score > next_vehicle_score)
				{
					const vehicles::Vehicle* temp = registered_vehicles[j];
					registered_vehicles[j] = registered_vehicles[j + 1];
					registered_vehicles[j + 1] = temp;
					swapped = true;
				}
			}

			if (swapped == false)
				break;
		}
	}

	void Race::createLeadershipList()
	{
		deleteLeadershipList();
		leadership_list = new LeadershipListEntry[participants_number];

		for (int i = 0; i < participants_number; ++i)
		{
			leadership_list[i].vehicle_name = registered_vehicles[i]->getName();
			leadership_list[i].race_score = registered_vehicles[i]->calculateTravelTime(distance);
		}
	}
}
