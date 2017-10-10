/* ---------------------------------------------------------------------------
** This is a generic object class.  There are several properities that will
** be inherited from this class.  For example, all cars, the camera, and
** anything else in the world will be derived from this Object class.
** The idea for creating this class came from page 665 of the openGL
** game programming book.
**
** object.h
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/

#ifndef __OBJECT_H
#define __OBJECT_H

#include "vector.h"
#include <windows.h>                         // standard Windows app include
#include <gl/gl.h>                           // standard OpenGL include
#include <gl/glu.h>
#include "boundingbox.cpp"

class Object
{
public:
     Vector position;         // position of object
     Vector velocity;         // velocity of object
     Vector acceleration;     // acceleration of object
	 BoundingBox* box;
     scalar_t size;           // size of bounding sphere

public:
     Object() {};            // constructor
     ~Object() {};           // destructor

     virtual void Draw() = 0;      // draw object

     // animate object (physics calculations)
     virtual void Animate(scalar_t deltaTime) = 0;
};


#endif