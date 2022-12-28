/*  Tyrese Britten
    Systems Programming , Fall 2022
    Program 1
    This project is to refresh students minds of the
    intro to C course CPSC1110. The concepts we used are functions,
    manipulation arrays, uses loops and used the math library.
*/

// Libraries that are used for this program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



//Function to display the menu
void menu() {
  printf("1. e(x) (exp()) \n");
  printf("2. ln(x) (log()) \n");
  printf("3. sine(x) (sin()) \n");
  printf("4. cosine(x) (cos()) \n");
  printf("5. tangent(x) (tan()) \n");
  printf("6. Exit file \n");
}
//Input function asking min and max
void value(float* max, float* min){
do{
  printf("Please enter a minimum value\n");
   scanf("%f", min);
   printf("Please enter a maximum value\n");
    scanf("%f", max);
    if(*min > *max){
    printf("Please enter a minimum value that is not greater than maximum\n");
    }
  }while (*min > *max);

}

//Input function asking rows and columns
void square(int* rows, int* columns){
  do{
    printf("Please enter a row value\n");
    scanf("%d", rows);
    printf("Please enter a column value\n");
    scanf("%d", columns);
    if(*rows == 50){
      printf("You have reached the max rows\n");
    }
    else if(*columns == 200){
    printf("You have reached the max columns\n");
    }
  }while (*rows == 50 || *columns == 200);
}
/*
For the data function length_c is the height or the columns of the graph. plot is
to hold the values for the x's. Output is a matrix of output Input. Choices is
the variable that gets the choices from main.
*/

float data(int r, int c, int length_c, float *m_out, float plot, float output[300], int choices){
  float width_r = 0.00, minimum = 10000000, last_in [300];
  for(int i = 0; i <= (c-1); i++){
    last_in[i] = plot+(i*length_c);
    if(choices == 1){
      output[i] = exp(last_in[i]);
    }
    else if(choices == 2){
      output[i] = log(last_in[i]);
    }
    else if(choices == 3){
      output[i] = sin(last_in[i]);
    }
    else if(choices == 4){
      output[i] = cos(last_in[i]);
    }
    else if(choices == 5){
      output[i] = tan(last_in[i]);
    }
  if (output[i] > *m_out) {
    *m_out = output[i];
  }
  else if (output[i] < minimum){
    minimum = output[i];
  }
}
  width_r = (*m_out-minimum)/(r-1);
  return width_r;
}
/* The graph function is to get the information from the data and configure it
in this function. The width_r is the rows that are for the x values of the graph.
The m_out is the ax output from the data.
*/

void graph(int r, int c, int bin[50][200], float hold[50], float output[300], float width_r, float *m_out){
int dum1= 0, dum2 = 1;
  for(int i = 0; i <= (r-1) ; i++){
    hold[i] = ((*m_out) - (i*width_r));
      for(int k = 0; k <= (c-1); k++){
    if(output[k] < hold[i]){
      bin[i][k] = dum1;
    }
      else if(output[k] >= hold[i]){
        output[k] = -100000;
        bin[i][k] = dum2;
      }
    }
  }
}

/* This is the output function that will store all the variables.
The variable bin is the matrix that holds all the math functions.
Hold holds all the variables that will be printed out to the function.
*/

void output_plot(int r, int c, int bin[50][200], float hold[50]){
  float counter = 0.00;
  for(int i=0; i <= (r-1); i++){
    printf("%02d\n", ((r-1)-i));
    if (hold[i] > counter){
      printf("%+16.2f\n", hold[i]);
    }
      else{
        printf("%+16.2f\n", hold[i]);
      }
      for(int j = 0; j<= (c-1); j++){
        if(bin[i][j] == 1){
          printf("X");
        }
        else if(bin[i][j] == 0){
          fprintf(stdout,"%c",' ');
        }
        else if (j == (c-1)){
          printf("\n");
        }
      }
    }
  }
/* Main is the user interface. This is where all the functions are called and
give out the desired output.
*/
int main(void) {
float max = 0.00, min = 0.00, plot=0.00, output[300];
float length_c = 0.00, width_r= 0.00;
float m_out = 10000000, hold[300];
int rows=0, columns = 0, choices;
int bin[50][200];

  while (true){
menu();
printf("Please enter a number between 1-6 to choose in menu\n");
   scanf("%d", &choices);
   length_c = (max-min)/(columns-1);
    if (choices == 1){
    value(&max, &min);
    square(&rows, &columns);
    width_r = data(rows, columns, length_c, &m_out, plot, output, choices);
    graph(rows, columns, bin, hold, output, width_r, &m_out);
    output_plot(rows, columns, bin, hold);
}
    if (choices == 2){
      value(&max, &min);
      square(&rows, &columns);
      width_r = data(rows, columns, length_c, &m_out, plot, output, choices);
      graph(rows, columns, bin, hold, output, width_r, &m_out);
      output_plot(rows, columns, bin, hold);
    }
    if (choices == 3){
      value(&max, &min);
      square(&rows, &columns);
      width_r = data(rows, columns, length_c, &m_out, plot, output, choices);
      graph(rows, columns, bin, hold, output, width_r, &m_out);
      output_plot(rows, columns, bin, hold);
    }
    if (choices == 4){
      value(&max, &min);
      square(&rows, &columns);
      width_r = data(rows, columns, length_c, &m_out, plot, output, choices);
      graph(rows, columns, bin, hold, output, width_r, &m_out);
      output_plot(rows, columns, bin, hold);
    }
    if (choices == 5){
      value(&max, &min);
      square(&rows, &columns);
      width_r = data(rows, columns, length_c, &m_out, plot, output, choices);
      graph(rows, columns, bin, hold, output, width_r, &m_out);
      output_plot(rows, columns, bin, hold);
    }
    else if (choices == 6) {
      printf("Exit \n");
      return 0;
      }
    }
  }
