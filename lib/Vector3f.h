#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>
#include <GL/glut.h>

class Vector3f {
    public:
        Vector3f(GLfloat x=0, GLfloat y=0, GLfloat z=0) {
            setData(x, y, z);
        }
        Vector3f(GLfloat* _data) {
        	setData(_data);
        }
        Vector3f operator-(const Vector3f& v) const;
        Vector3f operator+(const Vector3f& v) const;
        Vector3f operator*(const Vector3f& v) const;
        GLfloat operator[](unsigned int i) const;
        GLfloat& operator[](unsigned int i);
        Vector3f product(const Vector3f& v) const;
        GLfloat length() const;
        Vector3f normalize() const;
        void setData(GLfloat x, GLfloat y, GLfloat z);
        void setData(GLfloat* newData);
        void print();
    private:
        GLfloat data[3];
};


Vector3f Vector3f::operator-(const Vector3f& v) const {
    Vector3f ret;
    for (int i = 0; i < 3; ++i) {
        ret.data[i] = data[i] - v.data[i];
    }
    return ret;
}

Vector3f Vector3f::operator+(const Vector3f& v) const {
    Vector3f ret;
    for (int i = 0; i < 3; ++i) {
        ret.data[i] = data[i] + v.data[i];
    }
    return ret;
}

Vector3f Vector3f::operator*(const Vector3f& v) const {
    return product(v);
}

GLfloat Vector3f::operator[](unsigned int i) const {
    return data[i];
}

GLfloat& Vector3f::operator[](unsigned int i) {
    return data[i];
}

Vector3f Vector3f::product(const Vector3f& v) const {
    Vector3f ret;
    ret.data[0] = data[1]*v.data[2] - data[2]*v.data[1];
    ret.data[1] = data[2]*v.data[0] - data[0]*v.data[2];
    ret.data[2] = data[0]*v.data[1] - data[1]*v.data[0];
    return ret;
}

GLfloat Vector3f::length() const {
    return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}

Vector3f Vector3f::normalize() const {
    Vector3f ret;
    GLfloat l = length();
    for (int i = 0; i < 3; ++i) {
        ret.data[i] = data[i]/l;
    }
    return ret;
}

void Vector3f::setData(GLfloat x, GLfloat y, GLfloat z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

void Vector3f::setData(GLfloat* newData) {
    data[0] = newData[0];
    data[1] = newData[1];
    data[2] = newData[2];
}

void Vector3f::print() {
    for (int i = 0; i < 3; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

#endif
