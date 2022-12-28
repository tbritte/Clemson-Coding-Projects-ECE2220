/* BMP.h header file to house all the typedef structs functions and fucntion
parameters being called through this project.
*/
//typedef for Header information for read
typedef struct HEADER {
  unsigned short int Type;
  unsigned int Size;
  unsigned short int Reserved1, Reserved2;
  unsigned int Offset;
}
Header;

//typedef for INFOHEADER information for read
typedef struct INFOHEADER {
  unsigned int Size;
  int Width, Height;
  unsigned short int Planes;
  unsigned short int Bits;
  unsigned int Compression;
  unsigned int ImageSize;
  int xResolution, yResolution;
  unsigned int Colors;
  unsigned int ImportantColors;
}
Infoheader;

//Grab all the RGB in bmp files
typedef struct PIXEL {
  unsigned char Red, Green, Blue;
}
PIXEL;

//Get rows and columns from the BMP files
//Also call in the PIXEL struct
typedef struct BMP {
  int Width, Height;
  PIXEL ** Pixels;
}
BMP;

//All functions that were used through the project
void getHeaders(FILE * infile, Header * inputHead, Infoheader * inputInfo);
void printHeaders(Header * inputHead, Infoheader * inputInfo, FILE * Opread);
void printBytes(FILE * fp, FILE * Opread);
void printPixels(BMP * pixelArray, FILE * Opread);
BMP * allocatePixelArray(int w, int h);
void populatePixelArray(BMP * pixelArray, FILE * infile);
void findEdges(BMP * oldPixels, BMP * newPixels);
void bmp_write(FILE * outputFile, BMP * pixelArray, Header * inputHead, Infoheader * inputInfo);
