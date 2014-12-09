#ifndef PLATFORM_MANAGER
#define PLATFORM_MANAGER

#include "./ConfigFile.h"
#include "PlatformObjects/Road.h"
#include "PlatformObjects/Gizmo.h"
#include "PlatformObjects/Teapot.h"
#include "PlatformObjects/Building.h"
#include "PlatformObjects/Car.h"
#include "PlatformObjects/Coin.h"
#include "PlatformObjects/Player.h"

class Platform;

class PlatformManager {
	public:
		PlatformManager(string filename): config(filename) {
			config.proc();
			player = new Player("", config.getDouble("PLAYER SPEED"));
		}
		void manage(Platform* platform);
		Player* getPlayer();
	private:
		ConfigFile config;
		Player* player;

		void manageBuildings(Platform* platform, double dist);
		void manageCoins(Platform* platform);
		void manageCars(Platform* platform);
};

void PlatformManager::manage(Platform* platform) {
	platform->addObject(player);
	double dist = config.getDouble("ROAD DISTANCE");
	manageBuildings(platform, dist);
	platform->addObject(new Road(dist));
	manageCoins(platform);
	manageCars(platform);
}

void PlatformManager::manageCoins(Platform* platform) {
	vector<double> left_coins = config.getDoubles("COINS LEFT");
	vector<double> center_coins = config.getDoubles("COINS CENTER");
	vector<double> right_coins = config.getDoubles("COINS RIGHT");
	for (auto z: left_coins) {
		platform->addObject(new Coin(-1, z));
	}
	for (auto z: center_coins) {
		platform->addObject(new Coin(0, z));
	}
	for (auto z: right_coins) {
		platform->addObject(new Coin(1, z));
	}
}

void PlatformManager::manageCars(Platform* platform) {
	vector<double> left_cars = config.getDoubles("CARS LEFT");
	vector<double> center_cars = config.getDoubles("CARS CENTER");
	vector<double> right_cars = config.getDoubles("CARS RIGHT");
	vector<double> left_speed = config.getDoubles("SPEED CARS LEFT");
	vector<double> center_speed = config.getDoubles("SPEED CARS CENTER");
	vector<double> right_speed = config.getDoubles("SPEED CARS RIGHT");
	for (int i = 0; i < left_cars.size(); ++i) {
		platform->addObject(new Car("", -1, left_cars[i], left_speed[i]));
	}
	for (int i = 0; i < center_cars.size(); ++i) {
		platform->addObject(new Car("", 0, center_cars[i], center_speed[i]));
	}
	for (int i = 0; i < right_cars.size(); ++i) {
		platform->addObject(new Car("", 1, right_cars[i], right_speed[i]));
	}
}

void PlatformManager::manageBuildings(Platform* platform, double dist) {
	double z = 0;
	Building* building;
	for (int i = 0; z < dist; ++i) {
		building = new Building("A", 0, z);
		platform->addObject(building);
		z += building->getZSize();
		building = new Building("B", 0, z);
		platform->addObject(building);
		z += building->getZSize();
	}
	z = 0;
	for (int i = 0; z < dist; ++i) {
		building = new Building("A", 1, z);
		platform->addObject(building);
		z += building->getZSize();
		building = new Building("B", 1, z);
		platform->addObject(building);
		z += building->getZSize();
	}
}

Player* PlatformManager::getPlayer() {
	return player;
}

#endif
