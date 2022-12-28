/*  Tyrese Britten
    Systems Programming , Spring 2022
    Program 5
    For this project will be using varies types of methods to make a
    wordle game. The goal it use dynamically allocated arrays, pulling in a
    file, using pointers to pass address and command line agruementd to make 
    a game called wordle.
*/

#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

#include <assert.h>

#include <ctype.h>

#include <time.h>

/*
This Function for toCAPS is to put the users guesses in capital letters
*/
void toCAPS(char *word) {
    while (*word) {
        *word = toupper((unsigned char) *word);
        word++;
    }
}
/* The Function here is reading int the dictionary and 
counting all the words from the dictionary file. We call this function
later in main
*/
int get_count_NWords(FILE *dp, char *letters){
    rewind(dp);
    char empty[40];
    int count = 0; 
    while (fgets(empty, 40, dp) != NULL){
        if (strlen(empty) == atoi(letters)+2) {
            count++;
        }
    }
    return count;
    fclose(dp);
}
/* Populate function is populating the Lengthwords with the dictionary input from the file 
pointer. We return Lengthwords so we can use the dictionary throughout the program.
*/
char** populate_NWords(FILE *dp, char *letters, int count, char **LengthNWords){
    rewind(dp);
    LengthNWords = malloc(count*(atoi(letters)+1)*sizeof(char*));

    char empty[40];
    int pos = 0;
    while (fgets(empty, 40, dp) != NULL){
        if (strlen(empty) == atoi(letters)+2) {
            empty[atoi(letters)] = '\0';

            LengthNWords[pos] = malloc(sizeof(char*)*atoi(letters)+1);
            toCAPS(empty);
            strcpy(LengthNWords[pos], empty);
            pos++;
        }
    }
    return LengthNWords;
}
/* This function prompts the user with asking them to enter a n letter word. The n dictates how long the wrong is
so Lengthwords is populated with the length of words the user will have,
*/
void prompt_user(char *letters, int numNWords, char **LengthNWords, char inputword[40]){
    printf("Enter a %s Letter word\n", letters);
    scanf("%s", inputword);
    toCAPS(inputword);
    for(int i = 0; i < numNWords; i++) {
        if(strcmp(inputword, LengthNWords[i]) == 0) {
            printf("%s | %s: %d\n" , inputword, LengthNWords[i], strcmp(inputword, LengthNWords[i]));
            return;
        }
    }
    prompt_user(letters, numNWords, LengthNWords, inputword);
}

/* Generate Answer function makes a random n length word in the dictionary however long it needs to be. This
will be the answer the user will be getting.
*/
char *generateAnswer(int numNWords, char **LengthNWords) {
    time_t t;
    srand((unsigned) time(&t));
     return LengthNWords[rand() % (numNWords != 0)];
}
/* Feedback function holds the checking when the user makes their guesses. They will get a ^,> or X to 
guide them to the correct answer. We get feeback string to be used in valid words for the list of words 
that gets narrowed down.
*/
void feedback(int letters, char inputword[40], char *answer, char *feedback_string){
    memset(feedback_string,0,strlen(feedback_string));
    char temp[letters];
    bool found = false;
    for (int i = 0; i < letters; i++) {
        found = false;
        for (int j = 0; j < letters; j++) {
            if(inputword[i] == answer[j] && i==j){
                found = true;
                temp[i] = '^';
            }
            if(inputword[i] == answer[j] && i!=j && !found) {
                temp[i] = '<';
                found = true;
            }
        }
        if (!found) {
            temp[i] = 'X';
        }
        
    }
    printf("Feedback: %s\n", temp);
    strcpy(feedback_string, temp);
    printf("\n\n");

}

/* For this function we are printing out the valid combinations a user has when they put in a guess.
There are 3 for loops that got through the word, the feedback string and then each letter of the 
feedback string. Once we got this for loops working, there are if conditions at will check the array of the
dictionary and compare it to the input word. This will be whne there are is a wrong letter. Then put 
a bool case is false. The next conditional will check if it the right letter but in the wrong position
. THis will check the same thing as in the previous case but will see if the letter and the position are differet.
If so it will be flagged. The last condition will check to see if everything is in the right position and the right letter.
Once we have all of this. The valid words will be printed and narrowed everytime the user makes a guess. We 
make sure of this by setting the dictionary equal to another array and pull the words that are needed.
*/
int valid_words(char *feedback_string, char **LengthNWords, char inputword[40],int numNWords){
    int i,j,k;
    char valid[numNWords][strlen(feedback_string)+1];
    int numOfValid = 0;
    bool isGood;

    printf("numNWords: %d\n", numNWords);
    for(j=0; j<numNWords; j++){
        isGood = true;
        for(k=0; k<=strlen(feedback_string); k++){
            for(i=0; i<=strlen(feedback_string); i++){
                if (inputword[k] != '\0' && isGood){
                    if(feedback_string[k] == 'X'){
                        if (LengthNWords[j][i] == inputword[k]){
                            isGood = false;
                        }
                    } else if(feedback_string[k] == '<') {
                        if (LengthNWords[j][i] == inputword[k] && k == i) {
                            isGood = false;
                        } 
                    } else if (feedback_string[k] == '^') {
                        if (k == i && LengthNWords[j][i] != inputword[k]) {
                            isGood = false;
                        } 
                    }
                }
            }
        }

        if(isGood == true){
            strcpy(valid[numOfValid],LengthNWords[j]);
            numOfValid++;
        }
    }

    char s[strlen(feedback_string)+1];
    s[0] = '\0';
    for (int m = 0; m < numNWords; m++) {
        if (m < numOfValid) {
            strcpy(LengthNWords[m], valid[m]);
        } else {
            strcpy(LengthNWords[m], s);
        }
    }
    return numOfValid;
}

/* This print function prints out the valid words that remain when the user puts in their guess. It will be
narrowed down as the user makes more guess when they go through the program.
*/
void print_valid(char **LengthNWords, int numNWords){
    printf("Valid Words(s) Found: \n");
    for(int i=0; i < numNWords; i+=5){
        for (int j = i; j < i+5; j++) {
            if (j <= numNWords) {
                printf("%s ",LengthNWords[j]);
            }
        }
        printf("\n");
    }
}

/* Main function with all the variables declared and the function calls. This is where everything 
comes together and we get what needed in the program. Also prompt the user to ask if they 
want to play again or not.
*/
int main(int argc, char * argv[]) {
    FILE * dp = fopen(argv[1], "r");
    char *letters = argv[2];
    char *guess = argv[3];
    char **LengthNWords = NULL;
    char **ValidNWords = NULL;
    char inputword[40];
    char *answer;
    char *doublefeed;
    char choice[10];
    bool playing = true;
    doublefeed= malloc(sizeof(char*)*atoi(letters)+1);
    char storeguess[atoi(guess)][atoi(letters)+1];
    if (argc < 3){
        printf("You have chosen a default letter length of 5 with 6 guesses. Please include additional inputs for customization.\n");
        letters = "5";
        guess = "6";
    }
    while (playing) {
        int numNWords = get_count_NWords(dp, letters);
        int numValidWords = numNWords;
        LengthNWords = populate_NWords(dp, letters, numNWords, LengthNWords);
        ValidNWords = populate_NWords(dp, letters, numNWords, ValidNWords);
        answer = generateAnswer(numNWords,LengthNWords);
        for (int i = 0; i < atoi(guess); i++){
            
            prompt_user(letters, numNWords, LengthNWords, inputword);
            strcpy(storeguess[i], inputword);
            
            for (int j = 0; j <= i+1; j++){
                printf("Guess %d: %s\n", j+1, storeguess[j+1]);
            }

           
            if (strcmp(inputword,answer)==0) {
                printf("YOU WIN!!!\n");
                printf( "Do you want to play again? (Yes/No) \n");
                scanf("%s", choice);
                if ( !strcmp(choice, "Yes" ) || !strcmp(choice, "yes" ) || !strcmp(choice, "YES" )){
                    playing = true;
                    break;
                }
                else if( !strcmp(choice, "No" ) || !strcmp(choice, "no" ) || !strcmp(choice, "NO" )){
                    playing = false;
                    break;
                }
                else{
                    playing = false;
                    break;
                }
            }

            feedback(atoi(letters), inputword, answer, doublefeed);
            numValidWords = valid_words(doublefeed, ValidNWords, inputword, numValidWords);
            print_valid(ValidNWords, numValidWords);
        }
    }
    fclose(dp);
}
    
