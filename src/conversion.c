#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct inputSeperate {

    int isOperator;
    int isNegative;
    char content[128];
    int iterations;
    double value;
    int impliedMultiplication;
    double Xponent;
};

//this function converts a char array and a position in that array to a struct. if there is a 
//multi-digit number, it will be turned from multiple elements of the char array to one struct
struct inputSeperate char2struct(char* input, int position){

    //initialise nessecary variables
    int length = strlen(input);
    struct inputSeperate structElement;
    memset(structElement.content, 0, 128);
    structElement.iterations = 0;
    structElement.Xponent = 0;
    int isNumber;
    int maxdigits = 64;

    int k = 0;
    char number[maxdigits];
    isNumber = isdigit(input[position]);
        
    //if we have an operator, fill in the struct information and return in
    if (isNumber == 0 && input[position] != 'x' && input[position] != 'X'){

        structElement.isOperator = 1;
        structElement.content[0] = input[position];
        structElement.iterations = 1;
        return structElement;
    }
    //if we have a number, find all the digits of it by looping through the input array.
    //return the struct with information about the number, as well as the position we are
    //now up to in the input array
    else if (input[position] != 'x' || input[position] != 'X'){

        structElement.isOperator = 0;
        int iterate = 1;
        memset(number, 0, sizeof(number));

        while (iterate == 1){

            number[k] = input[position];
            k++;
            structElement.iterations = structElement.iterations + 1;

            if (position + 1 == length){

                iterate = 0;
            }
            else if (isdigit(input[position+1]) == 0 && input[position+1] != '.'){

                iterate = 0;
            }
            else {

                iterate = 1;
                position++;
            }

        }

        double numberDouble = atof(number);
        structElement.value = numberDouble;
        strcpy(structElement.content, number);
    }

        //if one of the inputs is x, we will find if it has an exponent. if it does, we find what that exponent is, and 
        //record this as an element of the struct for the coeffecient of x. if there is no coefficient given, we make it
        //1.
        if (input[position+1] == 'x' || input[position+1] == 'X' || input[position] == 'x' || input[position] == 'X'){

                   char exponent[8];
                   memset(exponent,0,8);
                   int addValue = 1;
                   
                   //go to the right position based on if x has a coeffecient or not
                   if(input[position] == 'x' || input[position] == 'X'){

                       position = position + 1;
                       memset(structElement.content, 0, 128);
                       structElement.content[0] = '1';
                       structElement.value = 1;
                   }
                   else{
                       
                       addValue = 2;
                       position = position + 2;
                   }

                   //find the exponent of x, if there is one
                   if (input[position] == '^'){

                       position++;
                       int findExponent = 1;
                       int exponentPos = 0;
                       while (findExponent == 1){

                            exponent[exponentPos] = input[position];
                            exponentPos++;

                            if (position + 1 == length){

                                findExponent = 0;
                            }
                            else if (isdigit(input[position+1]) == 0){

                                findExponent = 0;
                            }
                            else {

                                findExponent = 1;
                                position++;
                            }
                       }

                       structElement.Xponent = atof(exponent);
                       structElement.iterations = structElement.iterations + exponentPos + addValue;
                   }
                   else {

                       structElement.Xponent = 1;
                       structElement.iterations = structElement.iterations + 1;
                   }

                   return structElement;
               }

    return structElement;
}   


