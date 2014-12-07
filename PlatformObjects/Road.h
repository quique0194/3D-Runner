#ifndef ROAD_H
#define ROAD_H

#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"

class Road: public PlatformObject {
    public:
        Road(double _distance = 100):
            distance(_distance) {
        }

        void display();
        void genBody(q3Scene& scene);

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

void Road::genBody(q3Scene& scene) {
    q3BodyDef bodyDef;
    body = scene.CreateBody( bodyDef );

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, distance ) );
    body->AddBox( boxDef );
}

#endif
