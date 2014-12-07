#ifndef PLATFORM_OBJECT_H
#define PLATFORM_OBJECT_H

#include "lib/qu3e/src/q3.h"

class PlatformObject {
    public:
        PlatformObject();
        virtual ~PlatformObject();
        virtual void display() = 0;
        virtual void genBody(q3Scene& scene) = 0;
    protected:
        q3Body* body;
};

PlatformObject::PlatformObject() {

}

#endif
