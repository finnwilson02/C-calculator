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

//this function applies operations to the postfix expression and outputs a result
int callOps(struct inputSeperate *input, int length){

    int inPos, outPos = 0;
    struct inputSeperate output[length];
    struct inputSeperate scanned;

    //loop through each struct in the postfix array
    for (inPos = 0; inPos < length; inPos++){

        //if the scanned value is a number, add it to the output. if its an 
        //operator, determine what the operator does and apply it to the values
        //already added to the output array
        scanned = input[inPos];
        if (scanned.isOperator == 0){

            output[outPos] = scanned;
            outPos++;
        }
        else {
            
            double value1 = output[outPos - 2].value;
            double value2 = output[outPos - 1].value;

            if (scanned.content[0] == '+'){

                value1 = value1 + value2;
            }
            else if (scanned.content[0] == '-'){

                value1 = value1 - value2;
            }
            else if (scanned.content[0] == '*'){

                value1 = value1*value2;
            }
            else if (scanned.content[0] == '/'){

                value1 = value1/value2;
            }
            else if (scanned.content[0] == '^'){

                value1 = pow(value1,value2);
            }
            else if (scanned.content[0] == 'e'){

                value1 = value1*pow(10,value2);
            }

            output[outPos - 2].value = value1;
            outPos--;
        }
    }

    //print the result to 3dp
    printf("%.3f\n",output[0].value);
    return 0;
}

//this function simplifies the postfix array of structs when it is an
//algebraic expression
int simplification(struct inputSeperate *input, int length){

    int inPos;
    struct inputSeperate outputX;
    struct inputSeperate outputPlain;
    outputX.value = 0;
    outputPlain.value = 0;
    struct inputSeperate scanned;
    int split = 0;
    int full = 0;

    //find each operator in the postfix array. when it is found, apply it appropriately
    //to the previous 2 values. this includes only adding/substracting terms with an equal x indice,
    //while multiplying/dividing/exponentiating any term (including both x and non-x terms if they 
    //are split), and applying transformations to both coefficients and exponents
    for (inPos = 0; inPos < length; inPos++){

        scanned = input[inPos];

        if (scanned.isOperator != 0){
            
            struct inputSeperate struct1 = input[inPos - 2];
            struct inputSeperate struct2 = input[inPos - 1];

            //determine if there are values that have been places in the x and non-x variables.
            //if there are, move them out so we can apply operations to them
            if (full == 1){

                struct1 = outputX;
            }

            //if the operator is add, apply the following transformations:
            if (scanned.content[0] == '+'){

                //if the two values have equal x-indices 
                if (struct1.Xponent == struct2.Xponent && struct1.Xponent != 0){

                    outputX.value = struct1.value + struct2.value;
                    outputX.Xponent = struct1.Xponent;
                }
                //if the two values dont have x-indices 
                else if (struct1.Xponent == struct2.Xponent && struct1.Xponent == 0){

                    outputPlain.value = struct1.value + struct2.value;
                }

                //if the two values have different x-indices
                else if (struct1.Xponent != struct2.Xponent && struct1.Xponent == 0){

                    outputPlain.value = struct1.value;
                    outputX.value = struct2.value;
                    split = 1;
                }
                else if (struct1.Xponent != struct2.Xponent && struct1.Xponent != 0){

                    outputX.value = struct1.value;
                    outputPlain.value = struct2.value;
                    split = 1;
                }
            }
            //its pretty much the same for each operator so I wont repeat the same comments
            else if (scanned.content[0] == '-'){

                if (struct1.Xponent == struct2.Xponent && struct1.Xponent != 0){

                    outputX.value = struct1.value - struct2.value;
                    outputX.Xponent = struct1.Xponent;
                }
                else if (struct1.Xponent == struct2.Xponent && struct1.Xponent == 0){

                    outputPlain.value = struct1.value - struct2.value;
                }
                else if (struct1.Xponent != struct2.Xponent && struct1.Xponent == 0){

                    outputPlain.value = struct1.value;
                    outputX.value = -1*struct2.value;
                    split = 1;
                }
                else if (struct1.Xponent != struct2.Xponent && struct1.Xponent != 0){

                    outputX.value = struct1.value;
                    outputPlain.value = -1*struct2.value;
                    split = 1;
                }
            }
            else if (scanned.content[0] == '*'){

                if (split == 1){

                    outputX.value = outputX.value*struct2.value;
                    outputPlain.value = outputPlain.value*struct2.value;
                }
                else {

                    if (struct1.Xponent != 0){

                        outputX.value = struct1.value*struct2.value;
                        outputX.Xponent = struct1.Xponent + struct2.Xponent;
                    }
                    else {

                        outputPlain.value = struct1.value*struct2.value;
                    }
                }
            }
            else if (scanned.content[0] == '/'){

                if (split == 1){

                    outputX.value = outputX.value/struct2.value;
                    outputPlain.value = outputPlain.value/struct2.value;
                }
                else {

                    if (struct1.Xponent != 0){

                        outputX.value = struct1.value/struct2.value;
                        outputX.Xponent = struct1.Xponent - struct2.Xponent;
                    }
                    else {

                        outputPlain.value = struct1.value/struct2.value;
                    }
                }
            }
            else if (scanned.content[0] == '^'){

                if (struct1.Xponent != 0){

                    outputX.value = pow(struct1.value,struct2.value);
                    outputX.Xponent = struct1.Xponent*struct2.value;
                }
                else {

                    outputPlain.value = pow(struct1.value,struct2.value);
                }
            }

            full = 1;
        }
    }

    //apply relevant print statements. these are all printing the same things, the
    //if statements are just nessecary to ensure negatives and instances where there
    //is no exponent/x term/non x-term print nicely
    if (outputX.value != 0 && outputPlain.value != 0){

        if (outputX.Xponent == 0 || outputX.Xponent == 1){
            if (outputPlain.value < 0){

                printf("%.3fx-%.3f\n",outputX.value, fabs(outputPlain.value));
            } 
            else {

                printf("%.3fx+%.3f\n",outputX.value, outputPlain.value);
            }  
        }
        else{

            if (outputPlain.value < 0){

                printf("%.3fx^%.3f-%.3f\n",outputX.value, outputX.Xponent, fabs(outputPlain.value));
            }
            else {

                printf("%.3fx^%.3f+%.3f\n",outputX.value, outputX.Xponent, outputPlain.value);
            } 
        }
    }
    else if (outputX.value != 0 && outputPlain.value == 0){

        if (outputX.Xponent == 0 || outputX.Xponent == 1){

            printf("%.3fx\n",outputX.value);
        }
        else{
            
            printf("%.3fx^%.3f\n",outputX.value, outputX.Xponent);
        }
    }
    else if (outputX.value == 0 && outputPlain.value != 0){

        printf("%.3f\n",outputPlain.value);
    }

    return 0;
}
