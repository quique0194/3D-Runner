#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

#include <GL/glut.h>

#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"
#include "../lib/gl_utils.h"
#include "../constants.h"
using namespace glutils;

class Car: public PlatformObject {
    public:
        Car(string _model, double _carril, double _z, double _velocity, int body_type=TYPE_OBSTACLE):
            PlatformObject(body_type, -20),
            model(_model),
            carril(_carril),
            z(_z),
            velocity(_velocity) {
        }

        void display();
        void genBody(q3Scene& scene);

    protected:
        string model;
        double carril;      // -1, 0 or 1
        double z;
        double velocity;

        virtual int getLayers() {
            return 0x00000001;
        }
};

void Car::display() {
    glColor3f(1, 1, 1);
    glPushMatrix();
        q3Vec3 tx = body->GetTransform().position;
        glTranslatef(tx[0], tx[1], tx[2]);
        draw_box(1.5, 1, 3);
    glPopMatrix();
}

void Car::genBody(q3Scene& scene) {
    q3BodyDef bodyDef;
    bodyDef.position = q3Vec3(3*carril*ROAD_WIDTH/8, 0.5, z);
    bodyDef.bodyType = eDynamicBody;
    bodyDef.linearVelocity = q3Vec3(0, 0, velocity);
    bodyDef.gravityScale = 5;
    bodyDef.lockAxisY = true;
    bodyDef.lockAxisX = true;
    bodyDef.lockAxisZ = true;
    bodyDef.userData = this;
    bodyDef.layers = getLayers();
    body = scene.CreateBody(bodyDef);

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    boxDef.Set( tx, q3Vec3(1.5, 1, 3) );
    boxDef.SetFriction(0);
    body->AddBox( boxDef );
}

#endif
