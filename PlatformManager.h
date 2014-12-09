#ifndef PLATFORM_MANAGER
#define PLATFORM_MANAGER

#include "./ConfigFile.h"
#include "PlatformObjects/Road.h"
#include "PlatformObjects/Gizmo.h"
#include "PlatformObjects/Teapot.h"
#include "PlatformObjects/Building.h"
#include "PlatformObjects/Car.h"
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
};

void PlatformManager::manage(Platform* platform) {
	platform->addObject(player);
	double dist = config.getDouble("ROAD DISTANCE");
	platform->addObject(new Road(dist));
	platform->addObject(new Building("A", 0, 0));
	platform->addObject(new Building("B", 1, 0));
	// platform->addObject(new Car("", 5));

	// platform->addObject(new Gizmo());
	// platform->addObject(new Teapot());
}

Player* PlatformManager::getPlayer() {
	return player;
}

#endif
