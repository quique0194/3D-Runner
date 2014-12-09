#ifndef PLATFORM_OBJECT_H
#define PLATFORM_OBJECT_H

#include "lib/qu3e/src/q3.h"
#include "constants.h"

class PlatformObject {
    public:
        PlatformObject(int _body_type = TYPE_OTHER, int _value=0):
            body_type(_body_type),
            value(_value) {

        }

        virtual void display() = 0;
        virtual void genBody(q3Scene& scene) = 0;
        int body_type;
        q3Body* body;
        int value;
};

#endif
