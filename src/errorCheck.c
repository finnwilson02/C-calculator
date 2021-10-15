#include <string.h>
#include <ctype.h>
#include <stdio.h>

//this function loops though the input char array and checks for illegal inputs. if one is
//found, the calculation is terminates, an error message displayed and a prompt given for a 
//new input
int vibeCheck(char* input){

	//i didnt assign input[i] to a variable as this was giving me some nasty memory issues,
	//sorry if it looks a bit messy
	int length = sizeof(input);
	int errorFound = 0;

	//loop through the input
	for (int i = 0; i<length; i++){

		//check if any illegal letters are inputted
		if (isalpha(input[i]) != 0){
			if (input[i] != 'e' && input[i] != 'E' && input[i] != 'x' && input[i] != 'X'){
				if (input[i] != 'h' && input[i] != 'H' && input[i] != 'q' && input[i] != 'Q'){

					printf("Error: Illegal input!\n");
					errorFound = 1;
					break;
				}
			}
		}

		//check if illegal consectuve operators are inputted
		if (input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '^' || input[i] == 'e'){
			if (input[i+1] != '(' && isdigit(input[i+1]) == 0 && input[i+1] != '-' && input[i+1] != 'x' && input[i+1] != 'X'){

				printf("Error: Illegal input!\n");
				errorFound = 1;
				break;
			}
		}
	}

	return errorFound;
}
