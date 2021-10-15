#include <stdio.h>
#include <string.h>
#include "conversion.h"

struct inputSeperate {

    int isOperator;
    int isNegative;
    char content[128];
    int iterations;
    double value;
    int impliedMultiplication;
    double Xponent;
};

//this file acts as a shortcut to push, pop, and peek from a stack of structs, as well as to find the
//precedence of an operator in relation to the top of the stack
struct inputSeperate stack[1024];
int top = -1;

//this ensures the memory is cleared for each new calculation
int clearmem(){

    for (int i=0; i<1024; i++){

        memset(stack[i].content, 0, 128);
        top = -1;
    }
    
    return 0;
}

//the function pushes a struct to the top of the stack
int push(struct inputSeperate scanned){

    //top is a counter to know where the most recent value on the stack is
    top++;
    stack[top] = scanned;

    return 0;
}

//this function returns and removes the top value from the stack
struct inputSeperate pop(){

    struct inputSeperate returnedStruct;
    
    //is the stack is empty, return a (the program knows this and will set precedence of
    //the scanned operator accordingly)
    if (top == -1){

        returnedStruct.content[0] = 'a';
    }
    else {

        returnedStruct = stack[top];
        top--;
    }

    return returnedStruct;
}

//return the top struct in the stack without popping/removing it
struct inputSeperate peek(){

    struct inputSeperate returnedStruct;
    
    if (top == -1){

        returnedStruct.content[0] = 'a';
    }
    else {

        returnedStruct = stack[top];
    }

    return returnedStruct;
}

//find the precednece of a scanned operator against the top of the stack. this function assigns a
//value to each operator based on precendence, compares and the values and determines what the 
//infix to postfix function will do with the operator (push, pop until lesser value operator or pop
//until open bracket)
int precedence(struct inputSeperate scanned){

    struct inputSeperate topStruct = peek();
    int value_top, value_scanned, pushChar, endBracket = 0;   

    if (topStruct.content[0] == '^'){

        value_top = 2;
    }
    else if (topStruct.content[0] == '*' || topStruct.content[0] == '/'){

        value_top = 1;
    }
    else if (topStruct.content[0] == '+' || topStruct.content[0] == '-'){

        value_top = 0;
    }
    else if (topStruct.content[0] == 'a' || topStruct.content[0] == '('){

        value_top = -1;
    }
    if (scanned.content[0] == '('){

        value_scanned = 3;
    }
    else if (scanned.content[0] == '^'){

        value_scanned = 2;
    }
    else if (scanned.content[0] == '*' || scanned.content[0] == '/' || scanned.content[0] == 'e'){

        value_scanned = 1;
    }
    else if (scanned.content[0] == '+' || scanned.content[0] == '-'){

        value_scanned = 0;
    }
    else if (scanned.content[0] == ')'){

        endBracket = 1;
    }
    
    if (endBracket == 1){

        pushChar = 2;
    }
    else if(value_scanned>value_top){

        pushChar = 1;
    }
    else{

        pushChar = 0;
    }

    return pushChar;
}

//this is like the precedence function, but only returns a value instead of instructions to push/pop.
int value(struct inputSeperate scanned){

    int value_scanned;

    if (scanned.content[0] == '('){

        value_scanned = -1;
    }
    else if (scanned.content[0] == '^'){

        value_scanned = 2;
    }
    else if (scanned.content[0] == '*' || scanned.content[0] == '/' || scanned.content[0] == 'e'){

        value_scanned = 1;
    }
    else if (scanned.content[0] == '+' || scanned.content[0] == '-'){

        value_scanned = 0;
    }

    return value_scanned;
}

int valueTop(){

    return top;
}

