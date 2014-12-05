#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>

class PlatformObject;

class Platform {
    public:
        Platform(double dt = 1.0/60.0);
        ~Platform();

        void addObject(PlatformObject* object);
        void removeObject(PlatformObject* object);
    private:
        vector<PlatformObject*> objects;
        q3Scene scene;
};

Platform::Platform(double dt): scene(dt) {
    scene.SetIterations( 10 );
    scene.SetAllowSleep( true );
    scene.RemoveAllBodies( );
}

Platform::~Platform() {
    for (auto object: objects) {
        delete object;
    }
}

Platform::addObject(PlatformObject* object) {
    objects.push_back(object);
}

Platform::removeObject(PlatformObject* object) {

}


#endif
