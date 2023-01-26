//
// Name: Renee Brandt
// Purpose: Check each line of given input and find out how many characters the file input or stdin has (default c).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //used within getopt
#include "findc.h"

void help() {
   printf("The options for this program are: \n");
   printf("	-f inputFileName (required), specify a file to search\n");
   printf("	-c character, specify a character to look for, (default 'c')\n");
}

int main(int argc, char ** argv) {
   char* fileName = NULL;
   char charName = 'c';
   int charCount = -1;
   int fileMode = 0;
   FILE* filePtr;
   FILE* errorPtr;

//function definitions
int countCharsInFile(FILE * fptr){
   charCount = 0;
   char c = NULL;
   for (c = getc(fptr); c != EOF; c = getc(fptr)) {
      if (c == charName)
         charCount++;
   }
   return charCount;
}
int countCharsInBuff(){
   charCount = 0;
   char currChar;
   while ((currChar = getchar()) != EOF) {
      printf("Currchar is %c\n", currChar);
      if (currChar == charName) {
         //printf("The current character is %c, the desired character is %c\n", currChar, charName);
         charCount++;
       }
    }
   return charCount;
}


//Create error log file
errorPtr = fopen("logerr.txt", "w+");

//Create options using getopt
   int option;
      while ( (option = getopt(argc, argv, "hf:c:")) != -1) {
         switch(option) {
            case 'h':
               help();
               exit(EXIT_SUCCESS);
            case 'f':
               fileMode = 1;
               fileName = optarg;
               break;
            case 'c':
               charName = optarg[0];              
               break;
            case '?': //in case a flag is given that is not in the list
               if (optopt == 'c')
                  fprintf (stderr, "Option -%c requires an argument.\n", optopt);
               else if (isprint (optopt))
                  fprintf (stderr, "Unknown option '-%c'.\n", optopt);
               else
                  fprintf (stderr, "Unknown option character '\\x%x'.\n", optopt);
               return 1;
            default:
               help();
               exit(EXIT_FAILURE);
      }
   }

//Check for file input
if (fileMode){ //turned on in getopt when using -f
   filePtr = fopen(fileName, "r");
   if (filePtr == NULL) {
      printf("Bad file input! %s cannot be opened or doesn't exist.\n", fileName);
      fprintf (errorPtr, "Bad file input! %s cannot be opened or doesn't exist.\n", fileName);
      fclose (errorPtr);
      return EXIT_FAILURE;
   }
   charCount = countCharsInFile(filePtr);
   printf("Number of %c's found: %d\n", charName, charCount);
   fclose (filePtr);
}
else {  //check for directed input file. Currently seg faults
   charCount = countCharsInBuff();
   printf("Number of %c's found: %d\n", charName, charCount);
   //filePtr = fopen (fileName, "r");
   //if (filePtr == NULL) {
   //   printf("Bad input! %s cannot be opened or doesn't exist\n", fileName);
   //   fprintf(errorPtr, "Bad input! %s cannot be opened or doesn't exist\n", fileName);
   //   fclose(errorPtr);
   //   return EXIT_FAILURE;
   //}
   //countCharsInFile (filePtr);
}
if (charCount == -1)  {
   printf("ERROR: No input was provided for reading!\n");
   fprintf(errorPtr, "ERROR: No input was provided for reading!\n");
   fclose (errorPtr);
   return(EXIT_FAILURE);
}
   return EXIT_SUCCESS;
}
