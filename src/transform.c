#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

struct inputSeperate {

    int isOperator;
    int isNegative;
    char content[128];
    int iterations;
    double value;
    int impliedMultiplication;
    double Xponent;
};

//this function takes care of negative numbers and implied multiplication by storing information
//about them in the stack
struct inputSeperate transform(struct inputSeperate *input, int position){

    struct inputSeperate scanned = input[position];
    scanned.iterations = 1;
    scanned.impliedMultiplication = 0;
    scanned.isNegative = 0;

    //determine if there is a negative number. if so, remove the negative sign from the struct array 
    //and tell the next struct (a number) that it is negative
    if (scanned.content[0] == '-'){

        if (isdigit(input[position-1].content[0]) != 0 && position != 0){

            return scanned;
        }
        else if (input[position-1].content[0] == ')'){

            return scanned;
        } 
        else {

            input[position+1].isNegative = 1;
            input[position+1].iterations = 2;
            input[position+1].impliedMultiplication = 0;
            return input[position+1];
        }
    }

    //determine if there is implied multiplication
    else if (scanned.content[0] == '('){

        if (isdigit(input[position-1].content[0]) != 0 || input[position-1].content[0] == ')'){

            scanned.impliedMultiplication = 1;
            return scanned;
        }
        else {

            return scanned;
        }
    }

    else {

        return scanned;
    }

}


