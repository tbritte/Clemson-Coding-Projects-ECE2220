/*  Tyrese Britten
    Systems Programming , Spring 2022
    Program 3
    This program is teaching the class about bitwise operators
    and how to change differetn binary bits and gave a conversion
    to different bases. These bases are from 4,8, and to 16.
*/

#include <stdio.h>

#include <ctype.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

/* This Function is used to reverse the end output of the values */
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

/* These three functions will get the entry input that the user input. Then
will convert to a binary value. This will be used in the conversion to
different bases.
*/

void QuaternarytoBin(char * QuatOut, char bin[32]) {

  long int i = 0;

  while (QuatOut[i]) {

    switch (QuatOut[i]) {
    case '0':
      strcat(bin, "00");
      break;
    case '1':
      strcat(bin, "01");
      break;
    case '2':
      strcat(bin, "10");
      break;
    case '3':
      strcat(bin, "11");
      break;
    default:
      printf("\nInvalid octaldecimal digit %c",
        QuatOut[i]);
    }
    i++;
  }
    printf("bin string: %s", bin);

}
void OctalToBin(char * OctalOut, char bin[32]) {

  long int i = 0;

  while (OctalOut[i]) {

    switch (OctalOut[i]) {
    case '0':
      strcat(bin, "000");
      break;
    case '1':
      strcat(bin, "001");
      break;
    case '2':
      strcat(bin, "010");
      break;
    case '3':
      strcat(bin, "011");
      break;
    case '4':
      strcat(bin, "100");
      break;
    case '5':
      strcat(bin, "101");
      break;
    case '6':
      strcat(bin, "110");
      break;
    case '7':
      strcat(bin, "111");
      break;
    default:
      printf("\nInvalid octaldecimal digit %c",
        OctalOut[i]);
    }
    i++;
  }

  printf("bin string: %s", bin);

}
void HexToBin(char * hexOut, char bin[32]) {

  long int i = 0;

  while (hexOut[i]) {

    switch (hexOut[i]) {
    case '0':
      strcat(bin, "0000");
      break;
    case '1':
      strcat(bin, "0001");
      break;
    case '2':
      strcat(bin, "0010");
      break;
    case '3':
      strcat(bin, "0011");
      break;
    case '4':
      strcat(bin, "0100");
      break;
    case '5':
      strcat(bin, "0101");
      break;
    case '6':
      strcat(bin, "0110");
      break;
    case '7':
      strcat(bin, "0111");
      break;
    case '8':
      strcat(bin, "1000");
      break;
    case '9':
      strcat(bin, "1001");
      break;
    case 'A':
    case 'a':
      strcat(bin, "1010");
      break;
    case 'B':
    case 'b':
      strcat(bin, "1011");
      break;
    case 'C':
    case 'c':
      strcat(bin, "1100");
      break;
    case 'D':
    case 'd':
      strcat(bin, "1101");
      break;
    case 'E':
    case 'e':
      strcat(bin, "1110");
      break;
    case 'F':
    case 'f':
      strcat(bin, "1111");
      break;
    default:
      printf("\nInvalid hexadecimal digit %c",
        hexOut[i]);
    }
    i++;
  }

  printf("bin string: %s", bin);
}

/* These three functions will convert from binary in to different
bases that will be shown to the user.
*/

void bintoOctal(char *binvalue){
  long int i = strlen(binvalue)-3;
  char octStr[32] = "";
  char comp[4];
  while (i > 0) {


    comp[0]='\0';
    strncat(comp,&binvalue[i],3);

    if(strcmp(comp, "000") == 0){
      strcat(octStr, "0");
    }
    else if(strcmp(comp, "001") == 0){
      strcat(octStr, "1");
    }
    else if(strcmp(comp, "010") == 0){
      strcat(octStr, "2");
    }
    else if(strcmp(comp, "011") == 0){
      strcat(octStr, "3");
    }
    else if(strcmp(comp, "100") == 0){
      strcat(octStr, "4");
    }
    else if(strcmp(comp, "101") == 0){
      strcat(octStr, "5");
    }
    else if(strcmp(comp, "110") == 0){
      strcat(octStr, "6");
    }
    else if(strcmp(comp, "111") == 0){
      strcat(octStr, "7");
    }
    else {
      printf("\nInvalid digit %c", binvalue[i]);
    }

    i = i - 3;
  }
    strrev(octStr);
    printf(" O%s\n",octStr);
}
void bintoHex(char *binvalue){

  long int i = strlen(binvalue)-4;

  char hexstr[32] = "";

  char comp[5];

  while (i > 0) {

    comp[0]='\0';
    strncat(comp,&binvalue[i],4);

    if(strcmp(comp, "0000") == 0){
      strcat(hexstr, "0");
    }
    else if(strcmp(comp, "0001") == 0){
      strcat(hexstr, "1");
    }
    else if(strcmp(comp, "0010") == 0){
      strcat(hexstr, "2");
    }
    else if(strcmp(comp, "0011") == 0){
      strcat(hexstr, "3");
    }
    else if(strcmp(comp, "0100") == 0){
      strcat(hexstr, "4");
    }
    else if(strcmp(comp, "0101") == 0){
      strcat(hexstr, "5");
    }
    else if(strcmp(comp, "0110") == 0){
      strcat(hexstr, "6");
    }
    else if(strcmp(comp, "0111") == 0){
      strcat(hexstr, "7");
    }
    else if(strcmp(comp, "1000") == 0){
      strcat(hexstr, "8");
    }
    else if(strcmp(comp, "1001") == 0){
      strcat(hexstr, "9");
    }
    else if(strcmp(comp, "1010") == 0){
      strcat(hexstr, "A");
    }
    else if(strcmp(comp, "1011") == 0){
      strcat(hexstr, "B");
    }
    else if(strcmp(comp, "1100") == 0){
      strcat(hexstr, "C");
    }
    else if(strcmp(comp, "1101") == 0){
      strcat(hexstr, "D");
    }
    else if(strcmp(comp, "1110") == 0){
      strcat(hexstr, "E");
    }
    else if(strcmp(comp, "1111") == 0){
      strcat(hexstr, "F");
    }
    else {
      printf("\nInvalid digit %c", binvalue[i]);
    }

    i = i - 4;
  }
    strrev(hexstr);
    printf(" H%s\n",hexstr);
}
void bintoQuat(char *binvalue){

  long int i = strlen(binvalue)-2;

  char Quatstr[32] = "";

  char comp[5];

  while (i > 0) {

    comp[0]='\0';
    strncat(comp,&binvalue[i],2);

    if(strcmp(comp, "00") == 0){
      strcat(Quatstr, "0");
    }
    else if(strcmp(comp, "01") == 0){
      strcat(Quatstr, "1");
    }
    else if(strcmp(comp, "10") == 0){
      strcat(Quatstr, "2");
    }
    else if(strcmp(comp, "11") == 0){
      strcat(Quatstr, "3");
    }
    else {
      printf("\nInvalid digit %c", binvalue[i]);
    }

    i = i - 2;
  }
    strrev(Quatstr);
    printf(" Q%s\n",Quatstr);
}

//Print out the options
void menu() {
  printf("Enter a Q for quaternary (base 4) \n");
  printf("Enter a O for octal (base 8) \n");
  printf("Enter a H for hexadecimal (base 16) \n");
  printf("Enter a C to Clear Data) \n");
  printf("Up to 32 digits\n");
  printf("Enter L to Quit \n");
  printf("\n");
}

/* The main function. FOR THESE TO WORK YOU WILL HAVE TO
PRESS C TO CLEAR THE DATA TO GET THE REST OF THE TEST CASES
*/
int main(void){
  char userinput[10];
  char first_letter;
  char binStr[32] = "0000";
  while (true) {
    menu();
  scanf("%s", userinput);
  first_letter = userinput[0];


  if(first_letter == 'Q' || first_letter == 'q' ){
    QuaternarytoBin(userinput+1, binStr);
    bintoOctal(binStr);
    bintoHex(binStr);

  } else if(first_letter == 'H'|| first_letter == 'h'){

    HexToBin(userinput+1, binStr);
    bintoOctal(binStr);
    bintoQuat(binStr);

  } else if(first_letter == 'O'|| first_letter == 'o'){
    OctalToBin(userinput+1, binStr);
      bintoHex(binStr);
      bintoQuat(binStr);

  }
  else if (first_letter == 'c' || first_letter == 'C'){
    printf("Clearing Data\n");
      system("clear");
      return 0;
    }
  else if (first_letter == 'L' || first_letter == 'l'){
    printf("Quit\n");
      return 0;
  }
 }
}
