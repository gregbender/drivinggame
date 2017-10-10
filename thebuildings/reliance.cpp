/*
* This file was produced by 3D Exploration Plugin, we
* added to the Gen3DObjectList() function to help automatically
* produce bouding boxes and help the display lists be exported
* properly.
* http://www.xdsoft.com/explorer/
*/
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include <math.h>

namespace reliance_building {

struct sample_MATERIAL{
 GLfloat ambient[3];
 GLfloat diffuse[3];
 GLfloat specular[3];
 GLfloat emission[3];
 GLfloat alpha;
 GLfloat phExp;
 int   texture;
};
struct sample_TEXTURE{
 char * name;
 GLint  id;
};

static sample_MATERIAL materials [1] = {
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,2.14355f,0} //Concrete_Stucco
};

static sample_TEXTURE texture_maps [1] = {
{"textures/reliance_0.bmp",0}
};

// 104 Verticies
// 4 Texture Coordinates
// 58 Normals
// 156 Triangles

static BYTE face_indicies[156][9] = {
// Box01
	{0,2,3 ,0,1,0 ,0,1,2 }, {3,1,0 ,0,2,0 ,2,3,0 }, {4,5,7 ,3,4,3 ,3,0,1 },
	{7,6,4 ,3,5,3 ,1,2,3 }, {0,1,5 ,6,6,6 ,3,0,1 }, {5,4,0 ,6,6,6 ,1,2,3 },
	{1,3,7 ,7,7,7 ,3,0,1 }, {7,5,1 ,7,7,7 ,1,2,3 }, {3,2,6 ,8,8,8 ,3,0,1 },
	{6,7,3 ,8,8,8 ,1,2,3 }, {2,0,4 ,9,9,9 ,3,0,1 }, {4,6,2 ,9,9,9 ,1,2,3 }
// Box02
	, {8,10,11 ,10,10,10 ,0,1,2 }, {11,9,8 ,10,10,10 ,2,3,0 }, {12,13,15 ,11,12,11 ,3,0,1 },
	{15,14,12 ,11,13,11 ,1,2,3 }, {8,9,13 ,14,14,14 ,3,0,1 }, {13,12,8 ,15,15,15 ,1,2,3 },
	{9,11,15 ,16,16,16 ,3,0,1 }, {15,13,9 ,16,16,16 ,1,2,3 }, {11,10,14 ,17,17,17 ,3,0,1 },
	{14,15,11 ,17,17,17 ,1,2,3 }, {10,8,12 ,18,18,18 ,3,0,1 }, {12,14,10 ,18,18,18 ,1,2,3 }
// Box03
	, {16,18,19 ,19,20,19 ,0,1,2 }, {19,17,16 ,19,21,19 ,2,3,0 },
	{20,21,23 ,22,22,22 ,3,0,1 }, {23,22,20 ,22,22,22 ,1,2,3 }, {16,17,21 ,15,15,15 ,3,0,1 },
	{21,20,16 ,14,14,14 ,1,2,3 }, {17,19,23 ,16,16,16 ,3,0,1 }, {23,21,17 ,16,16,16 ,1,2,3 },
	{19,18,22 ,23,23,23 ,3,0,1 }, {22,23,19 ,23,23,23 ,1,2,3 }, {18,16,20 ,18,18,18 ,3,0,1 },
	{20,22,18 ,18,18,18 ,1,2,3 }
// Box04
	, {24,26,27 ,24,25,24 ,0,1,2 }, {27,25,24 ,24,1,24 ,2,3,0 },
	{28,29,31 ,26,5,26 ,3,0,1 }, {31,30,28 ,26,27,26 ,1,2,3 }, {24,25,29 ,28,28,28 ,3,0,1 },
	{29,28,24 ,28,28,28 ,1,2,3 }, {25,27,31 ,29,29,29 ,3,0,1 }, {31,29,25 ,29,29,29 ,1,2,3 },
	{27,26,30 ,30,30,30 ,3,0,1 }, {30,31,27 ,30,30,30 ,1,2,3 }, {26,24,28 ,31,31,31 ,3,0,1 },
	{28,30,26 ,32,32,32 ,1,2,3 }
// Box05
	, {32,34,35 ,33,33,33 ,0,1,2 }, {35,33,32 ,33,33,33 ,2,3,0 },
	{36,37,39 ,34,34,34 ,3,0,1 }, {39,38,36 ,34,34,34 ,1,2,3 }, {32,33,37 ,35,35,35 ,3,0,1 },
	{37,36,32 ,35,35,35 ,1,2,3 }, {33,35,39 ,36,36,36 ,3,0,1 }, {39,37,33 ,36,36,36 ,1,2,3 },
	{35,34,38 ,30,30,30 ,3,0,1 }, {38,39,35 ,30,30,30 ,1,2,3 }, {34,32,36 ,37,37,37 ,3,0,1 },
	{36,38,34 ,37,37,37 ,1,2,3 }
// Box06
	, {40,42,43 ,33,33,33 ,0,1,2 }, {43,41,40 ,33,33,33 ,2,3,0 },
	{44,45,47 ,34,34,34 ,3,0,1 }, {47,46,44 ,34,34,34 ,1,2,3 }, {40,41,45 ,35,35,35 ,3,0,1 },
	{45,44,40 ,35,35,35 ,1,2,3 }, {41,43,47 ,38,38,38 ,3,0,1 }, {47,45,41 ,38,38,38 ,1,2,3 },
	{43,42,46 ,30,30,30 ,3,0,1 }, {46,47,43 ,30,30,30 ,1,2,3 }, {42,40,44 ,37,37,37 ,3,0,1 },
	{44,46,42 ,37,37,37 ,1,2,3 }
// Box07
	, {48,50,51 ,33,33,33 ,0,1,2 }, {51,49,48 ,33,33,33 ,2,3,0 },
	{52,53,55 ,34,34,34 ,3,0,1 }, {55,54,52 ,34,34,34 ,1,2,3 }, {48,49,53 ,35,35,35 ,3,0,1 },
	{53,52,48 ,35,35,35 ,1,2,3 }, {49,51,55 ,36,36,36 ,3,0,1 }, {55,53,49 ,36,36,36 ,1,2,3 },
	{51,50,54 ,30,30,30 ,3,0,1 }, {54,55,51 ,30,30,30 ,1,2,3 }, {50,48,52 ,37,37,37 ,3,0,1 },
	{52,54,50 ,37,37,37 ,1,2,3 }
// Box08
	, {56,58,59 ,39,39,39 ,0,1,2 }, {59,57,56 ,39,39,39 ,2,3,0 },
	{60,61,63 ,40,40,40 ,3,0,1 }, {63,62,60 ,40,40,40 ,1,2,3 }, {56,57,61 ,41,41,41 ,3,0,1 },
	{61,60,56 ,42,42,42 ,1,2,3 }, {57,59,63 ,29,29,29 ,3,0,1 }, {63,61,57 ,29,29,29 ,1,2,3 },
	{59,58,62 ,43,43,43 ,3,0,1 }, {62,63,59 ,44,44,44 ,1,2,3 }, {58,56,60 ,37,37,37 ,3,0,1 },
	{60,62,58 ,37,37,37 ,1,2,3 }
// Box09
	, {64,66,67 ,45,1,45 ,0,1,2 }, {67,65,64 ,45,46,45 ,2,3,0 },
	{68,69,71 ,47,48,47 ,3,0,1 }, {71,70,68 ,47,5,47 ,1,2,3 }, {64,65,69 ,49,49,49 ,3,0,1 },
	{69,68,64 ,49,49,49 ,1,2,3 }, {65,67,71 ,50,50,50 ,3,0,1 }, {71,69,65 ,50,50,50 ,1,2,3 },
	{67,66,70 ,51,51,51 ,3,0,1 }, {70,71,67 ,51,51,51 ,1,2,3 }, {66,64,68 ,37,37,37 ,3,0,1 },
	{68,70,66 ,37,37,37 ,1,2,3 }
// Box10
	, {72,74,75 ,33,33,33 ,0,1,2 }, {75,73,72 ,33,33,33 ,2,3,0 },
	{76,77,79 ,34,34,34 ,3,0,1 }, {79,78,76 ,34,34,34 ,1,2,3 }, {72,73,77 ,49,49,49 ,3,0,1 },
	{77,76,72 ,49,49,49 ,1,2,3 }, {73,75,79 ,36,36,36 ,3,0,1 }, {79,77,73 ,36,36,36 ,1,2,3 },
	{75,74,78 ,30,30,30 ,3,0,1 }, {78,79,75 ,30,30,30 ,1,2,3 }, {74,72,76 ,37,37,37 ,3,0,1 },
	{76,78,74 ,37,37,37 ,1,2,3 }
// Box11
	, {80,82,83 ,33,33,33 ,0,1,2 }, {83,81,80 ,33,33,33 ,2,3,0 },
	{84,85,87 ,34,34,34 ,3,0,1 }, {87,86,84 ,34,34,34 ,1,2,3 }, {80,81,85 ,49,49,49 ,3,0,1 },
	{85,84,80 ,49,49,49 ,1,2,3 }, {81,83,87 ,36,36,36 ,3,0,1 }, {87,85,81 ,36,36,36 ,1,2,3 },
	{83,82,86 ,30,30,30 ,3,0,1 }, {86,87,83 ,30,30,30 ,1,2,3 }, {82,80,84 ,52,52,52 ,3,0,1 },
	{84,86,82 ,52,52,52 ,1,2,3 }
// Box12
	, {88,90,91 ,33,33,33 ,0,1,2 }, {91,89,88 ,33,33,33 ,2,3,0 },
	{92,93,95 ,34,34,34 ,3,0,1 }, {95,94,92 ,34,34,34 ,1,2,3 }, {88,89,93 ,49,49,49 ,3,0,1 },
	{93,92,88 ,49,49,49 ,1,2,3 }, {89,91,95 ,36,36,36 ,3,0,1 }, {95,93,89 ,36,36,36 ,1,2,3 },
	{91,90,94 ,30,30,30 ,3,0,1 }, {94,95,91 ,30,30,30 ,1,2,3 }, {90,88,92 ,37,37,37 ,3,0,1 },
	{92,94,90 ,37,37,37 ,1,2,3 }
// Box13
	, {96,98,99 ,53,53,53 ,0,1,2 }, {99,97,96 ,53,53,53 ,2,3,0 },
	{100,101,103 ,54,54,54 ,3,0,1 }, {103,102,100 ,54,54,54 ,1,2,3 },
	{96,97,101 ,55,55,55 ,3,0,1 }, {101,100,96 ,56,56,56 ,1,2,3 },
	{97,99,103 ,36,36,36 ,3,0,1 }, {103,101,97 ,36,36,36 ,1,2,3 },
	{99,98,102 ,44,44,44 ,3,0,1 }, {102,103,99 ,43,43,43 ,1,2,3 },
	{98,96,100 ,57,57,57 ,3,0,1 }, {100,102,98 ,57,57,57 ,1,2,3 }
};
static GLfloat vertices [104][3] = {
{0.0525555f,-0.5f,0.498744f},{0.0525555f,-0.5f,0.402591f},{-0.0532137f,-0.5f,0.498744f},
{-0.0532137f,-0.5f,0.402591f},{0.0525554f,0.5f,0.498744f},{0.0525554f,0.5f,0.402591f},
{-0.0532138f,0.5f,0.498744f},{-0.0532138f,0.5f,0.402591f},{0.0529699f,0.288702f,0.395486f},
{0.0529699f,0.288702f,-0.498744f},{-0.0527993f,0.288702f,0.395486f},{-0.0527993f,0.288702f,-0.498744f},
{0.0529699f,0.394471f,0.395486f},{0.0529699f,0.394471f,-0.498744f},{-0.0527993f,0.394471f,0.395486f},
{-0.0527993f,0.394471f,-0.498744f},{0.0529699f,-0.396618f,0.395486f},{0.0529699f,-0.396618f,-0.498744f},
{-0.0527993f,-0.396618f,0.395486f},{-0.0527993f,-0.396618f,-0.498744f},{0.0529699f,-0.290849f,0.395486f},
{0.0529699f,-0.290849f,-0.498744f},{-0.0527993f,-0.290849f,0.395486f},{-0.0527993f,-0.290849f,-0.498744f},
{-0.0526806f,-0.5f,0.497954f},{-0.0526806f,-0.5f,0.4018f},{-0.0815268f,-0.5f,0.497954f},
{-0.0815268f,-0.5f,0.4018f},{-0.0526807f,0.5f,0.497954f},{-0.0526807f,0.5f,0.4018f},
{-0.0815268f,0.5f,0.497954f},{-0.0815268f,0.5f,0.4018f},{-0.0527993f,-0.5f,0.306437f},
{-0.0527993f,-0.5f,0.210283f},{-0.0816454f,-0.5f,0.306437f},{-0.0816454f,-0.5f,0.210283f},
{-0.0527993f,0.5f,0.306437f},{-0.0527993f,0.5f,0.210283f},{-0.0816455f,0.5f,0.306437f},
{-0.0816455f,0.5f,0.210283f},{-0.0527993f,-0.5f,0.102449f},{-0.0527993f,-0.5f,0.0062952f},
{-0.0816454f,-0.5f,0.102449f},{-0.0816454f,-0.5f,0.0062952f},{-0.0527993f,0.5f,0.102449f},
{-0.0527993f,0.5f,0.00629516f},{-0.0816455f,0.5f,0.102449f},{-0.0816455f,0.5f,0.00629516f},
{-0.0527993f,-0.5f,-0.101047f},{-0.0527993f,-0.5f,-0.197201f},{-0.0816454f,-0.5f,-0.101047f},
{-0.0816454f,-0.5f,-0.197201f},{-0.0527993f,0.5f,-0.101047f},{-0.0527993f,0.5f,-0.197201f},
{-0.0816455f,0.5f,-0.101047f},{-0.0816455f,0.5f,-0.197201f},{-0.0527993f,-0.5f,-0.304053f},
{-0.0527993f,-0.5f,-0.400207f},{-0.0816454f,-0.5f,-0.304053f},{-0.0816454f,-0.5f,-0.400207f},
{-0.0527993f,0.5f,-0.304053f},{-0.0527993f,0.5f,-0.400207f},{-0.0816455f,0.5f,-0.304053f},
{-0.0816455f,0.5f,-0.400207f},{0.0816455f,-0.5f,-0.4008f},{0.0816455f,-0.5f,-0.496954f},
{0.0527993f,-0.5f,-0.4008f},{0.0527993f,-0.5f,-0.496954f},{0.0816454f,0.5f,-0.400801f},
{0.0816454f,0.5f,-0.496954f},{0.0527993f,0.5f,-0.400801f},{0.0527993f,0.5f,-0.496954f},
{0.0816455f,-0.5f,-0.208853f},{0.0816455f,-0.5f,-0.305007f},{0.0527993f,-0.5f,-0.208853f},
{0.0527993f,-0.5f,-0.305007f},{0.0816454f,0.5f,-0.208853f},{0.0816454f,0.5f,-0.305007f},
{0.0527993f,0.5f,-0.208853f},{0.0527993f,0.5f,-0.305007f},{0.0816455f,-0.5f,-0.00775336f},
{0.0816455f,-0.5f,-0.103907f},{0.0527993f,-0.5f,-0.00775336f},{0.0527993f,-0.5f,-0.103907f},
{0.0816454f,0.5f,-0.0077534f},{0.0816454f,0.5f,-0.103907f},{0.0527993f,0.5f,-0.0077534f},
{0.0527993f,0.5f,-0.103907f},{0.0816455f,-0.5f,0.192862f},{0.0816455f,-0.5f,0.0967083f},
{0.0527993f,-0.5f,0.192862f},{0.0527993f,-0.5f,0.0967083f},{0.0816454f,0.5f,0.192862f},
{0.0816454f,0.5f,0.0967083f},{0.0527993f,0.5f,0.192862f},{0.0527993f,0.5f,0.0967083f},
{0.0816455f,-0.5f,0.40261f},{0.0816455f,-0.5f,0.306456f},{0.0527993f,-0.5f,0.40261f},
{0.0527993f,-0.5f,0.306456f},{0.0816454f,0.5f,0.402609f},{0.0816454f,0.5f,0.306456f},
{0.0527993f,0.5f,0.402609f},{0.0527993f,0.5f,0.306456f}
};
static GLfloat normals [58][3] = {
{1.79898e-07f,-1.0f,1.97888e-07f},{0.0f,-1.0f,3.95775e-07f},{3.59795e-07f,-1.0f,0.0f},
{-1.79898e-07f,1.0f,-1.97888e-07f},{-3.59795e-07f,1.0f,0.0f},{0.0f,1.0f,-3.95775e-07f},
{1.0f,4.75691e-08f,0.0f},{2.73842e-14f,-7.61105e-08f,-1.0f},{-1.0f,-4.75691e-08f,1.88267e-14f},
{0.0f,7.61105e-08f,1.0f},{0.0f,-1.0f,4.25564e-08f},{-1.79898e-07f,1.0f,-6.38346e-08f},
{0.0f,1.0f,-8.51129e-08f},{-3.59795e-07f,1.0f,-4.25564e-08f},{1.0f,4.49744e-08f,-1.91395e-15f},
{1.0f,4.49744e-08f,-3.8279e-15f},{0.0f,0.0f,-1.0f},{-1.0f,-4.49744e-08f,1.91395e-15f},
{0.0f,0.0f,1.0f},{1.79898e-07f,-1.0f,6.38346e-08f},{3.59795e-07f,-1.0f,4.25564e-08f},
{0.0f,-1.0f,8.51129e-08f},{0.0f,1.0f,-4.25564e-08f},{-1.0f,-4.49744e-08f,1.91395e-15f},
{6.59625e-07f,-1.0f,1.97888e-07f},{1.31925e-06f,-1.0f,0.0f},{-6.59625e-07f,1.0f,-1.97888e-07f},
{-1.31925e-06f,1.0f,0.0f},{1.0f,4.28122e-08f,-1.6944e-14f},{0.0f,-7.61106e-08f,-1.0f},
{-1.0f,-4.75691e-08f,0.0f},{-1.00409e-13f,7.61106e-08f,1.0f},{-1.00409e-13f,7.61106e-08f,1.0f},
{0.0f,-1.0f,0.0f},{0.0f,1.0f,0.0f},{1.0f,4.28122e-08f,0.0f},
{0.0f,-3.80553e-08f,-1.0f},{0.0f,3.80553e-08f,1.0f},{0.0f,-4.40014e-08f,-1.0f},
{0.0f,-1.0f,3.95775e-07f},{0.0f,1.0f,-3.95775e-07f},{1.0f,4.28122e-08f,-1.6944e-14f},
{1.0f,4.28122e-08f,-1.6944e-14f},{-1.0f,-4.75691e-08f,1.88267e-14f},{-1.0f,-4.75691e-08f,1.88267e-14f},
{6.59625e-07f,-1.0f,1.97888e-07f},{1.31925e-06f,-1.0f,0.0f},{-6.59625e-07f,1.0f,-1.97888e-07f},
{-1.31925e-06f,1.0f,0.0f},{1.0f,4.75691e-08f,0.0f},{5.02044e-14f,-3.80553e-08f,-1.0f},
{-1.0f,-4.75691e-08f,1.88267e-14f},{0.0f,4.40014e-08f,1.0f},{0.0f,-1.0f,3.95775e-07f},
{0.0f,1.0f,-3.95775e-07f},{1.0f,4.75691e-08f,-1.88267e-14f},{1.0f,4.75691e-08f,-1.88267e-14f},
{0.0f,7.61106e-08f,1.0f}
};
static GLfloat textures [4][2] = {
{1.0f,1.0f},{1.0f,2.0f},{0.0f,2.0f},
{0.0f,1.0f}
};
/*Material indicies*/
/*{material index,face count}*/
static int material_ref [1][2] = {
{0,156}
};
struct DIB2D{
 BITMAPINFOHEADER *Info;
 RGBQUAD *palette;
 BYTE    *bits;
};
struct GLTXTLOAD{
 GLint format;
 GLint perpixel;
 GLint Width;
 GLint Height;
 BYTE* bits;
};

/*
BOOL LoadDIB(char*file,DIB2D*dib)
Only trueColor and 256 color ucompressed bitmaps supported
*/
BOOL LoadDIB(char*file,DIB2D*dib)
 {
  BOOL result=FALSE;
  HANDLE hfile=CreateFile(file,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,0);
  if(hfile!=INVALID_HANDLE_VALUE)
    {
     DWORD readed;
     int size=GetFileSize(hfile,0);
     if(size>sizeof(BITMAPFILEHEADER))
      {
       BITMAPFILEHEADER bmfh;
       ReadFile(hfile,&bmfh,sizeof(BITMAPFILEHEADER),&readed,0);
       if((readed==sizeof(BITMAPFILEHEADER)) && (bmfh.bfType==0x4d42))
        {
         dib->Info=(BITMAPINFOHEADER*)(new BYTE[size-sizeof(BITMAPFILEHEADER)]);
         ReadFile(hfile,dib->Info,size-sizeof(BITMAPFILEHEADER),&readed,0);
         dib->bits=(BYTE*)(dib->Info+1);

         if(dib->Info->biBitCount==8)
          {
           dib->palette=(RGBQUAD*)dib->bits;
           if(dib->Info->biClrUsed)dib->bits+=dib->Info->biClrUsed*4;else dib->bits+=1024;
          }else{
           dib->palette=NULL;
          }
         result=TRUE;
        }
      }
     CloseHandle(hfile);
    }
   return result;
 };

long ScanBytes(int pixWidth, int bitsPixel) {
  return (((long)pixWidth*bitsPixel+31) / 32) * 4;
}

BOOL  ScaleImage(DIB2D&dib,GLTXTLOAD&p)
 {
   GLint glMaxTexDim;     // OpenGL maximum texture dimension
   GLint XDMaxTexDim=512; // user maximum texture dimension
   GLint minsize =2;
   double xPow2, yPow2;
   int ixPow2, iyPow2;
   int xSize2, ySize2;
   GLint m_iWidth=dib.Info->biWidth;
   GLint m_iHeight=dib.Info->biHeight;
   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);

   glMaxTexDim = min(XDMaxTexDim, glMaxTexDim);

   if (m_iWidth <= glMaxTexDim)
      xPow2 = log((double)m_iWidth) / log(2.0);
   else
      xPow2 = log((double)glMaxTexDim) / log(2.0);

   if (m_iHeight <= glMaxTexDim)
      yPow2 = log((double)m_iHeight) / log(2.0);
   else
      yPow2 = log((double)glMaxTexDim) / log(2.0);

   ixPow2 = (int)xPow2;
   iyPow2 = (int)yPow2;

   if (xPow2 != (double)ixPow2)
      ixPow2++;
   if (yPow2 != (double)iyPow2)
      iyPow2++;

   xSize2 = 1 << ixPow2;
   ySize2 = 1 << iyPow2;

   if(xSize2<minsize)xSize2=minsize;
   if(ySize2<minsize)ySize2=minsize;

   if(((xSize2==m_iWidth) && (ySize2==m_iHeight)))
   {
     if(dib.Info->biBitCount==24){
       p.format=GL_BGR_EXT;
       p.perpixel=3;
       return FALSE;
      }
     if(dib.Info->biBitCount==32)
      {
       p.format=GL_BGRA_EXT;
       p.perpixel=4;
       return FALSE;
      }
   }

   BYTE *bits=(BYTE *)dib.bits;
   if(dib.Info->biBitCount==8){

    // convert to TRUECOLOR
    int _perline=ScanBytes(8,m_iWidth);
    int perline=ScanBytes(24,m_iWidth);
    bits= new BYTE[perline*m_iHeight * sizeof(BYTE)];
    for(int y=0;y<m_iHeight;y++){
     BYTE *_b=((BYTE *)dib.bits)+y*_perline;
     BYTE *b=bits+y*perline;
     for(int x=0;x<m_iWidth;x++){
      RGBQUAD _p=dib.palette[*_b];
      _b++;
      *b=_p.rgbBlue;b++;
      *b=_p.rgbGreen;b++;
      *b=_p.rgbRed;b++;
     }
    }
   }
   BOOL isAlpha=(dib.Info->biBitCount==32);
   int _mem_size=xSize2 * ySize2 *  sizeof(BYTE);
   if(isAlpha){
         _mem_size*=4;
          p.perpixel=4;
          p.format=GL_BGRA_EXT;
          }else {
          _mem_size*=3;
          p.perpixel=3;
          p.format=GL_BGR_EXT;
          }
   BYTE *pData = (BYTE*)new BYTE[_mem_size];
   if (!pData) return FALSE;

   if(isAlpha){
   gluScaleImage(GL_BGRA_EXT, m_iWidth, m_iHeight,
                 GL_UNSIGNED_BYTE, bits,
                 xSize2, ySize2, GL_UNSIGNED_BYTE, pData);
   }
   else
   gluScaleImage(GL_RGB, m_iWidth, m_iHeight,
                 GL_UNSIGNED_BYTE, bits,
                 xSize2, ySize2, GL_UNSIGNED_BYTE, pData);


   if(bits!=dib.bits)delete bits;
//   m_pBits = pData;
   m_iWidth = xSize2 ;
   m_iHeight = ySize2 ;
   p.Width=m_iWidth;
   p.Height=m_iHeight;
   p.bits=pData;

   return TRUE ;
 }
void LoadTexture(char*filename)
 {
  DIB2D dib;
  GLTXTLOAD load;
  if(LoadDIB(filename,&dib))
   {

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(ScaleImage(dib,load))
     {
   glTexImage2D(GL_TEXTURE_2D,0,load.perpixel,
                load.Width,load.Height,0,
                load.format,GL_UNSIGNED_BYTE,
                load.bits);
                delete load.bits;
     }else{

   glTexImage2D(GL_TEXTURE_2D,0,load.perpixel,
                dib.Info->biWidth,dib.Info->biHeight,
                0,load.format,GL_UNSIGNED_BYTE,dib.bits);
     }
   delete dib.Info;
   }

  //DeleteObject(hbitmap);
 };


void MyMaterial(GLenum mode,GLfloat *f,GLfloat alpha)
{
 GLfloat d[4];
 d[0]=f[0];
 d[1]=f[1];
 d[2]=f[2];
 d[3]=alpha;
 glMaterialfv (GL_FRONT_AND_BACK,mode,d);
}
/*
 *  SelectMaterial uses OpenGL commands to define facet colors.
 *
 *  Returns:
 *    Nothing
 */

void SelectMaterial(int i)
{
  //
  // Define the reflective properties of the 3D Object faces.
  //
  glEnd();
  GLfloat alpha=materials[i].alpha;
  MyMaterial (GL_AMBIENT, materials[i].ambient,alpha);
  MyMaterial (GL_DIFFUSE, materials[i].diffuse,alpha);
  MyMaterial (GL_SPECULAR, materials[i].specular,alpha);
  MyMaterial (GL_EMISSION, materials[i].emission,alpha);
  glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,materials[i].phExp);
	glEnd();
	if(materials[i].texture>-1)
	{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture_maps[materials[i].texture].id);
	}
	else
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

  glBegin(GL_TRIANGLES);

};

GLint Gen3DObjectList()
{
 int i;
 int j;

  GLuint texture_name;
  glGenTextures(1,&texture_name);
  texture_maps[0].id=texture_name;
  glBindTexture(GL_TEXTURE_2D,texture_name);
  LoadTexture(texture_maps[0].name);
 GLint lid=glGenLists(1);
	int mcount=0;
	int mindex=0;
   glNewList(lid, GL_COMPILE);

    glBegin (GL_TRIANGLES);
      for(i=0;i<sizeof(face_indicies)/sizeof(face_indicies[0]);i++)
       {
      if(!mcount)
       {
        SelectMaterial(material_ref[mindex][0]);
        mcount=material_ref[mindex][1];
        mindex++;
       }
       mcount--;
       for(j=0;j<3;j++)
        {
          int vi=face_indicies[i][j];
          int ni=face_indicies[i][j+3];//Normal index
          int ti=face_indicies[i][j+6];//Texture index
           glNormal3f (normals[ni][0],normals[ni][1],normals[ni][2]);
           glTexCoord2f(textures[ti][0],textures[ti][1]);
           glVertex3f (vertices[vi][0],vertices[vi][1],vertices[vi][2]);
        }
       }
    glEnd ();

   glEndList();
   return lid;
};
}