#ifndef BUILDING_H
#define BUILDING_H

#include <string>
using namespace std;

#include "../constants.h"
#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"
#include "../lib/gl_utils.h"
using namespace glutils;


class Building: public PlatformObject {
    public:
        Building(string _type, int _side, double _z_ini):
            type(_type),
            side(_side),
            z_ini(_z_ini) {
            	if (type == "A") {
            		x_size = 5;
            		y_size = 2;
            		z_size = 3;
            	} else if (type == "B") {
            		x_size = 3;
            		y_size = 5;
            		z_size = 4;
            	}
        }

        void display();
        void genBody(q3Scene& scene);
        double getZSize();

    private:
        string type;
        int side;
        double z_ini;
        double x_size, y_size, z_size;
};

void Building::display() {
	if (type == "A") {
    	glColor3f(1, 0, 0);	
	} else if (type == "B") {
		glColor3f(0, 1, 0);
	}
    glPushMatrix();
        q3Vec3 tx = body->GetTransform().position;
        glTranslatef(tx[0], tx[1], tx[2]);
        draw_box(x_size, y_size, z_size);
    glPopMatrix();
}

void Building::genBody(q3Scene& scene) {
    q3BodyDef bodyDef;
    if (side == 0) {	// left
    	bodyDef.position = q3Vec3(-ROAD_WIDTH/2 - x_size/2, y_size/2, z_ini + z_size/2);
    } else {			// right
    	bodyDef.position = q3Vec3(ROAD_WIDTH/2 + x_size/2, y_size/2, z_ini + z_size/2);
    }
    body = scene.CreateBody( bodyDef );

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    boxDef.Set( tx, q3Vec3(x_size, y_size, z_size) );
    boxDef.SetFriction(0);
    body->AddBox( boxDef );
}

double Building::getZSize() {
	return z_size;
}

#endif
