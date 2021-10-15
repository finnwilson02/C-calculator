#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"
#include "conversion.h"
#include "stack.h"
#include "errorCheck.h"

//this function parses the inputs, has a while loop so the calculator can be used repeatedly and calls other
//functions to find errors and do the calculations
int main(){

    printf("Cursed Calculator\n");
    int ask_input = 1;
    
    //this loop will continually ask for new inputs to calculate
    while (ask_input == 1){

        //set nessecary variables and get an input with fgets
        int input_length = 1024;
        char input_spaced[input_length];
        clearmem();
        int errorFound = 0;
        int divZero = 0;

        printf(">>> ");

        fgets(input_spaced,input_length,stdin);
        
        input_length = strlen(input_spaced);
        char input[input_length];
        int j = 0;
        int reduced_length = 0;

        //loop through the input. remove spaces and check for division by 0
        for (int i=0; i<input_length; i++){
                
            if (input_spaced[i] == '/' && input_spaced[i+1] == '0'){

                printf("Error: Divide by zero!\n");
                divZero = 1;
            }
            else if (isspace(input_spaced[i]) != 0){

            }
            else if (input_spaced[i] == '\n'){

                break;
            }
            else {
                    
                input[j] = input_spaced[i];
                j++;
                reduced_length++;
            }

        }

        //call the function to check for errors in the input. if there is an error, the code will display an
        //error message and prompt the user for a new input. Otherwise, it displays the help menu, quits, or 
        //calls a function to calculate the result based on the input
        errorFound = vibeCheck(input);

        if (errorFound == 0 && divZero == 0){

            if (input[0] == 'h' || input[0] == 'H'){

                help();
            }
            else if (input[0] == 'q' || input[0] == 'Q'){

                printf("Goodbye!\n");
                return 0;
            }

            else {

                postfix(input, reduced_length);
            }
        }
        
    }

    return 0;
}
