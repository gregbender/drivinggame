/* ---------------------------------------------------------------------------
** This is a single plane
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#ifndef __PLANE_C_INCLUDED__
#define __PLANE_C_INCLUDED__

#include <math.h>
#include <windows.h>                         // standard Windows app include
#include <gl/gl.h>                           // standard OpenGL include
#include <gl/glu.h>
#include <fstream.h>
#include "vector.h"

/*
* BoundingBox
*/
class Plane {
	public :
		/*
		* Plane Constructor
		*/
		Plane(GLfloat one[3], GLfloat two[3], GLfloat three[3], GLfloat four[3]):
			angle(0)
		{
			points[0] = one;
			points[1] = two;
			points[2] = three;
			points[3] = four;

			angles[0] = (float)atan(points[0][0]/points[0][2]);
			angles[1] = (float)atan(points[1][0]/points[1][2]);
			angles[2] = (float)atan(points[2][0]/points[2][2]);
			angles[3] = (float)atan(points[3][0]/points[3][2]);

			for(int i=0;i<4;i++)
			{
				if(points[i][2]<0)
				{
					angles[i]+=4*(float)atan(1.0f);
				}
			}

			transx = 0.0f;
			transy = 0.0f;
			transz = 0.0f;
		} // end Plane()

		/*
		* Plane Deconstructor
		*/
		~Plane() {
		} // end ~Plane()


		void rotateit( GLfloat deg, Vector norm ) {
			GLfloat calculated_angle = deg * (3.14f / 180.0f);
			//angle+=calculated_angle;

			//calculated_angle=angle;
				
			for (int i = 0; i < 4; i++ ) {

				Vector testVec = Vector( points[i][0], 0.0f, points[i][2] );
				
				GLfloat xmodifier = 1.0f;
				GLfloat zmodifier = 1.0f;

				if ( points[i][0] < 0.0f ) {
					//xmodifier = -1.0f;
				}
				if (points[i][2] < 0.0f ) {
					//zmodifier = -1.0f;
				}		

				testVec = Vector(xmodifier * (testVec.Length() * (float)sin( calculated_angle+angles[i] )), 0.0f, zmodifier * (testVec.Length() * (float)cos( calculated_angle+angles[i] )));

				points[i][0] = testVec.x;
				//points[i][1] = 1;
				points[i][2] = testVec.z;

			}	
	
		} // end rotate

		void Draw() {
			glBegin(GL_LINE_STRIP);
			glColor3f(1.0f, 1.0f, 1.0f);
			for (int i = 0; i < 4; i++ ) {
				glVertex3f( points[i][0], points[i][1], points[i][2] ); 
			}
				glVertex3f( points[0][0], points[0][1], points[0][2] ); 
			glEnd();
		}

		void do_trans() {
			for (int i = 0; i < 4; i++ ) {
				points[i][0] += transx;
				points[i][1] += transy;
				points[i][2] += transz;
			}
		}

		void undo_trans() {
			for (int i = 0; i < 4; i++ ) {
				points[i][0] -= transx;
				points[i][1] -= transy;
				points[i][2] -= transz;
			}
		}

		void translate( GLfloat x, GLfloat y, GLfloat z ) {
			transx = x;
			transy = y;
			transz = z;
		} // end translate

	public:
		GLfloat rotate;
		GLfloat* points[4];
		GLfloat transx;
		GLfloat transy;
		GLfloat transz;
	private:
		GLfloat angle;
		GLfloat angles[4];

}; // end Car class
#endif
