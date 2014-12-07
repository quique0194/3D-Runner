#ifndef GISMO_H
#define GISMO_H

#include "../lib/qu3e/src/q3.h"
#include "../PlatformObject.h"

class Gizmo: public PlatformObject {
    public:
        Gizmo() {
        }

        void display();
        void genBody(q3Scene& scene);
};

void Gizmo::display() {
    glBegin(GL_LINES);
        glColor3d(255,0,0);
        glVertex2d(0, 0);
        glVertex2d(1, 0);
        glColor3d(0, 255, 0);
        glVertex2d(0, 0);
        glVertex2d(0, 1);
    glEnd();
}

void Gizmo::genBody(q3Scene& scene) {
}

#endif
