/*
 *	SAXMapHandler core
 *	
 *	Description:
 *		Holds function implementation for SAXMapHandler member functions
 *		Functions are primarily event handlers
 *
 *	Authors:
 *		Michael D. Krauklis
 *	Contributors:
 *		none
 *
 */
#include "SAXMapHandler.hpp"

/*
 *	Name:
 *		SAXMapHandler
 *
 *	Description:
 *		constructor, initializes all member variables
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		void
 *
 */
SAXMapHandler::SAXMapHandler():
	cars(null),buildings(null),roads(null),heights(null),
	ctail(null),btail(null),rtail(null),htail(null),the_world(null),
	b(false),c(false),r(false),h(false),e(false),rend(false),
	parser(null)
{
}

	
/*
 *	Name:
 *		~SAXMapHandler
 *
 *	Description:
 *		Descructor, goes through linked lists and frees all allocated memory
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		void
 *
 */
SAXMapHandler::~SAXMapHandler(){
	//free up cars linked list
	Car *tempc=null;
	while(cars!=null)
	{
		tempc=cars->next;
		delete cars;
		cars=tempc;
	}
	//free up buildings linked list
	Building *tempb=null;
	while(buildings!=null)
	{
		tempb=buildings->next;
		delete buildings;
		buildings=tempb;
	}
	//free up roads linked list
	Road *tempr=null;
	while(roads!=null)
	{
		tempr=roads->next;
		delete roads;
		roads=tempr;
	}
	//free heights linked list
	Height *temph=null;
	while(heights!=null)
	{
		temph=heights->next;
		delete heights;
		heights=temph;
	}
	//delete the_world structure
	delete the_world;
}


/*
 *	Name:
 *		getBuildings
 *
 *	Description:
 *		returns the head pointer to the Buildings linked list
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		Building*, head of Buildings linked list
 *
 */
SAXMapHandler::Building* SAXMapHandler::getBuildings()
{
	return buildings;
}


/*
 *	Name:
 *		getCars
 *
 *	Description:
 *		returns the head pointer to the Cars linked list
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		Car*, head of Cars linked list
 *
 */
SAXMapHandler::Car* SAXMapHandler::getCars()
{
	return cars;
}


/*
 *	Name:
 *		getRoads
 *
 *	Description:
 *		returns the head pointer to the Roads linked list
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		Road*, head of Roads linked list
 *
 */
SAXMapHandler::Road* SAXMapHandler::getRoads()
{
	return roads;
}


/*
 *	Name:
 *		getHeights
 *
 *	Description:
 *		returns the head pointer to the Heights linked list
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		Height*, head of Heights linked list
 *
 */
SAXMapHandler::Height* SAXMapHandler::getHeights()
{
	return heights;
}


/*
 *	Name:
 *		getWorld
 *
 *	Description:
 *		returns the pointer to the World structure
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		World*, pointer to World structure
 *
 */
SAXMapHandler::World* SAXMapHandler::getWorld()
{
	return the_world;
}



/*
 *	Name:
 *		copyRoad
 *
 *	Description:
 *		pointer to the new coppied Road structure
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		Road*, pointer to new structure
 *
 */
SAXMapHandler::Road* SAXMapHandler::copyRoad(SAXMapHandler::Road* r)
{
	//create new Road structure
	Road *retval=new Road;

	//copy values
	retval->next=null;
	retval->type=r->type;
	retval->x=r->x;
	retval->y=r->y;

	//return the new road
	return retval;
}



/*
 *	Name:
 *		executeParse
 *
 *	Description:
 *		executes a parse which will in tern create an internal structure representation
 *		of the given xml document, world.xml
 *
 *	Params:
 *		char*	systemid	string representing file name or URI of xml document to be parsed
 *
 *	Returns:
 *		int value representing status
 *		0	success
 *		1	failure
 *
 */
int SAXMapHandler::executeParse(char* systemid){

	// Initialize the XML4C2 system
    try
    {
        XMLPlatformUtils::Initialize();
    }

    catch (const XMLException& toCatch)
    {
        cerr << "Error during initialization! Message:\n"
            << toCatch.getMessage() << endl;
        return 1;
    }


	try
	{
		//SchemaValidator *validator = new SchemaValidator();
		//parser = new SAXParser(validator);
		//parser->setDoSchema(true);

		//create new parser
		parser = new SAXParser();
		//set it up to do namespaces, although this isn't that important given that schema
		//validation isn't working anyway
		parser->setDoNamespaces(true);

		//grrr, schema validation still not working
		//parser->setValidationScheme(SAXParser::Val_Always);

		//this doesn't work...
		parser->setValidationSchemaFullChecking(true);
		//this doesn't work either... wierd!
		parser->setExternalSchemaLocation("world.xsd");

		//not supported in C++, only Java API, grrrrrrr!!!!
		//parser->setFeature("http://xml.org/sax/features/validation ", true);

		//set the document handler and the error handler to... THIS object:)
		parser->setDocumentHandler(this);
		parser->setErrorHandler(this);


		//parse and output time(although in our project there is no standard output)
		cout<<"--Parsing--"<<endl;
		const unsigned long startMillis = XMLPlatformUtils::getCurrentMillis();
        parser->parse(systemid);
        const unsigned long endMillis = XMLPlatformUtils::getCurrentMillis();
		cout<<endl<<endl<<"Parse duration:  "<<(endMillis - startMillis)<<"ms."<<endl;
	}
	catch (SAXMapException *e)
	{
		cerr<<e->getMessage()<<endl;
		return 1;
	}
	catch (const XMLException& toCatch)
    {
        cerr << "Error during parsing! Message:\n"<< toCatch.getMessage() << endl;
        return 1;
    }
	catch (SAXException *e)
	{
		cerr<<e->getMessage()<<endl;
	}
	catch(...)
	{
		cerr<<"unidentified exception"<<endl;
		return 1;
	}

	//kill the parser, but not the handler
	delete parser;

	//close the XML4C2 system
	XMLPlatformUtils::Terminate();

	return 0;

}


// -----------------------------------------------------------------------
//  Handlers for the SAX DocumentHandler interface
// -----------------------------------------------------------------------


/*
 *	Name:
 *		startElement
 *
 *	Description:
 *		called at the start tag of each element <tag>
 *
 *	Params:
 *		XMLCh*	name	constant XMLCh string representing the name of the element
 *		AttributeList&	attributes	reference to an attribute list corelating to the
 *									given element
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::startElement(const XMLCh* const name, AttributeList& attributes){
	
	//if OUT_NAME is defined output the starting tag to standard output
	#if defined(OUT_NAME)
		cout<<"<"<<XMLString::transcode(name);
	#endif


	// **********************************************
	// world element
	// **********************************************
	if(strcmp("world",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world!=null)
		{
			throw new SAXMapException("Parse Error: World element occurs more than once.");
		}
		//create a new world!
		the_world = new World;
		//cycle through attributes
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("x",name)==0)
			{
				the_world->x=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else if(strcmp("y",name)==0)
			{
				the_world->y=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else
			{
				throw new SAXMapException("Parse Error: invalid-argument for world element");
			}
		}

	}
	// **********************************************
	// time element
	// **********************************************
	else if(strcmp("time",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!rend)
		{
			throw new SAXMapException("Parse Error: time element must be a child of rendering element");
		}
		//should be one
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("time_of_day",name)==0)
			{
				the_world->time_of_day=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for time element");
			}
		}
	}
	// **********************************************
	// roads element
	// **********************************************
	else if(strcmp("roads",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!e)
		{
			throw new SAXMapException("Parse Error: roads element must be a child of entities element");
		}
		r=true;
	}
	// **********************************************
	// road element
	// **********************************************
	else if(strcmp("road",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!r)
		{
			throw new SAXMapException("Parse Error: road element must be a child of roads element");
		}
		Road *temp=new Road;
		temp->next=null;
		temp->type=0;
		temp->x=0;
		temp->y=0;
//		temp->orientation=0;
//		temp->span=1;

		int spanx=0;
		int spany=0;

		if(roads==null)
		{
			roads = temp;
			rtail = roads;
		}
		else
		{
			rtail->next = temp;
			rtail = rtail->next;
		}
				
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("type",name)==0)
			{
				rtail->type=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else if(strcmp("x",name)==0)
			{
				rtail->x=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("y",name)==0)
			{
				rtail->y=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("spanx",name)==0)
			{
				spanx=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("spany",name)==0)
			{
				spany=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for road element");
			}
		}
		num_roads++;

		//code for creating a rectangle of roads (for highway use)
		if(spanx!=0||spany!=0)
		{
			Road *rt=rtail;
			if(spanx>=0)
			{
				if(spany>=0)
				{
					for(int x=spanx;x>=0;x--)
					{
						for(int y=spany;y>=0;y--)
						{
							if(x!=0||y!=0)
							{
								rtail->next=copyRoad(rt);
								rtail=rtail->next;
								rtail->x+=x;
								rtail->y+=y;
								num_roads++;
							}
						}
					}
				}
				else
				{
					for(int x=spanx;x>=0;x--)
					{
						for(int y=spany;y<=0;y++)
						{
							if(x!=0||y!=0)
							{
								rtail->next=copyRoad(rt);
								rtail=rtail->next;
								rtail->x+=x;
								rtail->y+=y;
								num_roads++;
							}
						}
					}
				}
			}
			else
			{
				if(spany>=0)
				{
					for(int x=spanx;x<=0;x++)
					{
						for(int y=spany;y>=0;y--)
						{		
							if(x!=0||y!=0)
							{
								rtail->next=copyRoad(rt);
								rtail=rtail->next;
								rtail->x+=x;
								rtail->y+=y;
								num_roads++;
							}
						}
					}
				}
				else
				{
					for(int x=spanx;x<=0;x++)
					{
						for(int y=spany;y<=0;y++)
						{	
							if(x!=0||y!=0)
							{
								rtail->next=copyRoad(rt);
								rtail=rtail->next;
								rtail->x+=x;
								rtail->y+=y;
								num_roads++;
							}
						}
					}
				}
			}
		}

		//old code that used orientation, could only create a line, not a plane
		/*if(rtail->span!=1){
			Road *rt=rtail;
			if(rt->orientation==0)
			{
				for(int i=1;i<rt->span;i++)
				{
					rtail->next=copyRoad(rt);
					rtail=rtail->next;
					rtail->x+=i;
					num_roads++;
				}
			}
			else if(rt->orientation==1)
			{
				for(int i=1;i<rt->span;i++)
				{
					rtail->next=copyRoad(rt);
					rtail=rtail->next;
					rtail->y-=i;
					num_roads++;
				}
			}
			else if(rt->orientation==2)
			{
				for(int i=1;i<rt->span;i++)
				{
					rtail->next=copyRoad(rt);
					rtail=rtail->next;
					rtail->x-=i;
					num_roads++;
				}
			}
			else
			{
				for(int i=1;i<rt->span;i++)
				{
					rtail->next=copyRoad(rt);
					rtail=rtail->next;
					rtail->y+=i;
					num_roads++;
				}
			}
		}*/
	}
	// **********************************************
	// rendering element
	// **********************************************
	else if(strcmp("rendering",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		rend=true;
	}
	// **********************************************
	// physics element
	// **********************************************
	else if(strcmp("physics",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!rend)
		{
			throw new SAXMapException("Parse Error: physics element must be a child of rendering element");
		}		
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("gravity",name)==0)
			{
				the_world->gravity=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else if(strcmp("friction",name)==0)
			{
				the_world->friction=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for physics element");
			}
		}
	}
	// **********************************************
	// heights element
	// **********************************************
	else if(strcmp("heights",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		h=true;
	}
	// **********************************************
	// height element
	// **********************************************
	else if(strcmp("height",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!h)
		{
			throw new SAXMapException("Parse Error: height element must be a child of heights element");
		}
		Height *temp=new Height;
		temp->height=0;
		temp->next=null;
		temp->orientation=0;
		temp->span=0;
		temp->x=0;
		temp->y=0;

		if(heights==null)
		{
			heights = temp;
			htail = heights;
		}
		else
		{
			htail->next = temp;
			htail = htail->next;
		}

		htail->span=0;
				
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("height",name)==0)
			{
				htail->height=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else if(strcmp("x",name)==0)
			{
				htail->x=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("y",name)==0)
			{
				htail->y=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("orientation",name)==0)
			{
				htail->orientation=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("span",name)==0)
			{
				htail->span=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for height element");
			}
		}
	}
	// **********************************************
	// fog element
	// **********************************************
	else if(strcmp("fog",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!rend)
		{
			throw new SAXMapException("Parse Error: fog element must be a child of rendering element");
		}		
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("viscosity",name)==0)
			{
				the_world->fog_viscosity=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for fog element");
			}
		}
	}
	// **********************************************
	// entities element
	// **********************************************
	else if(strcmp("entities",XMLString::transcode(name))==0)
	{
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		e=true;
	}
	// **********************************************
	// distance element
	// **********************************************
	else if(strcmp("distance",XMLString::transcode(name))==0)
	{
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		if(!rend)
		{
			throw new SAXMapException("Parse Error: distance element must be a child of rendering element");
		}		
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("rendering_distance",name)==0)
			{
				the_world->rendering_distance=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for distance element");
			}
		}
	}
	// **********************************************
	// comment element
	// **********************************************
	else if(strcmp("comment",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
	}
	// **********************************************
	// cars element
	// **********************************************
	else if(strcmp("cars",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!e)
		{
			throw new SAXMapException("Parse Error: cars element must be a child of entities element");
		}
		c=true;
	}
	// **********************************************
	// car element
	// **********************************************
	else if(strcmp("car",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!c)
		{
			throw new SAXMapException("Parse Error: car element must be a child of cars element");
		}
		Car *temp = new Car;
		temp->next=null;
		temp->orientation=0;
		temp->type=0;
		temp->x=0;
		temp->y=0;

		if(cars==null)
		{
			cars = temp;
			ctail = cars;
		}
		else
		{
			ctail->next = temp;
			ctail = ctail->next;
		}
				
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("type",name)==0)
			{
				ctail->type=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else if(strcmp("x",name)==0)
			{
				ctail->x=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("y",name)==0)
			{
				ctail->y=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("orientation",name)==0)
			{
				ctail->orientation=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for car element");
			}
		}
		num_cars++;
	}
	// **********************************************
	// buildings element
	// **********************************************
	else if(strcmp("buildings",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!e)
		{
			throw new SAXMapException("Parse Error: buildings element must be a child of entities element");
		}
		b=true;
	}
	// **********************************************
	// building element
	// **********************************************
	else if(strcmp("building",XMLString::transcode(name))==0)
	{
		//internal hard coded validation
		if(the_world==null)
		{
			throw new SAXMapException("Parse Error: start element must be a world element");
		}
		//internal hard coded validation
		if(!b)
		{
			throw new SAXMapException("Parse Error: building element must be a child of buildings element");
		}
		Building *temp = new Building;
		temp->next=null;
		temp->orientation=0;
		temp->x=0;
		temp->y=0;

		if(buildings==null)
		{
			buildings = temp;
			btail = buildings;
		}
		else
		{
			btail->next = temp;
			btail = btail->next;
		}
				
		unsigned int length = attributes.getLength();
		for(unsigned int i=0;i<length;i++)
		{
			char* name = XMLString::transcode(attributes.getName(i));

			#if defined(OUT_NAME)
			OUT_NAME
			#endif

			if(strcmp("type",name)==0)
			{
				btail->type=atoi(XMLString::transcode(attributes.getValue(i)));
			}
			else if(strcmp("x",name)==0)
			{
				btail->x=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("y",name)==0)
			{
				btail->y=atoi(XMLString::transcode(attributes.getValue(i)));
			}	
			else if(strcmp("orientation",name)==0)
			{
				btail->orientation=atoi(XMLString::transcode(attributes.getValue(i)));
			}			
			else
			{
				throw new SAXMapException("Parse Error: invalid-attribute for building element");
			}
		}
		num_buildings++;
	}
	// **********************************************
	// invalid element
	// **********************************************
	else
	{
		throw new SAXMapException("Parse Error: unrecognized element");
	}
	#if defined(OUT_NAME)
		cout<<">";
	#endif
}

/*
 *	Name:
 *		endElement
 *
 *	Description:
 *		called at the end tag of each element </tag> or <tag/>
 *
 *	Params:
 *		XMLCh*	name	constant XMLCh string representing the name of the element
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::endElement(const XMLCh* const name){
	
	#if defined	OUT_NAME
		cout<<"</"<<XMLString::transcode(name)<<">";
	#endif

	if(strcmp("world",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// time element
	// **********************************************
	else if(strcmp("time",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// roads element
	// **********************************************
	else if(strcmp("roads",XMLString::transcode(name))==0)
	{
		r=false;
	}
	// **********************************************
	// road element
	// **********************************************
	else if(strcmp("road",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// rendering element
	// **********************************************
	else if(strcmp("rendering",XMLString::transcode(name))==0)
	{
		rend=false;
	}
	// **********************************************
	// physics element
	// **********************************************
	else if(strcmp("physics",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// heights element
	// **********************************************
	else if(strcmp("heights",XMLString::transcode(name))==0)
	{
		h=false;
	}
	// **********************************************
	// height element
	// **********************************************
	else if(strcmp("height",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// fog element
	// **********************************************
	else if(strcmp("fog",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// entities element
	// **********************************************
	else if(strcmp("entities",XMLString::transcode(name))==0)
	{
		e=false;
		if(b||c||r){
			throw new SAXMapException("Parse Error: entities element closing in open child");
		}
	}
	// **********************************************
	// distance element
	// **********************************************
	else if(strcmp("distance",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// comment element
	// **********************************************
	else if(strcmp("comment",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// cars element
	// **********************************************
	else if(strcmp("cars",XMLString::transcode(name))==0)
	{
		c=false;
	}
	// **********************************************
	// car element
	// **********************************************
	else if(strcmp("car",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// buildings element
	// **********************************************
	else if(strcmp("buildings",XMLString::transcode(name))==0)
	{
		b=false;
	}
	// **********************************************
	// building element
	// **********************************************
	else if(strcmp("building",XMLString::transcode(name))==0)
	{
	}
	// **********************************************
	// invalid element
	// **********************************************
	else
	{
		throw new SAXMapException("error: unrecognized element");
	}
}


/*
 *	Name:
 *		characters
 *
 *	Description:
 *		PCDATA of a given element
 *
 *	Params:
 *		XMLCh*	chars	PCDATA of a given element in string format
 *		int	length	length of chars
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::characters(const XMLCh* const chars, const unsigned int length){
	#if defined(OUT_NAME)
		cout<<XMLString::transcode(chars);
	#endif

}


/*
 *	Name:
 *		ignorableWhitespace
 *
 *	Description:
 *		whitespace between a <tag> and PCDATA
 *
 *	Params:
 *		XMLCh*	chars	white space of a given element in string format
 *		int	length	length of chars
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::ignorableWhitespace(const XMLCh* const chars, const unsigned int length){
	#if defined(OUT_NAME)
		cout<<XMLString::transcode(chars);
	#endif
}


/*
 *	Name:
 *		resetDocument
 *
 *	Description:
 *		when reset is called this function is called to set all values to null
 *		performs destructor like functions and then constructor init
 *		currently disabled
 *
 *	Params:
 *		XMLCh*	chars	white space of a given element in string format
 *		int	length	length of chars
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::resetDocument(){
	//not used so not implemented
	//would simply call destructor and constructor like functions
	//or implement their functionality
}




// -----------------------------------------------------------------------
//  Handlers for the SAX ErrorHandler interface
// -----------------------------------------------------------------------


/*
 *	Name:
 *		warning
 *
 *	Description:
 *		event called when there is a warning while parsing
 *
 *	Params:
 *		SAXParseException&	exception	reference to a SAXParseException representing the warning
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::warning(const SAXParseException& exception){
	cerr<<"Warning:\t"<<XMLString::transcode(exception.getMessage())<<endl<<endl;
}


/*
 *	Name:
 *		error
 *
 *	Description:
 *		event called when there is a error while parsing
 *		prints error information
 *
 *	Params:
 *		SAXParseException&	exception	reference to a SAXParseException representing the error
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::error(const SAXParseException& exception){
	cerr<<"Error:\t"<<XMLString::transcode(exception.getMessage())<<endl;
	//cerr<<"SystemId:\t"<<XMLString::transcode(exception.getSystemId())<<endl;
	//cerr<<"Line:\t\t"<<exception.getLineNumber()<<endl;
	//cerr<<"Column:\t\t"<<exception.getColumnNumber()<<endl<<endl;
}


/*
 *	Name:
 *		fatalError
 *
 *	Description:
 *		event called when there is a fatalError while parsing
 *		application will be killed afterword
 *
 *	Params:
 *		SAXParseException&	exception	reference to a SAXParseException representing the fatalError
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::fatalError(const SAXParseException& exception){
	cerr<<"Fatal Error:\t"<<XMLString::transcode(exception.getMessage())<<endl;
	cerr<<"SystemId:\t"<<XMLString::transcode(exception.getSystemId())<<endl;
	cerr<<"Line:\t\t"<<exception.getLineNumber()<<endl;
	cerr<<"Column:\t\t"<<exception.getColumnNumber()<<endl<<endl;
}


/*
 *	Name:
 *		resetErrors
 *
 *	Description:
 *		doesn't do any real resetting, simply outputs to standard err
 *
 *	Params:
 *		void
 *
 *	Returns:
 *		void
 *
 */
void SAXMapHandler::resetErrors(){
	cerr<<"Errors Reset\n";
}

//static member variable initialization
int SAXMapHandler::num_buildings = 0;
int SAXMapHandler::num_cars = 0;
int SAXMapHandler::num_roads = 0;

