#ifndef TEAPOT_H
#define TEAPOT_H

#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"

class Teapot: public PlatformObject {
    public:
        Teapot() {
        }

        void display();
        void genBody(q3Scene& scene);
};

void Teapot::display() {
    GLfloat mat_ambient[4]  = {0.2, 0.2, 0.2, 1.0};
    GLfloat mat_diffuse[4]  = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_specular[4] = {0.3, 0.3, 0.3, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glutSolidTeapot(2);
}

void Teapot::genBody(q3Scene& scene) {
}

#endif
