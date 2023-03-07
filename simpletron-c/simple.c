#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "simple.h"

int main() {	
	//Memory
	int memory[SIZE];

	// Registers
	int instructionCounter = -1, accumulator = 0,  instructionRegister = 0, opCode = 0, operand = 0;

	// Variables
	int word;
	char choice;

	printf("\t\t***WELCOME TO SIMPLETRON***");

	loadProgram(memory, SIZE);
	
	do {
		++instructionCounter;
		instructionRegister = memory[instructionCounter];
		opCode = instructionRegister / 100;
		operand = instructionRegister % 100;

		display(memory, SIZE, accumulator, instructionCounter, instructionRegister, opCode, operand);

		system("stty raw -echo");
		printf("\n\nPress 'Q' to quit from the program. Press any other 'ALPHABET/NUMERIC/CHARACTER' key to execute next instruction: ");
		scanf(" %c", &choice);
		system("stty -raw echo");

		if(toupper(choice) == 'Q')
			break;

		system("clear");

		switch (opCode) {
			case READ:
				printf("\t***READING***");
				printf("\nEnter a word: ");
				scanf(" %d", &word);
				memory[operand] = word;
			break;

			case WRITE:
				printf("\t***WRITING***");
				printf("\n%d \n", memory[operand]);
			break;

			case LOAD:
				printf("\t***LOADING***\n");
				accumulator = memory[operand];
			break;

			case STORE:
				printf("\t***STORING***\n");
				memory[operand] = accumulator;
			break;

			case ADD:
				printf("\t***ADDING***\n");
				accumulator += memory[operand];
			break;

			case SUBTRACT:
				printf("\t***SUBTRACTING***\n");
				accumulator -= memory[operand];
			break; 

			case DIVIDE:
				printf("\t***DIVIDING***\n");
				accumulator /= memory[operand];
			break;

			case MULTIPLY:
				printf("\t***MULTIPLYING***\n");
				accumulator *= memory[operand];
			break;

			case BRANCH:
				printf("\t***BRANCHING***\n");
				instructionCounter = operand - 1;
			break;

			case BRANCHNEG:
				printf("\t***BRANCHING NEGATIVE***\n");
				if(accumulator < 0)
					instructionCounter = operand - 1;
			break;

			case BRANCHZERO:
				printf("\t***BRANCHING ZERO***\n");
				if(accumulator == 0)
		            instructionCounter = operand - 1;
			break;

			case HALT:
				printf("\t***HALTING***\n");
			break;

			default:
				printf("ERROR!");
				exit(1);
		}
	} while(opCode != HALT);

	system("clear");
	display(memory, SIZE, accumulator, instructionCounter, instructionRegister, opCode, operand);
	printf("\n\nThank you for using simpletron. \n");

	return 1;
}