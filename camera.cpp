/* ---------------------------------------------------------------------------
** This is a camera object.  This is used to focus on the
** users car.
**
** camera.cpp
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#ifndef __CAMERA_C_INCLUDED__
#define __CAMERA_C_INCLUDED__

// standard includes
#include "object.h"

/*
* Camera object, controls how 3d world will look
*/
class Camera : public Object {
	public :
		/*
		* Camera constructor
		*/
		Camera() {
			//position = Vector( 

			position = Vector( 0.0f, 3.0f, -3.0f );
			velocity = Vector( 0.0f, 0.0f, 0.0f );
			acceleration = Vector (0.0f, 0.0f, 0.0f );

			go_to = Vector (0.0f, 3.0f, -3.0f );

			lookat_position = Vector ( 0.0f, 0.0f, 0.0f );
		    lookat_velocity = Vector (0.0f, 0.0f, 0.0f );
		    lookat_acceleration = Vector (0.0f, 0.0f, 0.0f );

			predefined_camera[0] = Vector( 0.0f, 1.0f, -3.0f );
			predefined_camera[1] = Vector( 0.0f, 1.0f, -3.0f );
			predefined_camera[2] = Vector( -1.0f, 3.0f, -3.0f );
			predefined_camera[3] = Vector( 1.0f, 3.0f, -3.0f );
			predefined_camera[4] = Vector( -1.0f, 3.0f, 0.0f );
			predefined_camera[5] = Vector( 1.0f, 3.0f, 0.0f );
			predefined_camera[6] = Vector( 1.0f, 3.0f, 0.0f );
			predefined_camera[7] = Vector( -1.0f, 3.0f, 3.0f );
			predefined_camera[8] = Vector( 1.0f, 3.0f, 3.0f );
			predefined_camera[9] = Vector( 1.0f, 3.0f, 3.0f );




		} // end Camera()

		/*
		* Camera Deconstructor
		*/
		~Camera() {

		} // end ~Camera()

		/*
		* use a predefined camera position
		*/
		void use_predefined_camera( int ident ) {
			PositionAt(predefined_camera[ident]);
		} // end use_predefined camera

		/*
		* Where this camera should start pointing
		*/
		void PointAt(Vector vec) {
			lookat_position = vec;
		} // end PointAt()

		/*
		* where this camera should be put now
		*/
		void PositionAtNow( Vector vec ) {
			position = vec;
			/*
			//float angle_rad = (car_angle)*3.14f/180.0f;
			//position = vec+Vector((go_to.z+go_to.x)*sin(angle_rad),go_to.y,(go_to.z+go_to.x)*cos(angle_rad));
			//go_to = vec;
			//acceleration = Vector( 0.0f, 0.0f, 0.0f);
			//velocity = Vector( 0.0f, 0.0f, 0.0f);
			//acceleration = Vector( 0.0f, 0.0f, 0.0f);
			//velocity = Vector( 0.0f, 0.0f, 0.0f);			
			*/
		} // end PositionAtNow

		/*
		* Where this camera should be positioned eventually
		*/
		void PositionAt( Vector vec ) {
			go_to = vec;
			//acceleration = Vector( 0.0f, 0.0f, 0.0f);
			//velocity = Vector( 0.0f, 0.0f, 0.0f);
		} // end PositionAt()


		/*
		* this places the camera
		*/
		void Draw() {
	
			gluLookAt( position.x, position.y, position.z, 
						lookat_position.x, lookat_position.y, lookat_position.z, 
							0.0f, 1.0f, 0.0f);

		} // end Draw

		void stop() {
			acceleration = -acceleration;
			velocity = -velocity;
		}

		/*
		* this animates the camera
		*/
		void Animate( scalar_t deltaTime ) {
			float fastestTime = deltaTime;

			acceleration = -(position);

			if ( (acceleration.Length() <= 0.15)) {
				acceleration = Vector( 0.0f, 0.0f, 0.0f);
				velocity = Vector( 0.0f, 0.0f, 0.0f);
			}
			else {
				velocity += acceleration * fastestTime;
				position += velocity * fastestTime + 
								acceleration * (fastestTime * fastestTime * 0.5f);
			}

		} // end Animate


		Vector* getGo(){
			return &go_to;
		}



		GLfloat car_angle;
	private:
		Vector lookat_position;
		Vector lookat_velocity;
		Vector lookat_acceleration;

		Vector point_at;	// where the camera should be gradually pointed to
		Vector go_to;		// where the camera should be gradually moved to
	
		Vector predefined_camera[10];

}; // end Car class
#endif
