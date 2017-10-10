#ifndef SAX_MAP_HANDLER
#define SAX_MAP_HANDLER

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/validators/schema/SchemaValidator.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include "SAXMapException.cpp"
#include "global.hpp"

/*xerces-c_1.lib must also be in the Object/library modules path*/

class SAXMapHandler : public HandlerBase {

public:
	// -----------------------------------------------------------------------
	// Public Structures and Enumerated Types
	// -----------------------------------------------------------------------

	//structure used to represent a node in a building linked list
	struct Building{
		int type;
		int orientation;
		int x;
		int y;
		Building *next;
	};

	//structure used to represent a node in a car linked list
	struct Car{
		int type;
		int orientation;
		int x;
		int y;
		Car *next;
	};

	//structure used to represent a node in a road linked list
	struct Road{
		int type;
		int x;
		int y;
		//int orientation;
		//int span;
		Road *next;
	};

	//structure used to represent a node in a height linked list
	struct Height{
		int span;
		int height;
		int orientation;
		int x;
		int y;
		Height *next;
	};

	//structure holding world data
	struct World{
		int x;
		int y;
		int rendering_distance;
		int fog_viscosity;
		int gravity;
		int friction;
		int time_of_day;
	};


	//-----------------------------------------------------------------------
    //  Constructors/Destructors
    // -----------------------------------------------------------------------

	//constructor
	SAXMapHandler();
	//destructor
	~SAXMapHandler();

    // -----------------------------------------------------------------------
    //  methods
    // -----------------------------------------------------------------------

	//  execution
	int executeParse(char* systemid);

	//  accessors

	//returns head of buildings linked list
	Building* getBuildings();
	//returns head of cars linked list
	Car* getCars();
	//returns head of roads linked list
	Road* getRoads();
	//returns head of height linked list
	Height* getHeights();
	//returns world structure
	World* getWorld();

    // -----------------------------------------------------------------------
    //  Handlers for the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
	void startElement(const XMLCh* const name, AttributeList& attributes);
	void endElement(const XMLCh* const name);
    void characters(const XMLCh* const chars, const unsigned int length);
    void ignorableWhitespace(const XMLCh* const chars, const unsigned int length);
    void resetDocument();


    // -----------------------------------------------------------------------
    //  Handlers for the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
	void warning(const SAXParseException& exception);
    void error(const SAXParseException& exception);
    void fatalError(const SAXParseException& exception);
    void resetErrors();

	static int num_buildings;
	static int num_cars;
	static int num_roads;


protected:


private:

	Road* copyRoad(Road*);

	//used for internal validation
	bool b;
	bool c;
	bool r;
	bool h;
	bool e;
	bool rend;

	//linked lists
	Building *buildings;
	Car *cars;
	Road *roads;
	Height *heights;

	//tails used for efficiency
	Building *btail;
	Car *ctail;
	Road *rtail;
	Height *htail;

	//world structure pointer
	World *the_world;

	//parser pointer
	SAXParser *parser;

};


#endif