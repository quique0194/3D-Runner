#ifndef PLATFORM_MANAGER
#define PLATFORM_MANAGER

#include "./ConfigFile.h"
#include "PlatformObjects/Road.h"
#include "PlatformObjects/Gizmo.h"
#include "PlatformObjects/Teapot.h"

class Platform;

class PlatformManager {
	public:
		PlatformManager(string filename): config(filename) {
			config.proc();
		}
		void manage(Platform* platform);
	private:
		ConfigFile config;
};

void PlatformManager::manage(Platform* platform) {
	double dist = config.getDouble("ROAD DISTANCE");
	// platform->addObject(new Road(dist));

	// platform->addObject(new Gizmo());
	platform->addObject(new Teapot());
}

#endif
