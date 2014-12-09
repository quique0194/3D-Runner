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
			player = new Player("", 5);
		}
		void manage(Platform* platform);
		Player* getPlayer();
	private:
		ConfigFile config;
		Player* player;

		void manageBuildings(Platform* platform, double dist);
};

void PlatformManager::manage(Platform* platform) {
	platform->addObject(player);
	double dist = config.getDouble("ROAD DISTANCE");
	manageBuildings(platform, dist);

	platform->addObject(new Road(dist));

	platform->addObject(new Coin(-1, 14));
	platform->addObject(new Coin(-1, 15));
	platform->addObject(new Coin(-1, 16));
	platform->addObject(new Coin(-1, 17));
	platform->addObject(new Coin(-1, 18));

	// platform->addObject(new Car("", 5));

	// platform->addObject(new Gizmo());
	// platform->addObject(new Teapot());
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
