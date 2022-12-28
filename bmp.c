
/*  BMP.c file housing all the functions and the instructions
that are used in program.c
*/

// Libraries that was were used for this project
#include <stdio.h>

#include <unistd.h>

#include <ctype.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

#include "bmp.h"

//Gets the headers from the structs in bmp.h
void getHeaders(FILE * infile, Header * inputHead, Infoheader * inputInfo) {
  //Read in the data from the input BMP files
  fread(&inputHead->Type, sizeof(inputHead->Type), 1, infile);
  fread(&inputHead->Size, sizeof(inputHead->Size), 1, infile);
  fread(&inputHead->Reserved1, sizeof(inputHead->Reserved1), 1, infile);
  fread(&inputHead->Reserved2, sizeof(inputHead->Reserved2), 1, infile);
  fread(&inputHead->Offset, sizeof(inputHead->Offset), 1, infile);
  fread(&inputInfo->Size, sizeof(inputInfo->Size), 1, infile);
  fread(&inputInfo->Width, sizeof(inputInfo->Width), 1, infile);
  fread(&inputInfo->Height, sizeof(inputInfo->Height), 1, infile);
  fread(&inputInfo->Planes, sizeof(inputInfo->Planes), 1, infile);
  fread(&inputInfo->Bits, sizeof(inputInfo->Bits), 1, infile);
  fread(&inputInfo->Compression, sizeof(inputInfo->Compression), 1, infile);
  fread(&inputInfo->ImageSize, sizeof(inputInfo->ImageSize), 1, infile);
  fread(&inputInfo->xResolution, sizeof(inputInfo->xResolution), 1, infile);
  fread(&inputInfo->yResolution, sizeof(inputInfo->yResolution), 1, infile);
  fread(&inputInfo->Colors, sizeof(inputInfo->Colors), 1, infile);
  fread(&inputInfo->ImportantColors, sizeof(inputInfo->ImportantColors), 1, infile);
}

//Display Read data
void printHeaders(Header * inputHead, Infoheader * inputInfo, FILE *Opread) {
  //Print out read data to an outputFile from terminal
  fprintf(Opread,"Type: %c\n", inputHead->Type);
  fprintf(Opread,"Type: %c\n", inputHead->Type+11);
  fprintf(Opread,"Size: %d\n", inputHead->Size);
  fprintf(Opread,"Offset: %d\n", inputHead->Offset);
  fprintf(Opread,"Size: %d\n", inputInfo->Size);
  fprintf(Opread,"Width: %d\n", inputInfo->Width);
  fprintf(Opread,"Height: %d\n", inputInfo->Height);
  fprintf(Opread,"Planes: %d\n", inputInfo->Planes);
  fprintf(Opread,"Bits: %d\n", inputInfo->Bits);
  fprintf(Opread,"Compression: %d\n", inputInfo->Compression);
  fprintf(Opread,"ImageSize: %d\n", inputInfo->ImageSize);
  fprintf(Opread,"xResolution: %d\n", inputInfo->xResolution);
  fprintf(Opread,"yResolution: %d\n", inputInfo->yResolution);
  fprintf(Opread,"Colors: %d\n", inputInfo->Colors);
  fprintf(Opread,"ImportantColors: %d\n", inputInfo->ImportantColors);
}

//Print the bytes int BMP files
void printBytes(FILE *fp, FILE *Opread) {
  rewind(fp);
  unsigned char c;
  for (int i = 0; i < (sizeof(Header) + sizeof(Infoheader)); i++) {
    c = getc(fp);
    fprintf(Opread,"Byte[%d] = %03u\n", i, c);

  }
}
//Prints out the RGB colors in every BMP file
void printPixels(BMP *pixelArray, FILE *Opread){
  unsigned char r, g, b;
  int rows, cols;

  for (rows = 0; rows < pixelArray->Height; rows++){
    for(cols = 0; cols < pixelArray->Width; cols++){

        r = pixelArray->Pixels[rows][cols].Red;
        g = pixelArray->Pixels[rows][cols].Green;
        b = pixelArray->Pixels[rows][cols].Blue;
        fprintf(Opread,"RGB[%d,%d] = %03u.%03u.%03u\n",rows, cols,b,g,r);
    }
    if(cols%2 != 0)
    fprintf(Opread,"Padding[%d] = %03d\n", rows, rows);
  }

}

//Allocate Space for pixels from BMP files
BMP *allocatePixelArray(int w, int h){
int		i;

  BMP *pixelArray = NULL;
  pixelArray = (BMP *)malloc(sizeof(BMP));

 pixelArray->Width = w;
 pixelArray->Height = h;
 pixelArray->Pixels = (PIXEL**)malloc(h*w*sizeof(PIXEL));


 for (i = 0; i < h; i++){
     pixelArray->Pixels[i] = (PIXEL*)malloc(w*sizeof(PIXEL));
}

 //goes into populatePixelArray
 if(!pixelArray) {
   fprintf(stderr,"WARNING: could not allocate memory for img\n");
 }

 return pixelArray;
}

//Populate arrays that will be used in edge detection
void populatePixelArray(BMP *pixelArray, FILE *infile){

int	rows, cols;
PIXEL px;

    for (rows = 0; rows < pixelArray->Height; rows++){
      for(cols = 0; cols < pixelArray->Width; cols++){
        if( (fread(&px,sizeof(PIXEL),1,infile) < 1) || feof(infile))
          fprintf(stderr,"Error getting PIXEL from file\n");

        pixelArray->Pixels[rows][cols] = px;

    }
      while (cols%2 != 0) {
         getc(infile);
        cols++;
      }
    }
}

//Find the edges in BMP files to desplay different image
void findEdges(BMP *oldPixels, BMP *newPixels) {
  int row,col,i,j;
  char Matrix[3][3] = {
    {0,-1,0},
    {-1,4,-1},
    {0,-1,0}
  };

  for (row = 0; row < oldPixels->Height; row++) {
    for (col = 0; col < oldPixels->Width; col++) {
        char r = 0 ,g = 0, b = 0;
      for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
          if (!((row+i < 0) || (row+i >= oldPixels->Height) || (col+j < 0) || (col+j >= oldPixels->Width))) {
            r = r + Matrix[i+1][j+1] * oldPixels->Pixels[row+i][col+j].Red;
            g = g + Matrix[i+1][j+1] * oldPixels->Pixels[row+i][col+j].Green;
            b = b + Matrix[i+1][j+1] * oldPixels->Pixels[row+i][col+j].Blue;
          }
        }
      }
      newPixels->Pixels[row][col].Red = r;
      newPixels->Pixels[row][col].Green = g;
      newPixels->Pixels[row][col].Blue = b;
    }
  }


}

//Writes in all information for read and edge detection
void bmp_write(FILE *outputFile, BMP *pixelArray, Header * inputHead, Infoheader * inputInfo){

	int		i,j;
  // write BMP header

  fwrite(&inputHead->Type, sizeof(inputHead->Type), 1, outputFile);
  fwrite(&inputHead->Size, sizeof(inputHead->Size), 1, outputFile);
  fwrite(&inputHead->Reserved1, sizeof(inputHead->Reserved1), 1, outputFile);
  fwrite(&inputHead->Reserved2, sizeof(inputHead->Reserved2), 1, outputFile);
  fwrite(&inputHead->Offset, sizeof(inputHead->Offset), 1, outputFile);
  fwrite(&inputInfo->Size, sizeof(inputInfo->Size), 1, outputFile);
  fwrite(&inputInfo->Width, sizeof(inputInfo->Width), 1, outputFile);
  fwrite(&inputInfo->Height, sizeof(inputInfo->Height), 1, outputFile);
  fwrite(&inputInfo->Planes, sizeof(inputInfo->Planes), 1, outputFile);
  fwrite(&inputInfo->Bits, sizeof(inputInfo->Bits), 1, outputFile);
  fwrite(&inputInfo->Compression, sizeof(inputInfo->Compression), 1, outputFile);
  fwrite(&inputInfo->ImageSize, sizeof(inputInfo->ImageSize), 1, outputFile);
  fwrite(&inputInfo->xResolution, sizeof(inputInfo->xResolution), 1, outputFile);
  fwrite(&inputInfo->yResolution, sizeof(inputInfo->yResolution), 1, outputFile);
  fwrite(&inputInfo->Colors, sizeof(inputInfo->Colors), 1, outputFile);
  fwrite(&inputInfo->ImportantColors, sizeof(inputInfo->ImportantColors), 1, outputFile);

PIXEL px;


for(i=0;i<pixelArray->Height;i++) {
    for(j=0;j<pixelArray->Width;j++) {
      px = pixelArray->Pixels[i][j];
      fwrite(&px, sizeof(PIXEL), 1, outputFile);
    }

    while (j%2 != 0) {
      unsigned char nChar = '0';
      fwrite(&nChar,sizeof(unsigned char),1,outputFile);
       j++;
    }
  }
}
