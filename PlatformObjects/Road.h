#ifndef ROAD_H
#define ROAD_H

#include "qu3e/src/q3.h"
#include "../PlatformObject.h"

class Road: public PlatformObject {
    public:
        Road(double _distance = 100):
            distance(_distance) {

        }

        void display();
        void genBody(q3Scene& scene, const q3Transform& tx);

    private:
        double distance;           // how long is the road
};

void Road::display() {
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex3f(-3, 0, 0);
        glVertex3f(3, 0, 0);
        glVertex3f(3, -5, 0);
        glVertex3f(-3, -5, 0);
    glEnd();
}

void Road::genBody(q3Scene& scene, const q3Transform& tx) {
    q3BodyDef bodyDef;
    q3Body* body = scene.CreateBody( bodyDef );

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, distance ) );
    body->AddBox( boxDef );
}

#endif
