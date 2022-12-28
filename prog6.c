/*  Tyrese Britten
    Systems Programming , Fall 2021
    Program 6
    This program is display information and different configuration of a BMP image.
    This process is called image process and this will be done with multipile files
    to read in data from bmp files imported over the terminal. We can display
    the information of that img and get edge detection so show a different
    side of that image.
*/

// Libraries that was were used for this project
#include <stdio.h>

#include <unistd.h>

#include <ctype.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

#include "bmp.h"

//BMP.c functions called in main
int main(int argc, char * argv[]){
  //Variables that are declared
  char *input1 = argv[1];
  char *input2 = argv[2];
  char Newname[256];
  FILE *fp;
  FILE *Opedge;
  FILE *Opread;
  char *input3 = argv[3];
  Opread = fopen(input3, "w");
  fp = fopen(argv[2], "r");

  BMP	*inputImage=NULL, *outputImage=NULL;



  struct HEADER inputHead;
  struct INFOHEADER inputInfo;
  //Checks to see if there are too many command line arguments
  if (argc > 4){
    printf("Invalid command line args\n");
    printf("Valid args: ./executable read filename.bmp\n");
    exit(1);
  }

  //Get the headers, pixels and space to do what is needed
  getHeaders(fp, &inputHead, &inputInfo);
  inputImage = allocatePixelArray(inputInfo.Width, inputInfo.Height);
  populatePixelArray(inputImage, fp);

//If, else if and else statment to do what is desired
//Read date here
  if (!strcmp(input1,"read") || !strcmp(input1,"Read")){
    printf("\n");
    //Information Printed to output.txt file
    fprintf(Opread,"%s\n", input2);
    printHeaders(&inputHead, &inputInfo, Opread);
    printBytes(fp, Opread);
    printPixels(inputImage, Opread);
}
  //Edge  detection
  else if (!strcmp(input1,"edge") || !strcmp(input1,"Edge")){
    //Change the name of bmp file to show where the edge detection worked
    strcpy(Newname,argv[2]);
    Newname[strlen(Newname) - 4] = 0;
    strcat(Newname, "-edge.bmp");
    Opedge = fopen(Newname, "w");

    //Check to see there is something in the edge file
    if(Opedge == NULL) {
       printf("Cannot create output file: %s\n", Newname);
       exit(1);
    }

    //Gets space, finds the edge and writes the information to a new file
    outputImage = allocatePixelArray(inputInfo.Width, inputInfo.Height);
    findEdges(inputImage, outputImage);
    bmp_write(Opedge, outputImage, &inputHead, &inputInfo);

  }
  else{
    printf("Please give a valid option for your second command argument\n");
    return 0;
  }
}
