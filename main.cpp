#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <iostream>

#include <GL/glut.h>
#include "Clock.h"
#include "lib/qu3e/src/q3.h"
#include "Platform.h"
// #include "PlatformManager.h"

#define ESC_KEY 27

const float dt = 1.0f / 60.0f;
Platform platform(dt);
// PlatformManager manager("config.txt");

namespace Camera {
    float position[ 3 ] = { 0.0f, 5.0f, -20.0f };
    float target[ 3 ] = { 0.0f, 0.0f, 0.0f };
};

namespace Light {
    float ambient[ 4 ] = { 1.0f, 1.0f, 1.0f, 0.5f };
    float diffuse[ 4 ] = { 0.2f, 0.4f, 0.7f, 1.0f };
    float specular[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Mouse( int button, int state, int x, int y ) {
    if ( state == GLUT_DOWN )
        switch(button)
        {
        case GLUT_LEFT_BUTTON:
            {
            }
            break;
        case GLUT_RIGHT_BUTTON:
            {
            }
            break;
        }
}

void Keyboard(unsigned char key, int x, int y) {
    const float increment = 0.2f;

    switch(key)
    {
    case ESC_KEY:
        exit( 0 );
        break;
    case 'w':
        Camera::position[ 2 ] -= increment;
        Camera::target[ 2 ] -= increment;
        break;
    case 's':
        Camera::position[ 2 ] += increment;
        Camera::target[ 2 ] += increment;
        break;
    case 'a':
        Camera::position[ 0 ] -= increment;
        Camera::target[ 0 ] -= increment;
        break;
    case 'd':
        Camera::position[ 0 ] += increment;
        Camera::target[ 0 ] += increment;
        break;
    case 'q':
        Camera::position[ 1 ] -= increment;
        Camera::target[ 1 ] -= increment;
        break;
    case 'e':
        Camera::position[ 1 ] += increment;
        Camera::target[ 1 ] += increment;
        break;
    }
}

void Reshape( int width, int height ) {
    if ( height <= 0 )
        height = 1;

    f32 aspectRatio = (f32)width / (f32)height;
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective( 45.0f, aspectRatio, 0.1f, 10000.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(
        Camera::position[ 0 ], Camera::position[ 1 ], Camera::position[ 2 ],
        Camera::target[ 0 ], Camera::target[ 1 ], Camera::target[ 2 ],
        0.0f, 1.0f, 0.0f
        );
}

void DisplayFunction( void ) {
    i32 w = glutGet( GLUT_WINDOW_WIDTH );
    i32 h = glutGet( GLUT_WINDOW_HEIGHT );
    Reshape( w, h );
    platform.display();
}

int main( int argc, char** argv ) {
    // Starting width / height of the window
    const u32 kWindowWidth = 1000;
    const u32 kWindowHeight = 600;

    // Initialize GLUT
    glutInit( &argc, argv );

    // Get how big our screen is that we're displaying the window on
    int screenWidth = glutGet( GLUT_SCREEN_WIDTH );
    int screenHeight = glutGet( GLUT_SCREEN_HEIGHT );

    // Initialize the display mode to utilize double buffering, 4-channel framebuffer and depth buffer
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );

    // Setup the window
    glutInitWindowSize( kWindowWidth, kWindowHeight );
    glutInitWindowPosition( (screenWidth - kWindowWidth) / 2, (screenHeight - kWindowHeight) / 2 );
    glutCreateWindow( "3D Runner" );

    glutDisplayFunc( DisplayFunction );
    glutReshapeFunc( Reshape );
    glutKeyboardFunc( Keyboard );
    glutMouseFunc( Mouse );
    glutIdleFunc( DisplayFunction );

    // Setup all the open-gl states we want to use (ones that don't change in the lifetime of the application)
    // Note: These can be changed anywhere, but generally we don't change the back buffer color
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );

    // Show the window that we just initailized
    glutShowWindow( );

    // Used FFP to setup lights
    float floats[ 4 ];
    for ( i32 i = 0; i < 4; ++i )
        floats[ i ] = (float)Light::ambient[ i ];
    glLightfv( GL_LIGHT0, GL_AMBIENT, floats );
    for ( i32 i = 0; i < 4; ++i )
        floats[ i ] = (float)Light::diffuse[ i ];
    glLightfv( GL_LIGHT0, GL_DIFFUSE, floats );
    for ( i32 i = 0; i < 4; ++i )
        floats[ i ] = (float)Light::specular[ i ];
    glLightfv( GL_LIGHT0, GL_SPECULAR, floats );
    for ( i32 i = 0; i < 4; ++i )
        floats[ i ] = (float)Camera::position[ i ];
    glLightfv( GL_LIGHT0, GL_POSITION, floats );
    glEnable( GL_LIGHT0 );
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

    // initialize platform
    // manager.manage(&platform);

    glutMainLoop( );

    return 0;
}


