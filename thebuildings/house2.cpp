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

namespace coolhouse {

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

static sample_MATERIAL materials [24] = {
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,0}, //TruncatedPyramidOnTop_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,1}, //none
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,2}, //TruncatedPyramidOnTop_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,3}, //TruncatedPyramidOnTop_2
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,4}, //TSWOnTop_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,5}, //TSWOnTop_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,6}, //TSWOnTop_2
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,7}, //RoofOnTop1_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,8}, //RoofOnTop1_2
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,9}, //RoofOnTop1_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,10}, //RoofOnTop_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,11}, //RoofOnTop_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,12}, //RoofOnTop_2
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,13}, //BoxOnTop1_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,14}, //BoxOnTop1_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,15}, //BoxOnTop1_2
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,16}, //BoxOnTop_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,17}, //BoxOnTop_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,18}, //Box2_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,19}, //Box2_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,20}, //Box2_2
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,1}, //Box_0
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,21}, //Box_1
 {{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	{1.0f,1.0f,1.0f},	1.0f,100.0f,22} //Box_2
};

static sample_TEXTURE texture_maps [23] = {
{"textures/house2_0.bmp",0},
{"textures/house2_1.bmp",0},
{"textures/house2_2.bmp",0},
{"textures/house2_3.bmp",0},
{"textures/house2_4.bmp",0},
{"textures/house2_5.bmp",0},
{"textures/house2_6.bmp",0},
{"textures/house2_7.bmp",0},
{"textures/house2_8.bmp",0},
{"textures/house2_9.bmp",0},
{"textures/house2_10.bmp",0},
{"textures/house2_11.bmp",0},
{"textures/house2_12.bmp",0},
{"textures/house2_13.bmp",0},
{"textures/house2_14.bmp",0},
{"textures/house2_15.bmp",0},
{"textures/house2_16.bmp",0},
{"textures/house2_17.bmp",0},
{"textures/house2_18.bmp",0},
{"textures/house2_19.bmp",0},
{"textures/house2_20.bmp",0},
{"textures/house2_21.bmp",0},
{"textures/house2_22.bmp",0}
};

// 58 Verticies
// 10 Texture Coordinates
// 38 Normals
// 84 Triangles

static BYTE face_indicies[84][9] = {
// TruncatedPyramidOnTop
	{5,3,0 ,0,1,0 ,0,1,2 }, {0,4,5 ,0,2,0 ,2,3,0 }, {3,2,1 ,3,3,3 ,4,5,3 },
	{1,0,3 ,3,3,3 ,3,2,4 }, {7,6,5 ,4,4,4 ,2,4,5 }, {5,4,7 ,4,4,4 ,5,3,2 },
	{1,2,6 ,5,5,5 ,3,0,1 }, {6,7,1 ,5,5,5 ,1,2,3 }, {6,2,3 ,6,6,6 ,6,7,3 },
	{3,5,6 ,6,6,6 ,3,2,6 }, {0,1,7 ,7,7,7 ,7,3,2 }, {7,4,0 ,7,7,7 ,2,6,7 }
// TSWOnTop
	, {10,9,8 ,8,8,8 ,8,2,3 }, {13,12,11 ,9,9,9 ,3,2,8 }, {12,13,8 ,6,6,6 ,3,7,6 },
	{8,9,12 ,6,6,6 ,6,2,3 }, {11,12,9 ,10,10,10 ,3,7,6 }, {9,10,11 ,10,10,10 ,6,2,3 },
	{13,11,10 ,11,11,11 ,3,7,6 }, {10,8,13 ,11,11,11 ,6,2,3 }
// RoofOnTop1
	, {15,18,14 ,12,12,12 ,2,9,3 }, {17,19,16 ,13,13,13 ,2,9,3 },
	{14,18,19 ,14,15,14 ,6,7,3 }, {19,17,14 ,14,16,14 ,3,2,6 }, {17,16,15 ,6,6,6 ,6,7,3 },
	{15,14,17 ,6,6,6 ,3,2,6 }, {16,19,18 ,17,17,17 ,6,7,3 }, {18,15,16 ,17,17,17 ,3,2,6 }
// RoofOnTop
	, {21,24,20 ,18,18,18 ,2,9,3 }, {23,25,22 ,19,19,19 ,2,9,3 },
	{23,22,21 ,6,6,6 ,6,7,3 }, {21,20,23 ,6,6,6 ,3,2,6 }, {22,25,24 ,20,20,20 ,6,7,3 },
	{24,21,22 ,20,20,20 ,3,2,6 }, {20,24,25 ,21,21,21 ,6,7,3 }, {25,23,20 ,21,21,21 ,3,2,6 }
// BoxOnTop1
	, {29,28,27 ,22,22,22 ,6,7,3 }, {27,26,29 ,22,22,22 ,3,2,6 },
	{33,32,31 ,23,23,23 ,2,6,7 }, {31,30,33 ,23,23,23 ,7,3,2 }, {27,28,32 ,24,24,24 ,2,6,7 },
	{32,33,27 ,24,24,24 ,7,3,2 }, {31,29,26 ,25,25,25 ,6,7,3 }, {26,30,31 ,25,25,25 ,3,2,6 },
	{32,28,29 ,6,6,6 ,6,7,3 }, {29,31,32 ,6,6,6 ,3,2,6 }, {26,27,33 ,7,7,7 ,7,3,2 },
	{33,30,26 ,7,7,7 ,2,6,7 }
// BoxOnTop
	, {37,36,35 ,26,26,26 ,6,7,3 }, {35,34,37 ,26,26,26 ,3,2,6 },
	{41,40,39 ,27,27,27 ,2,6,7 }, {39,38,41 ,27,27,27 ,7,3,2 }, {35,36,40 ,28,28,28 ,2,6,7 },
	{40,41,35 ,28,28,28 ,7,3,2 }, {39,37,34 ,29,29,29 ,6,7,3 }, {34,38,39 ,29,29,29 ,3,2,6 },
	{40,36,37 ,6,6,6 ,6,7,3 }, {37,39,40 ,6,6,6 ,3,2,6 }, {34,35,41 ,7,7,7 ,7,3,2 },
	{41,38,34 ,7,7,7 ,2,6,7 }
// Box2
	, {45,44,43 ,30,30,30 ,6,7,3 }, {43,42,45 ,30,30,30 ,3,2,6 },
	{49,48,47 ,31,31,31 ,2,6,7 }, {47,46,49 ,31,31,31 ,7,3,2 }, {43,44,48 ,32,32,32 ,2,6,7 },
	{48,49,43 ,32,32,32 ,7,3,2 }, {47,45,42 ,33,33,33 ,6,7,3 }, {42,46,47 ,33,33,33 ,3,2,6 },
	{48,44,45 ,6,6,6 ,6,7,3 }, {45,47,48 ,6,6,6 ,3,2,6 }, {42,43,49 ,7,7,7 ,7,3,2 },
	{49,46,42 ,7,7,7 ,2,6,7 }
// Box
	, {53,52,51 ,34,34,34 ,6,7,3 }, {51,50,53 ,34,34,34 ,3,2,6 },
	{57,56,55 ,35,35,35 ,2,6,7 }, {55,54,57 ,35,35,35 ,7,3,2 }, {51,52,56 ,36,36,36 ,2,6,7 },
	{56,57,51 ,36,36,36 ,7,3,2 }, {55,53,50 ,37,37,37 ,6,7,3 }, {50,54,55 ,37,37,37 ,3,2,6 },
	{56,52,53 ,6,6,6 ,6,7,3 }, {53,55,56 ,6,6,6 ,3,2,6 }, {50,51,57 ,7,7,7 ,7,3,2 },
	{57,54,50 ,7,7,7 ,2,6,7 }
};
static GLfloat vertices [58][3] = {
{-0.101707f,0.102742f,0.5f},{0.471442f,0.102742f,0.215198f},{0.444702f,0.0705465f,0.226369f},
{-0.0766527f,0.0705465f,0.485435f},{-0.457094f,0.102742f,-0.215198f},{-0.430355f,0.0705465f,-0.22637f},
{0.0910007f,0.0705465f,-0.485435f},{0.116054f,0.102742f,-0.5f},{-0.471442f,-0.141666f,-0.14168f},
{-0.39596f,-0.141666f,-0.179188f},{-0.412782f,-0.0690224f,-0.17083f},{-0.318396f,-0.0690224f,0.0191155f},
{-0.301574f,-0.141666f,0.010757f},{-0.377056f,-0.141666f,0.0482651f},{-0.226076f,-0.141627f,0.340461f},
{-0.152459f,-0.141627f,0.488613f},{-0.0926456f,-0.141627f,0.458891f},{-0.166263f,-0.141627f,0.310739f},
{-0.189267f,-0.058023f,0.414536f},{-0.129455f,-0.058023f,0.384816f},{0.117837f,0.102742f,-0.49641f},
{-0.45531f,0.102742f,-0.211609f},{-0.10349f,0.102742f,0.496411f},{0.469658f,0.102742f,0.211609f},
{-0.168737f,0.375181f,-0.35401f},{0.183084f,0.375181f,0.35401f},{-0.380607f,-0.141666f,0.0426715f},
{-0.305608f,-0.141666f,0.00540549f},{-0.305608f,-0.156651f,0.00540549f},{-0.380607f,-0.156651f,0.0426715f},
{-0.469128f,-0.141666f,-0.135475f},{-0.469128f,-0.156651f,-0.135475f},{-0.39413f,-0.156651f,-0.172741f},
{-0.39413f,-0.141666f,-0.172741f},{-0.376265f,-0.156651f,0.0300879f},{-0.31826f,-0.156651f,0.00126409f},
{-0.31826f,-0.308017f,0.00126409f},{-0.376265f,-0.308017f,0.0300879f},{-0.456477f,-0.156651f,-0.131333f},
{-0.456477f,-0.308017f,-0.131333f},{-0.398471f,-0.308017f,-0.160157f},{-0.398471f,-0.156651f,-0.160157f},
{-0.158094f,-0.141627f,0.483232f},{-0.09353f,-0.141627f,0.45115f},{-0.09353f,-0.158491f,0.45115f},
{-0.158094f,-0.158491f,0.483232f},{-0.225192f,-0.141627f,0.348202f},{-0.225192f,-0.158491f,0.348202f},
{-0.160628f,-0.158491f,0.31612f},{-0.160628f,-0.141627f,0.31612f},{-0.0773396f,0.0705465f,0.483771f},
{0.44379f,0.0705465f,0.224817f},{0.44379f,-0.375181f,0.224817f},{-0.0773396f,-0.375181f,0.483771f},
{-0.429443f,0.0705465f,-0.224817f},{-0.429443f,-0.375181f,-0.224817f},{0.0916872f,-0.375181f,-0.483771f},
{0.0916872f,0.0705465f,-0.483771f}
};
static GLfloat normals [38][3] = {
{-0.666241f,-0.668223f,0.331061f},{-0.666236f,-0.668228f,0.331059f},{-0.666246f,-0.668217f,0.331063f},
{0.444229f,-0.058736f,0.893986f},{-0.444229f,-0.05874f,-0.893986f},{0.666245f,-0.668217f,-0.331063f},
{0.0f,-1.0f,0.0f},{0.0f,1.0f,0.0f},{-0.445003f,-6.09991e-06f,-0.895529f},
{0.445003f,6.77216e-06f,0.895529f},{0.867015f,0.250346f,-0.430828f},{-0.665077f,0.669667f,0.330483f},
{-0.895532f,7.95888e-06f,0.444997f},{0.895532f,6.35045e-06f,-0.444997f},{-0.316334f,0.703327f,-0.636603f},
{-0.31633f,0.703325f,-0.636607f},{-0.316337f,0.70333f,-0.636599f},{0.31633f,0.703325f,0.636608f},
{-0.444996f,-2.17419e-06f,-0.895532f},{0.444997f,7.01885e-07f,0.895532f},{-0.580529f,0.761427f,0.28847f},
{0.580529f,0.761428f,-0.28847f},{0.444985f,0.0f,0.895538f},{-0.444986f,0.0f,-0.895537f},
{0.895533f,0.0f,-0.444995f},{-0.895533f,0.0f,0.444995f},{0.445001f,0.0f,0.89553f},
{-0.445001f,0.0f,-0.89553f},{0.895532f,0.0f,-0.444996f},{-0.895532f,0.0f,0.444996f},
{0.444999f,0.0f,0.895531f},{-0.444995f,0.0f,-0.895533f},{0.895532f,0.0f,-0.444998f},
{-0.895531f,0.0f,0.444999f},{0.444997f,0.0f,0.895532f},{-0.444997f,0.0f,-0.895532f},
{0.895532f,0.0f,-0.444997f},{-0.895532f,0.0f,0.444997f}
};
static GLfloat textures [10][2] = {
{0.997628f,0.0f},{0.00237162f,0.0f},{0.0f,1.0f},
{1.0f,1.0f},{0.0451833f,0.0f},{0.954817f,0.0f},
{0.0f,0.0f},{1.0f,0.0f},{0.222855f,0.0f},
{0.5f,0.0f}
};
/*Material indicies*/
/*{material index,face count}*/
static int material_ref [39][2] = {
{0,2},
{1,2},
{2,2},
{1,2},
{3,2},
{1,2},
{4,1},
{1,1},
{5,2},
{1,2},
{6,2},
{7,1},
{1,1},
{8,2},
{9,2},
{1,2},
{10,1},
{1,1},
{11,2},
{12,2},
{1,4},
{13,2},
{1,2},
{14,2},
{15,2},
{1,4},
{16,2},
{1,2},
{17,2},
{1,6},
{18,2},
{1,2},
{19,2},
{20,2},
{1,4},
{21,2},
{22,2},
{23,2},
{1,4}
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
  //MyMaterial (GL_SPECULAR, materials[i].specular,alpha);
  //MyMaterial (GL_EMISSION, materials[i].emission,alpha);
  //glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,materials[i].phExp);
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
 int k;
 int l;

for(i=0;i<23;i++)
  {
    GLuint texture_name;
    glGenTextures(1,&texture_name);
    texture_maps[i].id=texture_name;
    glBindTexture(GL_TEXTURE_2D,texture_name);
    LoadTexture(texture_maps[i].name);
  }

 GLint lid=glGenLists(1);
	int mcount=0;
	int mindex=0;
   glNewList(lid, GL_COMPILE);

   for (k=0; k < 58; k++ ) {
	   for (l=0; l < 3; l++ ) {
			vertices[k][l] = 2.0f*vertices[k][l];
	   }
   }

	glRotatef( 65.0f, 0.0f, 1.0f, 0.0f);

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