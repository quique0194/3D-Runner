#ifndef RENDERER_H
#define RENDERER_H

#include "lib/qu3e/src/q3.h"


class Renderer : public q3Render
{
public:
    void SetPenColor( f32 r, f32 g, f32 b, f32 a = 1.0f ) override
    {
        Q3_UNUSED( a );

        glColor3f( (float)r, (float)g, (float)b );
    }

    void SetPenPosition( f32 x, f32 y, f32 z ) override
    {
        x_ = x, y_ = y, z_ = z;
    }

    void SetScale( f32 sx, f32 sy, f32 sz ) override
    {
        glPointSize( (float)sx );
        sx_ = sx, sy_ = sy, sz_ = sz;
    }

    void Line( f32 x, f32 y, f32 z ) override
    {
        glBegin( GL_LINES );
        glVertex3f( (float)x_, (float)y_, (float)z_ );
        glVertex3f( (float)x, (float)y, (float)z );
        SetPenPosition( x, y, z );
        glEnd( );
    }

    void Triangle(
        f32 x1, f32 y1, f32 z1,
        f32 x2, f32 y2, f32 z2,
        f32 x3, f32 y3, f32 z3
        ) override
    {
        glBegin( GL_TRIANGLES );
        glColor4f( 0.2f, 0.4f, 0.7f, 0.5f );
        glVertex3f( (float)x1, (float)y1, (float)z1 );
        glVertex3f( (float)x2, (float)y2, (float)z2 );
        glVertex3f( (float)x3, (float)y3, (float)z3 );
        glEnd( );
    }

    void SetTriNormal( f32 x, f32 y, f32 z ) override
    {
        glNormal3f( (float)x, (float)y, (float)z );
    }

    void Point( ) override
    {
        glBegin( GL_POINTS );
        glVertex3f( (float)x_, (float)y_, (float)z_ );
        glEnd( );
    };

private:
    f32 x_, y_, z_;
    f32 sx_, sy_, sz_;
};

#endif