/* ---------------------------------------------------------------------------
** This is a binding box that is used to check for collissions
** A bounding box is created around an object.  Each bounding box object
** holds six planes (see plane.cpp).
**
** boundingbox.cpp
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#ifndef __BOX_C_INCLUDED__
#define __BOX_C_INCLUDED__

#include <math.h>
#include <windows.h>                         // standard Windows app include
#include <gl/gl.h>                           // standard OpenGL include
#include <gl/glu.h>
#include <fstream.h>
#include "plane.cpp"
#include "vector.h"

/*
* BoundingBox
*/
class BoundingBox {
	public :
		/*
		* BindingBox Constructor
		*/
		BoundingBox() {
			transx = 0.0f;
			transy = 0.0f;
			transz = 0.0f;
			rotate = 0.0f;
		} // end BindingBox()

		/*
		* Camera Deconstructor
		*/
		~BoundingBox() {
		} // end ~Camera()

		/*
		* This function rotates each of the planes a certain number
		* of degrees
		*/
		void rotatebox( GLfloat deg, Vector norm ) {
			for (int i = 0; i < 6; i++ ) {
				planes[i]->rotateit(deg, norm);
			}
		} // end rotate box

		/*
		* check for a collision
		* this takes in another bounding box and tests to see
		* if this bounding box is intersecting with any other
		* bounding boxes.
		*/
		bool checkCollision( BoundingBox* to_check ) {
	
			// is there a collision
			bool retval = false;

			// calculate max and min values of the box
			to_check->minx += to_check->transx;
			to_check->maxx += to_check->transx;

			to_check->miny += to_check->transy;
			to_check->maxy += to_check->transy;

			to_check->minz += to_check->transz;
			to_check->maxz += to_check->transz;
	
			// loop through each plane
			for (int i = 0; i < 6; i++ ) {
					planes[i]->do_trans();
				// loop through each point in a plane
				for (int j=0; j<4; j++ ) {
					
					// see if the point of any plane is inside
					// any of the other planes
					if ( ((planes[i]->points[j][0] >= to_check->minx) &&
						(planes[i]->points[j][0] <= to_check->maxx)) &&

						((planes[i]->points[j][1] >= to_check->miny) &&
						(planes[i]->points[j][1] <= to_check->maxy)) &&

						((planes[i]->points[j][2] >= to_check->minz) &&
						(planes[i]->points[j][2] <= to_check->maxz))

						) {
						// there has been a collision
						retval = true;

					} // end if
				} // end for
					planes[i]->undo_trans();
			} // end for

			to_check->minx -= to_check->transx;
			to_check->maxx -= to_check->transx;

			to_check->miny -= to_check->transy;
			to_check->maxy -= to_check->transy;

			to_check->minz -= to_check->transz;
			to_check->maxz -= to_check->transz;
			return retval;
		} // end checkCollision

		/*
		* After the bounding box has been created, we pass in
		* an array of verticies, this function creates the bounding box
		* based around those verticies
		*/
		void set_verticies( GLfloat check_verticies[][3] ,long size) {

			minx = check_verticies[0][0];
			maxx = check_verticies[0][0];

			miny = check_verticies[0][1];
			maxy = check_verticies[0][1];

			minz = check_verticies[0][2];
			maxz = check_verticies[0][2];

			// set initial bounding box of size zero
			for (int i = 0; i < 8; i++ ) {
				points[i][0] = check_verticies[0][0];
				points[i][1] = check_verticies[0][1];
				points[i][2] = check_verticies[0][2];
			}

			// loop through each vertex
			for (int j = 0; j < size; j++) {

				// find max and min points of vertex
				if ( check_verticies[j][0] < minx ) {
					minx = check_verticies[j][0];
				}
				if ( check_verticies[j][0] > maxx) {
					maxx = check_verticies[j][0];
				}
				if ( check_verticies[j][1] < miny ) {
					miny = check_verticies[j][1];
				}
				if ( check_verticies[j][1] > maxy) {
					maxy = check_verticies[j][1];
				}
				if ( check_verticies[j][2] < minz ) {
					minz = check_verticies[j][2];
				}
				if ( check_verticies[j][2] > maxz) {
					maxz = check_verticies[j][2];
				}

				// point 1
				if ( check_verticies[j][0] < points[0][0] ) {
					points[0][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] < points[0][1] ) {
					points[0][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] > points[0][2] ) {
					points[0][2] = check_verticies[j][2];
				}

				// point 2
				if ( check_verticies[j][0] > points[1][0] ) {
					points[1][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] < points[1][1] ) {
					points[1][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] > points[1][2] ) {
					points[1][2] = check_verticies[j][2];
				}

				// point 3
				if ( check_verticies[j][0] > points[2][0] ) {
					points[2][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] < points[2][1] ) {
					points[2][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] < points[2][2] ) {
					points[2][2] = check_verticies[j][2];
				}

				// point 4
				if ( check_verticies[j][0] < points[3][0] ) {
					points[3][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] < points[3][1] ) {
					points[3][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] < points[3][2] ) {
					points[3][2] = check_verticies[j][2];
				}

				// point 5
				if ( check_verticies[j][0] < points[4][0] ) {
					points[4][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] > points[4][1] ) {
					points[4][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] > points[4][2] ) {
					points[4][2] = check_verticies[j][2];
				}

				// point 6
				if ( check_verticies[j][0] > points[5][0] ) {
					points[5][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] > points[5][1] ) {
					points[5][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] > points[5][2] ) {
					points[5][2] = check_verticies[j][2];
				}

				// point 7
				if ( check_verticies[j][0] > points[6][0] ) {
					points[6][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] > points[6][1] ) {
					points[6][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] < points[6][2] ) {
					points[6][2] = check_verticies[j][2];
				}

				// point 8
				if ( check_verticies[j][0] < points[7][0] ) {
					points[7][0] = check_verticies[j][0];
				}
				if ( check_verticies[j][1] > points[7][1] ) {
					points[7][1] = check_verticies[j][1];
				}
				if (check_verticies[j][2] < points[7][2] ) {
					points[7][2] = check_verticies[j][2];
				}

				// create 6 plane objects, one for each side of box
				planes[0] = new Plane(points[1],points[5],points[6],points[2]);
				planes[1] = new Plane(points[2],points[6],points[7],points[3]);
				planes[2] = new Plane(points[0],points[4],points[7],points[3]);
				planes[3] = new Plane(points[0],points[1],points[5],points[4]);
				planes[4] = new Plane(points[4],points[5],points[6],points[7]);
				planes[5] = new Plane(points[0],points[1],points[2],points[3]);
			}
		} // end set verticies

		/*
		* translate
		* this moves the bounding box to a certain position in world
		* coordinates
		*/
		void translate( GLfloat x, GLfloat y, GLfloat z ) {

			transx = x;
			transy = y;
			transz = z;

			// add translation value to each point in bounding box
			for (int i = 0; i < 6; i++ ) {
				planes[i]->translate(x, y, z);
			}
		} // end translate

		/*
		* Draw
		* used to draw the bounding box, only used for testing
		*/
		void Draw() {
			/*
			glDisable(GL_TEXTURE_2D );
			glDisable( GL_LIGHTING );

			glRotatef(90,1,0,0);
			glTranslatef(transx, transy, transz );
			for (int i = 0; i < 6; i++ ) {
				planes[i]->Draw();
			}

			glEnable( GL_LIGHTING );
			glEnable( GL_TEXTURE_2D );
			*/
		} // end draw

	public:
		GLfloat points[8][3];	// holder for temporarary points of the plane
		Plane* planes[6];		// holder of 6 plane objects

		GLfloat rotate;		// amount box has been rotated

		// position of box in the world
		GLfloat transx;
		GLfloat transy;
		GLfloat transz;

		// min and max values of the box
		GLfloat minx;
		GLfloat maxx;

		GLfloat miny;
		GLfloat maxy;

		GLfloat minz;
		GLfloat maxz;
}; // end Car class
#endif
