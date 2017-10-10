#ifndef SAX_MAP_EXCEPTION
#define SAX_MAP_EXCEPTION


class SAXMapException{

public:

	SAXMapException(char* e):error(e){
	}

	char* getMessage(){
		return error;
	}

private:
	char* error;

};

#endif