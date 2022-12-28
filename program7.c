/*  Tyrese Britten
    Systems Programming , Spring 2022
    Program 7
    This Project is to test the knowledge of using for
    of fork(), getpid(), wait(), signal(), alarm() and kill(). With these 
    functions we will be able to create a farm simulator game that the user will be
    managing plants. The user will be on the clock to get three plants to grow successfully 
    and get them ship out to a farmer. If they aren't maintain then they will die and the loser will 
    lose the game. There will be four integer (int) global variables that will be made and used for this
    program. 
   
*/

// Libraries that was were used for this project
#include <stdio.h>

#include <unistd.h>

#include <ctype.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

#include <time.h>

#include <signal.h>

/* Global variables that will be used throughout these program.
 Dr Reid said 4/29/2022 that we could use global variables for this assignment.
*/
int water, fert, plantNum;


/* Void write function that will be used to write in words into
the child process about the plant status. In this function it takes in 
a pointer and integer into it to be able to do what we need to do. Next 
strcat is used to echo the process being used and displays the number
*/
void write_term(char *string, int number){

  char saying[200];
  char num_str[4];
  sprintf(num_str, "%d", number);
  strcpy(saying, "echo \"");
  strcat(saying, string);
  strcat(saying,"\" > /dev/pts/");
  strcat(saying, num_str);
  system(saying);

}

/*Void print inventory is used to print out the fertilizer and water of each plant. We do
the same process from void write_term function. I forgot to mention to say about 
sprintf is used for the decimal values that will be used to get the value that will be decaying 
from the water and fertilizer
*/
void print_inventory() {
  char plant_saying[300] = "";
  char plantNumS[2], pidS[10], fertS[10], waterS[10];
  sprintf(plantNumS, "%d", plantNum);
  sprintf(pidS, "%d", getpid());
  sprintf(fertS, "%d", fert);
  sprintf(waterS, "%d", water);
  strcat(plant_saying, "Plant ");
  strcat(plant_saying, plantNumS);
  strcat(plant_saying, ": ");
  strcat(plant_saying, pidS);
  strcat(plant_saying, " - ");
  strcat(plant_saying, fertS);
  strcat(plant_saying, "mg of fertilizer left \n\t\t");
  strcat(plant_saying, waterS);
  strcat(plant_saying, " mL of water left");
  write_term(plant_saying, plantNum);
}

/* Void make_plant function that is making the format of the plant itself. This function 
will be called in the child process of the program. Write_term and print_inventory
will be called in this function to get the accruate picture.
*/
void make_plant(int day_num, int term){

  char day[4];
  char day_str[100] = "Day ";

  sprintf(day, "%d", day_num);
  strcat(day_str, day);
  write_term(day_str, term);
  write_term("\t  \\|/", term);
  write_term("\t --|--", term);
  for(int i = 1 ; i <= day_num; i++){ 
    write_term("\t  | |", term); 
  }
   
  write_term("-------------------------", term);
  print_inventory();
}

/* Int isNumber function that is made to get the integer value of the path in main. Path is to 
make sure the program recognize how many terminals are open. Also being able to write to those terminals.
*/
int isNumber(char s[]) {
  for (int i = 0; s[i] != '\0'; i++) {
    if (isdigit(s[i])) {
      return 1;
    }
  }
  return 0;
}

/* Void getchild function is used to get the process number of the the child processes. 
These processes will return 1,2 and 3 to get the right number to be printed out elsewhere 
in the program. 
*/
int getChild(int child1, int child2, int child3) {
  if (child1 == 0) {
    return 1;
  }

  else if (child2 == 0) {
    return 2;
  }
  else if (child3 == 0) {
    return 3;
  }
  return 0;
}

/* Void print_pids function that is geeting the pids of the child and printing out the number of 
each id for which plant is being looked at. 
*/
void print_pids(pid_t pids[3]){
  for (int i = 0; i < 3; i++) {
    printf("Plant %d: %d\n", i+1, pids[i]);
  }
}

/* Void function that is used to and water to the plant. This function
will be called multiple times in main
*/
void water_input(int signum){
  water = water + 200;
  print_inventory();
}

/*Void function that is used to and water to the plant. This function
will be called multiple times in main
*/
void fert_input(int signum){
  fert = fert + 2000;
  print_inventory();
}

/* Function main. In this function this is where the time is displayed and the parent and child process are 
called and used for this project. Once we have the child processes working then we can call the functions we made above
into each child process and get what is needed. The values of water and fertilizer are in thousands to make it 
easier to work with in the decay of the plant. The feed, water, pid and q process is in a do loop so 
when each key is pressed then it will be work as intended
*/
int main(int argc, char * argv[]){
  char number;
  char *thing;
  time_t t; 
  time(&t);

  printf("\nTime and Date: %s", ctime(&t));
  FILE *fp;
  char path[1035];
  fp = popen("ls /dev/pts/", "r");

  int terminals[4]; 
  int num_of_terms = 0;
  while (fgets(path, sizeof(path), fp) != NULL) {
    if (isNumber(path)) {
      terminals[num_of_terms++] = atoi(path);
    }
  }
  pclose(fp);

  pid_t pids[3];
  int child1, child2, child3;
  bool child = false;
  child1 = fork();

  if (child1 != 0) {
    child2 = fork();
  }

  if (child1 != 0 && child2 != 0) {
    child3 = fork();
  }

  if (getChild(child1, child2, child3) > 0) {
    child = true;
    plantNum = getChild(child1, child2, child3);
    signal(SIGUSR1, fert_input);
    signal(SIGUSR2, water_input);
  }

  if (!child) {
    pids[0] = child1;
    pids[1] = child2;
    pids[2] = child3;
  }

  fert = 10000;
  water = 1000;

  time_t decay, decay_next;
  time(&decay);
  
  time_t grow, grow_next;
  time(&grow);

  srand((unsigned) decay * getChild(child1, child2, child3));

  int day = 1;
  if (child)
    make_plant(day, getChild(child1, child2, child3));
  day++;


  do {
    double decay_sec, grow_sec;

    if (child) {
      time(&decay_next);
      time(&grow_next);
  
      if (water <= 0 || fert <= 0) {
        printf("Plant %d has died.\n", getChild(child1, child2, child3));
        kill(getpid(), SIGKILL);
      }

      if (day > 10) {
        printf("Plant %d ready to be sold!\n", getChild(child1, child2, child3));
        kill(getpid(), SIGKILL);
      }

      decay_sec = difftime(decay, decay_next);
      if (decay_sec < -1) {
        time(&decay);
        water = water - (rand() % 200) - 100;
        fert = fert - (rand() % 2000) - 1000;

        if(water < 500){
          char print_water[100] = "";
          char plantW[2];

          sprintf(plantW, "%d", getChild(child1, child2, child3));
          strcat(print_water, "Plant ");
          strcat(print_water, plantW);
          strcat(print_water, " needs more water.\n");

          write_term(print_water, getChild(child1, child2, child3));
          printf("%s",print_water);
        }

        if (fert < 5000) {
          char print_fert[100] = "";
          char plantF[2];

          sprintf(plantF, "%d", getChild(child1, child2, child3));
          strcat(print_fert, "Plant ");
          strcat(print_fert, plantF);
          strcat(print_fert, " needs more fertilizer.\n");

          write_term(print_fert, getChild(child1, child2, child3));
          printf("%s",print_fert);
        }
      }

      if (water <= 0 || fert <= 0) {
        printf("Plant %d has died.\n", getChild(child1, child2, child3));
        write_term("This plant has died.\n", getChild(child1, child2, child3));
        kill(getpid(), SIGKILL);
      }

      grow_sec = difftime(grow, grow_next);
      if (grow_sec < -5) {
        time(&grow);

        
        make_plant(day, getChild(child1, child2, child3));
        day++;
      }
    } else {
      char input;
      input = getchar();

      if (input == 's') {
        print_pids(pids);
      }

      if (input == 'f') {
        char childChar = getchar();
        
        int childNum = childChar - '0';
        
        kill(pids[childNum-1], SIGUSR1);
      }

      if (input == 'w') {
        char childChar = getchar();
        int childNum = childChar - '0';
        
        kill(pids[childNum-1], SIGUSR2);
      }

      if (input == 'q') {
        for (int i = 0; i < 3; i++) {
          kill(pids[i], SIGKILL);
          write_term("Plant Killed\n", i+1);
        }
        kill(getpid(), SIGKILL);
      }
    }
  } while(true);
  
  return 0;

}
