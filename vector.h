/*
* Ideas to use a vector class like this came from the book
* openGL Game Programming (ISBN# 0761533303), we tweaked this
* to suit our needs
*/

#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>
#include <stdio.h>

typedef float scalar_t;

#define	MIN	0.04

class Vector
{
public:
     scalar_t x;
     scalar_t y;
     scalar_t z;    // x,y,z coordinates

public:
     Vector(scalar_t a = 0, scalar_t b = 0, scalar_t c = 0) : x(a), y(b), z(c) {}
     Vector(const Vector &vec) : x(vec.x), y(vec.y), z(vec.z) {}

     // vector assignment
     const Vector &operator=(const Vector &vec) {
          x = vec.x;
          y = vec.y;
          z = vec.z;
          return *this;
     }

     // vecector equality
     const bool operator==(const Vector &vec) const
     {
          return ((x == vec.x) && (y == vec.y) && (z == vec.z));
     }

	 // vecector equality
     const bool precision_equality(const Vector &vec) const
     {
          return (fabs(x - vec.x)<MIN && fabs(y - vec.y)<MIN && fabs(z - vec.z)<MIN);
     }

     // vecector inequality
     const bool operator!=(const Vector &vec) const
     {
          return !(*this == vec);
     }

     // vector add
     const Vector operator+(const Vector &vec) const
     {
          return Vector(x + vec.x, y + vec.y, z + vec.z);
     }

     // vector add (opposite of negation)
     const Vector operator+() const
     {
          return Vector(*this);
     }

     // vector increment
     const Vector& operator+=(const Vector& vec)
     {    x += vec.x;
          y += vec.y;
          z += vec.z;
          return *this;
     }

     // vector subtraction
     const Vector operator-(const Vector& vec) const
     {
          return Vector(x - vec.x, y - vec.y, z - vec.z);
     }

     // vector negation
     const Vector operator-() const
     {
          return Vector(-x, -y, -z);
     }

     // vector decrement
     const Vector &operator-=(const Vector& vec)
     {
          x -= vec.x;
          y -= vec.y;
          z -= vec.z;

          return *this;
     }

     // scalar self-multiply
     const Vector &operator*=(const scalar_t &s)
     {
          x *= s;
          y *= s;
          z *= s;

          return *this;
     }

     // scalar self-divecide
     const Vector &operator/=(const scalar_t &s)
     {
          const float recip = 1/s; // for speed, one divecision

          x *= recip;
          y *= recip;
          z *= recip;

          return *this;
     }

     // post multiply by scalar
     const Vector operator*(const scalar_t &s) const
     {
          return Vector(x*s, y*s, z*s);
     }

     // pre multiply by scalar
     friend inline const Vector operator*(const scalar_t &s, const Vector &vec)
     {
          return vec*s;
     }

/*   friend inline const Vector operator*(const Vector &vec, const scalar_t &s)
     {
          return Vector(vec.x*s, vec.y*s, vec.z*s);
     }

*/   // divecide by scalar
     const Vector operator/(scalar_t s) const
     {
          s = 1/s;

          return Vector(s*x, s*y, s*z);
     }

     // cross product
     const Vector CrossProduct(const Vector &vec) const
     {
          return Vector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }

     // cross product
     const Vector operator^(const Vector &vec) const
     {
          return Vector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }

     // dot product
     const scalar_t DotProduct(const Vector &vec) const
     {
          return x*vec.x + y*vec.x + z*vec.z;
     }

     // dot product
     const scalar_t operator%(const Vector &vec) const
     {
          return x*vec.x + y*vec.x + z*vec.z;
     }


     // length of vector
     const scalar_t Length() const
     {
		//int xx=1,yy=1,zz=1;
		//if(x<0)
		//	xx=-1;
		//if(y<0)
		//	yy=-1;
		//if(z<0)
		//	zz=-1;
		//xx*yy*zz*

        return (scalar_t)sqrt((double)(x*x + y*y + z*z));
     }

     // return the unit vector
     const Vector UnitVector() const
     {
          return (*this) / Length();
     }

     // normalize this vector
     void Normalize()
     {
          (*this) /= Length();
     }

     const scalar_t operator!() const
     {
          return sqrtf(x*x + y*y + z*z);
     }

     // return vector with specified length
     const Vector operator | (const scalar_t length) const
     {
          return *this * (length / !(*this));
     }

     // set length of vector equal to length
     const Vector& operator |= (const float length)
     {
          return *this = *this | length;
     }

     // return angle between two vectors
     const float inline Angle(const Vector& normal) const
     {
          return acosf(*this % normal);
     }

     // reflect this vector off surface with normal vector
     const Vector inline Reflection(const Vector& normal) const
     {
          const Vector vec(*this | 1);     // normalize this vector
          return (vec - normal * 2.0 * (vec % normal)) * !*this;
     }

};

#endif