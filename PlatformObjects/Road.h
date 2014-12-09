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
    bodyDef.userData = this;
    body = scene.CreateBody(bodyDef);

    q3Transform tx;
    q3Identity(tx);

    q3BoxDef boxDef;
    boxDef.SetRestitution(0);
    boxDef.SetFriction(0);
    boxDef.Set(tx, q3Vec3(ROAD_WIDTH, 1, distance));
    body->AddBox(boxDef);


    // crear barandales
    q3Body* baranda;

    bodyDef.position = q3Vec3(ROAD_WIDTH/2, 2.5, distance/2);
    baranda = scene.CreateBody(bodyDef);

    boxDef.Set(tx, q3Vec3(0.1, 5, distance));
    baranda->AddBox(boxDef);

    bodyDef.position = q3Vec3(-ROAD_WIDTH/2, 2.5, distance/2);
    baranda = scene.CreateBody(bodyDef);
    baranda->AddBox(boxDef);

    // crear tope
    q3Body* tope;
    bodyDef.position = q3Vec3(0, 2.5, distance);
    tope = baranda = scene.CreateBody(bodyDef);

    boxDef.Set(tx, q3Vec3(ROAD_WIDTH, 5, 0.1));
    tope->AddBox(boxDef);
}

#endif
