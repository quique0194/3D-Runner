#ifndef ROAD_H
#define ROAD_H

#include "qu3e/src/q3.h"
#include "./PlatformObject.h"

class Road: public PlatformObject {
    public:
        Road(double _distance = 100): 
            distance(_distance) {

        }

        void genBody(q3Scene& scene, const q3Transform& tx);

    private:
        double distance;           // how long is the road
};

Road::genBody(q3Scene& scene, const q3Transform& tx) {
    q3BodyDef bodyDef;
    q3Body* body = scene.CreateBody( bodyDef );

    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, distance ) );
    body->AddBox( boxDef );
}

#endif
