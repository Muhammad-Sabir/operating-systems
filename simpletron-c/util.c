#include <stdio.h>
#include <stdlib.h>

void loadProgram(int *memory, int memorySize) {
	int value, i = 0;
    char filename[100];

    printf("\nPlease enter file path/name: ");
    scanf("%s", filename);

	
	FILE *fptr = NULL;
	fptr = fopen("program.txt", "r");
	
	if(fptr == NULL) {
		printf("FILE NOT FOUND!");
		exit(1);
	}
	
	while(fscanf(fptr, "%d ", &value) != EOF) {
		memory[i++] = value;
	}
	
	while(i < memorySize) {
		memory[i++] = 0;
	}
	
	fclose(fptr);
}

void display(int *memory, int memorySize, int acc, int instCounter, int instRegister, int opCode, int operand) {
    printf("\n Accumulator: %d", acc);
    printf("\n Instruction Counter: %d", instCounter);
    printf("\n Instruction Register: %d", instRegister);
    printf("\n OpCode: %d", opCode);
    printf("\n Operand: %d \n\n", operand);

    for(int i = 0; i < memorySize; i += 10) {
        for(int j = i; j < i + 10; j++) {
            printf("%04d ", memory[j]);
        }

        printf("\n");
    }
}
