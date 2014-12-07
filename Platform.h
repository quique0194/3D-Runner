#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
using namespace std;

class PlatformObject;

class Platform {
    public:
        Platform(double dt = 1.0/60.0);
        ~Platform();

        void addObject(PlatformObject* object);
        void removeObject(PlatformObject* object);

        void display();
    private:
        double dt;
        vector<PlatformObject*> objects;
        q3Scene scene;
        Clock clock;
};


Platform::Platform(double _dt): dt(_dt), scene(dt) {
    scene.SetIterations( 10 );
    scene.SetAllowSleep( true );
    scene.RemoveAllBodies( );
}

Platform::~Platform() {
    for (auto object: objects) {
        delete object;
    }
}

void Platform::addObject(PlatformObject* object) {
    objects.push_back(object);
}

void Platform::removeObject(PlatformObject* object) {

}

void Platform::display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    static float accumulator = 0;

    accumulator += clock.Start( ) * 0.5f;

    while (accumulator >= dt) {
        scene.Step( );
        accumulator -= dt;
    }

    clock.Stop( );

    glutSwapBuffers( );
}


#endif
