#ifndef PLATFORM_MANAGER
#define PLATFORM_MANAGER

#include "./ConfigFile.h"

class Platform;

class PlatformManager {
	public:
		PlatformManager(string filename): config(filename) {
			config.proc();
		}
		void managePlatform(Platform* platform);
	private:
		ConfigFile config;
};

void PlatformManager::managePlatform(Platform* platform) {
	double dist = config.getDouble("ROAD DISTANCE");
	platform.addObject(new Road(dist));
}

#endif
