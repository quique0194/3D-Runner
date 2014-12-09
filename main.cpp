#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <iostream>

#include <GL/glut.h>
#include "Clock.h"
#include "lib/qu3e/src/q3.h"
#include "Platform.h"
#include "PlatformManager.h"
#include "PlatformObjects/Player.h"
#include "ContactListeners/MyContactListener.h"

#define ESC_KEY 27
#define SPACEBAR 32

const float dt = 1.0f / 60.0f;
Platform platform(dt);
PlatformManager manager("config.txt");
Player* player;
MyContactListener* contactListener;

namespace Camera {
    q3Vec3 calculateUp(const q3Vec3& view) {
        return q3Normalize(q3Cross(view, q3Vec3(1, 0, 0)));
    }

    void recalculateCamera(GLfloat aspectRatio) {
        q3Vec3 target = player->getPosition();
        target[1] = 0;
        q3Vec3 position = target + q3Vec3(0, 10, -10),
        up = calculateUp(target - position);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, aspectRatio, 0.1f, 10000.0f);
        gluLookAt(
            position[0], position[1], position[2],
            target[0], target[1], target[2],
            up[0], up[1], up[2]
        );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
};

void Reshape(int width, int height) {
    if (height <= 0)
        height = 1;

    glViewport(0, 0, width, height);
    Camera::recalculateCamera((GLfloat)width / (GLfloat)height);
}

namespace Light {
    float ambient[ 4 ] = { 0.2, 0.2, 0.2, 1.0 };
    float diffuse[ 4 ] = { 0.3, 0.3, 0.3, 1.0 };
    float specular[ 4 ] = { 0.4, 0.4, 0.4, 1.0 };
};

void Keyboard(unsigned char key, int x, int y) {
    const float increment = 0.8f;

    switch(key) {
        case ESC_KEY:
            exit(0);
            break;
        case 'w':
            player->nitroOn();
            break;
        case 's':
            break;
        case 'a':
            player->moveRight();
            break;
        case 'd':
            player->moveLeft();
            break;
        case SPACEBAR:
            player->jump();
            break;
        case 'q':
            break;
        case 'e':
            break;
    }
}

void KeyboardUp(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            player->nitroOff();
            break;
        case 'a':
            player->stopMovingToSides();
            break;
        case 'd':
            player->stopMovingToSides();
            break;
    }
}

void DisplayFunction(void) {
    i32 w = glutGet(GLUT_WINDOW_WIDTH);
    i32 h = glutGet(GLUT_WINDOW_HEIGHT);
    Reshape(w, h);
    platform.display();
}

int main(int argc, char** argv) {
    // Starting width / height of the window
    const u32 kWindowWidth = 1000;
    const u32 kWindowHeight = 600;

    // Initialize GLUT
    glutInit(&argc, argv);

    // Get how big our screen is that we're displaying the window on
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Initialize the display mode to utilize double buffering, 4-channel framebuffer and depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // Setup the window
    glutInitWindowSize(kWindowWidth, kWindowHeight);
    glutInitWindowPosition((screenWidth - kWindowWidth) / 2, (screenHeight - kWindowHeight) / 2);
    glutCreateWindow("3D Runner");

    glutDisplayFunc(DisplayFunction);
    glutIdleFunc(DisplayFunction);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);

    // Setup all the open-gl states we want to use (ones that don't change in the lifetime of the application)
    // Note: These can be changed anywhere, but generally we don't change the back buffer color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Show the window that we just initialized
    glutShowWindow();

    // Used FFP to setup lights
    float floats[ 4 ];
    for (i32 i = 0; i < 4; ++i)
        floats[ i ] = (float)Light::ambient[ i ];
    glLightfv(GL_LIGHT0, GL_AMBIENT, floats);
    for (i32 i = 0; i < 4; ++i)
        floats[ i ] = (float)Light::diffuse[ i ];
    glLightfv(GL_LIGHT0, GL_DIFFUSE, floats);
    for (i32 i = 0; i < 4; ++i)
        floats[ i ] = (float)Light::specular[ i ];
    glLightfv(GL_LIGHT0, GL_SPECULAR, floats);
    // for (i32 i = 0; i < 4; ++i)
        // floats[ i ] = (float)position[ i ];
    floats[0] = 0;
    floats[1] = 10;
    floats[2] = -10;
    floats[3] = 1;
    glLightfv(GL_LIGHT0, GL_POSITION, floats);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);

    // initialize player and platform
    player = manager.getPlayer();
    manager.manage(&platform);
    contactListener = new MyContactListener(&platform, player);
    platform.setContactListener(contactListener);

    glutMainLoop();

    return 0;
}


