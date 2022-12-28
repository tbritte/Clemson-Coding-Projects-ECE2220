/*  Tyrese Britten
    Systems Programming , Spring 2022
    Program 2
    This program is doing all the variables with floats, strings,
    and integer values used for a specific task. That task is to input
    in information to store data of a company. This is used by making
    different instructions to complete this task. NOTE: The file that as been
    proved has be modified for the country Abbreviations  of the company.
    File will be given.
*/

/*  Disclaimer could get the countries to work with the abbreviations. One will 
be proved for the completeion fo the project */

// Libraries that were used for this project
#include <stdio.h>

#include <ctype.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

// Defining the function that were used
bool isValidString(char * theString);
bool isValidFloat(char * theString);
bool isValidInt(char * theString);
bool isValidString2(int theEntry);

//Char function to make sure the input is indeed a character
//Also to ask the user for the correct range of inputs
char * userStringEntry(char * entry, char * info) {
  printf("Enter %s \n", info);
  scanf("%s", entry);
  //If correct will return the entry from the user
  if (isValidString(entry)) {
    return entry;
    //If not throw error check
  } else {
    printf("Please enter valid %s\n", info);
    userStringEntry(entry, info);
  }

  return entry;
}
//Char function for check the txt file for the right country
char * usercountry(char * entry, char * info, FILE * fd2) {
  char line[5];

  printf("Enter %s\n", info);
  scanf("%s", entry);
  //Goes through the fil again and check to see if the input
  // Matchs the country in the file
  if (isValidString(entry)) {
    rewind(fd2);
    while (fgets(line, sizeof(line), fd2)) {
      line[strcspn(line, "\n")] = 0;
      if (strcmp(entry, line) == 0) {
        printf("%s", entry);
        return entry;
      }
    }
    //Throws error for not the right country in the file
    printf("Please enter valid %s\n", info);
    return usercountry(entry, info, fd2);
  } else {
    //Throws error for numbers
    printf("Please enter valid %s\n", info);
    return usercountry(entry, info, fd2);
  }

}

// Function Userentry for integers in main
int userEntry(int entry, char * info) {
  char stringEntry[32];

  printf("Enter %s \n", info);
  scanf("%s", stringEntry);
  //When enter it checks to see if the integer entry is in years
  //If so it will go through this conditional for the range
  if (isValidInt(stringEntry)) {
    entry = atoi(stringEntry);
    if (strcmp("FDA_approval", info) == 0) {
      if (entry == 0) {
        return entry;
      }
      //Throws error outside the range
      else {
        return userEntry(entry, info);
      }
      //Gives integer for other integers in main
    } else {
      return entry;
    }

  }
  //Throws error for not integer values
  else {
    printf("Please give a valid Input\n");
    return userEntry(entry, info);
  }
}

//Float function for floats in main
float userEntry2(float entry, char * info) {
  char stringEntry[32];

  printf("Enter %s \n", info);
  scanf("%s", stringEntry);
  //If it is a float then go through this conditional
  if (isValidFloat(stringEntry)) {
    entry = atof(stringEntry);
    return entry;
  }
  //Throws error if not in a float
  else {
    printf("Please give a valid Float\n");
    return userEntry2(entry, info);
  }
}

//float function to go itterate through the string the user put in
bool isValidFloat(char * theString) {
  for (int i = 0; i < strlen(theString); i++) {
    if (!isdigit(theString[i]) && (theString[i] != '.')) {
      return (false);
    }
  }
  return (true);
}

//Integer function to go itterate through the string the user put in
bool isValidInt(char * theString) {
  for (int i = 0; i < strlen(theString); i++) {
    if (!isdigit(theString[i])) {
      return (false);
    }
  }
  return (true);
}
//String  function to go itterate through the string the user put in
bool isValidString(char * theString) {
  for (int i = 0; i < strlen(theString); i++) {
    if (isdigit(theString[i])) {
      return (false);
    }
  }
  return (true);
}

// Void function for menu
void menu() {
  printf("1. Enter Company Information \n");
  printf("2. Enter Shot Information \n");
  printf("3. Enter Shot Application \n");
  printf("4. Display All Data\n");
  printf("5. Clear All Data\n");
  printf("6. Quit \n");
}

int main(void) {

  //These two lines are to grab the file and use it in main
  //Note File has be modified for the country Abbreviations

  FILE * fd2;
  fd2 = fopen("Country.txt", "r");

  // All the variables. With char variables there is double quotations
  //for blank space when they are not being used
  char Company_Name[32] = "";
  char Company_Country[32] = "";
  char E_mail[32] = "";
  int Shot_Doses = 0;
  int Company_Phone_Number = 0;
  float Shot_cost = 0.00;
  float Shot_Dosage = 0.00;
  int choices;
  int FDA_approval = 2 ;
  float Total_Shot_Sales = 0.00;
  int Total_Shot_Doses = 0;
  int Total_Shot_Injuries = 0;
  int Total_Shot_Deaths = 0;
  char line[5] = "";

  /*while loop to keep displaying the menu and the data for the input of the
  company */

  while (true) {
    menu();
    printf("Please pick a number between 1 - 6 to choose in menu \n");
    scanf("%d", & choices);
    //Choice 1, refer to menu
    if (choices == 1) {
      strcpy(Company_Name, userStringEntry(Company_Name, "Company Name"));
      printf("Country Abbreviations\n");
      while (fgets(line, sizeof(line), fd2)) {}
      strcpy(Company_Country, usercountry(Company_Country, "Company Country\n", fd2));
      Company_Phone_Number = userEntry(Company_Phone_Number, "Phone number");
      strcpy(E_mail, userStringEntry(E_mail, "E_mail"));

    }
    //Choice 2, refer to menu
    else if (choices == 2) {
      Shot_cost = userEntry2(Shot_cost , "Shot Cost in US Dollars");
      Shot_Doses = userEntry(Shot_Doses, "Recommended Shot Dosage");
      Shot_Dosage = userEntry2(Shot_Dosage , "Recommended Shot Dosage");
    }
    //Choice 3, refer to menu
    else if (choices == 3) {
      FDA_approval = userEntry(FDA_approval, "FDA Approval");
      Total_Shot_Doses = userEntry(Total_Shot_Doses, "Total Shot Doses Sold");
      Total_Shot_Sales = userEntry2(Total_Shot_Sales, "Total Shot Sales");
      Total_Shot_Injuries = userEntry(Total_Shot_Injuries, "Total Shot Injuries");
      Total_Shot_Deaths = userEntry(Total_Shot_Deaths, "Total Shot Deaths");
    }
    //Choice 1, refer to menu
    //Displays all the inputs
    else if (choices == 4) {
      printf("Displaying All Entries\n");
      printf("Company Information: %s %s %d %s \n", Company_Name, Company_Country,
       Company_Phone_Number, E_mail);
      printf("Shot Information $%0.2f, %d, %0.2f ml \n", Shot_cost, Shot_Doses, Shot_Dosage);
      if((FDA_approval)==0){
        printf("FDA_approval: Yes\n");
      }
      else if ((FDA_approval)==1){
        printf("FDA_approval: No\n");
      }
     printf("Shot Application: %d %0.2f %d %d \n", Total_Shot_Doses,
   Total_Shot_Sales, Total_Shot_Injuries, Total_Shot_Deaths);

    }
    //Clears all data and system
    else if (choices == 5) {
      printf("Clearing Data\n");
      system("clear");
    }
    //Quits out the program
    else if (choices == 6) {
      printf("Quit\n");
      return 0;
    }
  }
}
