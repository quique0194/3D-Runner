#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
using namespace std;

#include <GL/glut.h>

#include "./PlatformObject.h"
#include "./Renderer.h"
#include "./constants.h"
#include "./Clock.h"

class Platform {
    public:
        Platform(double dt = 1.0/60.0);
        ~Platform();

        void addObject(PlatformObject* object);
        void removeObject(PlatformObject* object);

        void setContactListener(q3ContactListener* listener);

        void display();
    private:
        double dt;
        Renderer renderer;
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

void Platform::setContactListener(q3ContactListener* listener) {
    scene.SetContactListener(listener);
}

void Platform::addObject(PlatformObject* object) {
    object->genBody(scene);
    objects.push_back(object);
}

void Platform::removeObject(PlatformObject* object) {
    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i] == object) {
            scene.RemoveBody(objects[i]->body);
            objects.erase(objects.begin()+i);
            return;
        }
    }
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
    for (auto object: objects) {
        object->display();
    }


    if (RENDER_BODIES) {
        scene.Render( &renderer );
    }
    glutSwapBuffers( );
}

#endif
