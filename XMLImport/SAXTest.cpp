// SAXTest.cpp : Defines the entry point for the application.
//

#include "SAXMapHandler.hpp"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>

int main(int argC, char* argV[])
{

	SAXMapHandler *handler = new SAXMapHandler();

	char *systemid = "world.xml";

	if(handler->executeParse(systemid)==0){
		cout<<"\n\nParse Success!"<<endl;
	}
	else{
		cout<<"\n\nParse Failed!"<<endl;
	}

	delete handler;

	return 0;
}

