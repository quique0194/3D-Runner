#ifndef GLUTILS_H
#define GLUTILS_H

namespace glutils {
	void draw_box(double x, double y, double z) {
		x /= 2;
		y /= 2;
		z /= 2;
	    glBegin(GL_QUADS);
	        glNormal3f(0, 0, -1);
	        glVertex3f(-x, y, -z);
	        glVertex3f(x, y, -z);
	        glVertex3f(x, -y, -z);
	        glVertex3f(-x, -y, -z);

	        glNormal3f(0, 0, 1);
	        glVertex3f(-x, y, z);
	        glVertex3f(x, y, z);
	        glVertex3f(x, -y, z);
	        glVertex3f(-x, -y, z);

	        glNormal3f(0, 1, 0);
	        glVertex3f(-x, y, -z);
	        glVertex3f(x, y, -z);
	        glVertex3f(x, y, z);
	        glVertex3f(-x, y, z);

	        glNormal3f(0, -1, 0);
	        glVertex3f(x, -y, -z);
	        glVertex3f(-x, -y, -z);
	        glVertex3f(-x, -y, z);
	        glVertex3f(x, -y, z);

	        glNormal3f(-1, 0, 0);
	        glVertex3f(-x, y, -z);
	        glVertex3f(-x, -y, -z);
	        glVertex3f(-x, -y, z);
	        glVertex3f(-x, y, z);

	        glNormal3f(1, 0, 0);
	        glVertex3f(x, y, -z);
	        glVertex3f(x, -y, -z);
	        glVertex3f(x, -y, z);
	        glVertex3f(x, y, z);
	    glEnd();
	}
};

#endif
