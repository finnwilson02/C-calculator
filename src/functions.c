#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"
#include "conversion.h"
#include "transform.h"
#include "operations.h"

struct inputSeperate {

    int isOperator;
    int isNegative;
    char content[128];
    int iterations;
    double value;
    int impliedMultiplication;
    double Xponent;
};

//this function displays a help menu
int help(){

    printf("The following arithmetic operations are valid:\n\n");
    printf("    '^' exponentiation\n    '+' addition\n    '-' subtraction\n");
    printf("    '*' multiplication\n    '/' division\n\n");
    printf("Single-variable algebraic expressions written in terms of 'x' are also valid.\n\n");
    printf("Enter 'h' to display this help message.\nEnter 'q' to quit the program.\n");

    return 0;
}

//this function converts the infix input to postfix, in order for the computer to be able to
//apply operators in the correct order
int postfix(char* input, int length){

    //initialise required variables and structs
    int pushChar;
    int position = 0;
    struct inputSeperate scanned;
    int arrPos = 0;
    int postPos = 0;
    int startBracket;
    int simplify = 0;

    struct inputSeperate inputStruct[length];
    struct inputSeperate postfixStruct[length+8];
    struct inputSeperate topStruct;

    //convert the character array to a struct array with the char2struct function
    while (position < length){

        inputStruct[arrPos] = char2struct(input, position);
        position = position + inputStruct[arrPos].iterations;

        if (inputStruct[arrPos].Xponent != 0){

            simplify = 1;
        }

        arrPos++;
    }

    length = arrPos;
    arrPos = 0;
    position = 0;

    //handle negative numbers and implicit multiplication with elements of our
    //structs, so we can convert to postfix
    while (position < length){

        inputStruct[arrPos] = transform(inputStruct, position);
        
        if (inputStruct[arrPos].isNegative == 1){

            inputStruct[arrPos].value = inputStruct[arrPos].value*-1;
        }

        position = position + inputStruct[arrPos].iterations;
        arrPos++;
    }

    struct inputSeperate startStack;
    startStack.content[0] = '(';
    push(startStack);
    int impliedAdded = 0;
    struct inputSeperate multi;
    multi.isOperator = 1;
    multi.content[0] = '*';

    //loop through the struct array, and apply to infix to postfix algorithm. 
    for(int i = 0; i<(arrPos); i++){

        scanned = inputStruct[i];

        if (scanned.impliedMultiplication == 1 && impliedAdded == 0){

            scanned = multi;
            impliedAdded = 1;
        }

        if (scanned.isOperator == 1){

            pushChar = precedence(scanned);

            //if the scanned operator is a closed bracket
            if (pushChar == 2){ //pop until ( is found on stack

                startBracket = 0;
                while (startBracket == 0){

                    topStruct = peek();
                    if (topStruct.content[0] == '('){

                        startBracket = 1;
                        pop();
                    }
                    else {

                        postfixStruct[postPos] = pop();
                        postPos++;
                    }
                }

                
            }
            //if the scanned operator has higher precedence then the top of the stack
            else if (pushChar == 1){ //push scanned to stack

                push(scanned);
            }

            //if the scanned operator has lower/equal precendence to the top of the stack
            else if (pushChar == 0){ //pop all from stack that are >= scanned operator. push scanned to stack if it is greater then top of stack, or if ( is encountered

                
                int arrSize = valueTop();
                int valueOld = value(scanned);
                int valueNew;
                
                //check each new top of stack value to see if it is higher/equal precedence to scanned value.
                //if it is, put it onto the postfix array
                for (int iterate = 0; iterate < arrSize; iterate++){
                    
                    postfixStruct[postPos] = pop();
                    postPos++;

                    topStruct = peek();
                    valueNew = value(topStruct);

                    if (valueNew < valueOld){

                        break;
                    }
                }
                
                push(scanned);
            }
        }

        //if the scanned struct is a number, immidiately put it onto the postfix array
        else {

            postfixStruct[postPos] = scanned;
            postPos++;
        }  

        //check if we have added implied multiplicaiton. if yes, make space for the extra struct we add
        if (impliedAdded == 1){

            i--;
            impliedAdded = 2;
        }

    }

    //add a final end bracket to the operator stack (this is nesscary to pop every operator)
    startBracket = 0;
    while (startBracket == 0){

        topStruct = peek();
        if (topStruct.content[0] == '('){

            startBracket = 1;
            pop();
        }
        else {

            postfixStruct[postPos] = pop();
            postPos++;
        }
    }

    //debugging
    for (int z = 0; z<postPos; z++){

        //printf("%s\n",postfixStruct[z].content);
    }

    //if we have an algebraic expression, call a function to simplify it. if not, call a function
    //to solve our expression. i didnt return this to the main function because its hard to return
    //the struct array in order - i believe the code is a lot cleaner this way
    if (simplify == 1){

        simplification(postfixStruct, postPos);
    }
    else {

        callOps(postfixStruct, postPos);
    }
    
    return 0;
}
