3D Driving World
Mike Krauklis
Greg Bender
Computer Graphics II - 4003-571
Warren R. Carithers

Compilation:
To compile you must download the xerces c++ api and place the library files in the path "xercesc"
You must also download and install the DirectX SDK
note: compilation only works in Debug mode, Release mode does not work

Most of the 3D models were downloaded as 3D studio max files
from: http://romka.demonews.com/models/index_eng.htm.

They were converted into display lists using 3D exploration:
http://www.righthemisphere.com/products/3dexplore/index.htm

Code for the frames per second timer was partially aquired from
the book openGL Game Programming (ISBN# 0761533303).  As well as pieces
of the Vector class and the direct input class.

Xerces library files (for world loading) are available at
http://xml.apache.org/xerces-c/index.html.

The code for extracting the viewing frustum function ExtractFrustum()
was taken from:
http://www.markmorley.com/opengl/frustumculling.html

The world is defined in an XML file called world.xml.

Backface culling is used to only show the front side of the buildings,
as well as simple bounding boxes around each building and car for frustum
culling.  Each car and building and road is stored in it's own linked list
(that is loaded up by the XML parser that reads world.xml).  Only cars,buildings,
and roads that are in the viewing frustum are renderd to the screen and checked
for collisions.  There is a very simple artificial inteligence based on the
roads, such that the computer controlled cars will usually drive somewhere
on the roads.  The models are all modular, (loaded up in display_list_loader.cpp)
so that cars and buildings can be replaced with different models, and
the system will continue to function.

The XML file (world.xml) is read in using a SAX parser and the xerces API.  This is
converted into several linked lists (of roads,buildings,cars) that are then traversed
by the Render() and RenderWorld() functions.

The code should support XML schema validation but due to the lagging development
of the C++ version of the xerces api (as opposted to the Java), schema
validation is not yet supported.

Controls:
UP ARROW - accelerate
DOWN ARROW - brake (go backwards)
LEFT ARROW - turn left
RIGHT ARROW - turn right
SPACEBAR - turn on emergency brake (skid)
HOLD C key - turn off collision detection

File Overview:

These are used to read in world.xml and turn things into
linked lists of objects:
XMLImport/global.hpp
XMLImport/SAXMapException.cpp
XMLImport/SAXMapHandler.cpp
XMLImport/SAXMapHandler.hpp
XMLImport/SAXTest.cpp

boundingbox.cpp -- creates a 6 plane bounding box around any object
building.cpp -- represents a building, and holds it's posiiton and bounding box
camera.cpp -- represents the camera, controls movement
car.cpp -- controls movement of user car and computer cars
display_list_loader.cpp -- holds functions that create display lists for
                        -- each object, and also functions that
                        -- automatically generate bounding boxes
init_roads.cpp -- holds functions needed for each type of road
main.cpp -- main file, bulk of code, create and sets of world
plane.cpp -- plane class, is used in the boundingbox and for collision detection
wheel.cpp -- the wheel of each car
HiResTimer.h -- timer used to help smooth movement of frames
object.h -- abstract class inherited by wheel/car/camera and building
vector.h -- vector class, used for acceleration/position and velocity

Directories:
thebuildings -- These directories contain cpp files that read in the texture files
                for each of these objects, and export them as display lists.  Many
                of these files were generated using the program '3D Exploration'.
textures -- contains all the textures needed by the buildings and
            cars, these are .raw and .bmp files


The dll files are needed for openGL/DirectInput/and the Xerces XML
processor.

world.xml -- defines what the world looks like
world.xsd -- schemea that could be used to see if the world.xml file
             is well-formed and valid.(but not really, we never got Schema validation to work)