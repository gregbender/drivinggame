

	//float li[4]={1-(fabs(handler->getWorld()->time_of_day-12)/12),1-(fabs(handler->getWorld()->time_of_day-12)/12),1-(fabs(handler->getWorld()->time_of_day-12)/12),1.0};
	float li[4]={1,1,1,1};

	// init road
	road_display_list0 = glGenLists(1);

    glNewList(road_display_list0, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road0.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);
		//glGenTextures(1, &road_texture);
		//glBindTexture(GL_TEXTURE_2D, road_texture);


		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list1 = glGenLists(1);

    glNewList(road_display_list1, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road1.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list2 = glGenLists(1);

    glNewList(road_display_list2, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road2.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);


		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list3 = glGenLists(1);

    glNewList(road_display_list3, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road3.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list4 = glGenLists(1);

    glNewList(road_display_list4, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road4.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list5 = glGenLists(1);

    glNewList(road_display_list5, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road5.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list6 = glGenLists(1);

    glNewList(road_display_list6, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road6.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list7 = glGenLists(1);

    glNewList(road_display_list7, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road7.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list8 = glGenLists(1);

    glNewList(road_display_list8, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road8.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list9 = glGenLists(1);

    glNewList(road_display_list9, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road9.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list10 = glGenLists(1);

    glNewList(road_display_list10, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road10.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list11 = glGenLists(1);

    glNewList(road_display_list11, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road11.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list12 = glGenLists(1);

    glNewList(road_display_list12, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road12.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list13 = glGenLists(1);

    glNewList(road_display_list13, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road13.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();



	//***********************************************************
	road_display_list14 = glGenLists(1);

    glNewList(road_display_list14, GL_COMPILE);

		road_texture = LoadTextureRAW("textures/road14.raw", 0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,li);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,li);
		glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,1.0f);

		glBegin (GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);

			glTexCoord3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

		glEnd ();
    glEndList();
