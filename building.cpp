/* ---------------------------------------------------------------------------
** Building Object
**
** Building.cpp
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#ifndef __BUILDING_C_INCLUDED__
#define __BUILDING_C_INCLUDED__

// standard includes
#include "object.h"



// include wheel object that this car contains
#include <iostream.h>
#include <fstream.h>

/*
* Car object, represents all aspects of a car in the 3D world.
*/
class Building :public Object {
	public :

		/*
		* Car constructor
		*/
		Building() {

			box = new BoundingBox();

		
		} // end Building()

		/*
		* Building
		*/

		~Building() {
			glDeleteLists(list, 1);
			
		} // end ~Car()


		BoundingBox* get_box() {
			return box;
		}

		/*
		* Called from main to set what this cars display lists will represent
		*/
		void set_display_lists(GLint building) {

			list = building;
		}  // end set_display_lists()



	void Draw() {

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);		
		

		glPushMatrix();
			box->translate(x, (box->maxy - box->miny)/2, y);
			//box->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(x, (box->maxy - box->miny)/2 - 0.2f, y);
			glRotatef(90.0f * orientation, 0.0f, 1.0f, 0.0f);
			glCallList(list);

		glPopMatrix();

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

	} // end Draw()


	void Animate( scalar_t deltaTime) {


	} // end Animate()

	public:
		float x;
		float y;
		int type;
		int orientation;
		GLint list;		// Buildings Display List

}; // end Car class
#endif