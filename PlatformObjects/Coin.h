#ifndef COIN_H
#define COIN_H


#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"
#include "../constants.h"
using namespace glutils;

class Coin: public PlatformObject {
    public:
        Coin(double _carril, double _z):
        	PlatformObject(TYPE_COIN, 10),
        	carril(_carril),
        	z(_z) {

        }

        void display();
        void genBody(q3Scene& scene);
    protected:
    	double carril; 	// can be -1, 0 or 1
    	double z;
};

void Coin::display() {
    glColor3f(1, 1, 0);
    glPushMatrix();
    	q3Vec3 tx = body->GetTransform().position;
    	glTranslatef(tx[0], tx[1], tx[2]);
    	glutSolidTorus(0.1, 0.25, 10, 10);
    glPopMatrix();
}

void Coin::genBody(q3Scene& scene) {
    q3BodyDef bodyDef;
    bodyDef.position = q3Vec3(3*carril*ROAD_WIDTH/8, 1, z);
    bodyDef.bodyType = eDynamicBody;
    bodyDef.gravityScale = 0;
    bodyDef.userData = this;
    body = scene.CreateBody(bodyDef);

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    boxDef.Set( tx, q3Vec3(0.5, 0.5, 0.5) );
    body->AddBox( boxDef );
}

#endif
