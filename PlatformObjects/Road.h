#ifndef ROAD_H
#define ROAD_H

#include "../constants.h"
#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"
#include "../lib/gl_utils.h"
using namespace glutils;


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
    glColor3f(0.3, 0.3, 0.3);
    glPushMatrix();
        q3Vec3 tx = body->GetTransform().position;
        glTranslatef(tx[0], tx[1], tx[2]);
        draw_box(ROAD_WIDTH, 1, distance);
    glPopMatrix();
}

void Road::genBody(q3Scene& scene) {
    q3BodyDef bodyDef;
    bodyDef.position = q3Vec3(0, -0.5, distance/2);
    body = scene.CreateBody( bodyDef );

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    boxDef.Set( tx, q3Vec3(ROAD_WIDTH, 1, distance) );
    boxDef.SetFriction(0);
    body->AddBox( boxDef );
}

#endif
