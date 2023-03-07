#include <stdio.h>

int add(int numOne, int numTwo);
float div(int numOne, int numTwo);
int sub(int numOne, int numTwo);
int mul(int numOne, int numTwo);

int main() {
	char choice;
	int numOne, numTwo;
	float result;

	do {
		printf("\n\nPlease enter +, -, *, / or Q to quit : ");
		scanf(" %c", &choice);


		switch(choice) {
			case '+':
				printf("\nEnter two numbers to add: ");	
				scanf("%d %d", &numOne, &numTwo);
				result = add(numOne, numTwo);
				break;
			case '-':
				printf("\nEnter two numbers to subtract(2nd will be subtracted from 1st number): ");	
				scanf("%d %d", &numOne, &numTwo);
				result = sub(numOne, numTwo);
				break;
			case '*':
				printf("\nEnter two numbers to multiply: ");	
				scanf("%d %d", &numOne, &numTwo);
				result = mul(numOne, numTwo);
				break;
			case '/':
				printf("\nEnter two numbers to divide(1st number will be numerator and 2nd will be denomerator): ");	
				scanf("%d %d", &numOne, &numTwo);
				result = div(numOne, numTwo);
				break;
		}
		
		printf("\nResult: %.2f", result);

	} while(choice != 'Q' && choice != 'q');

	printf("\n\nThanks for using mycalc.\n");			

	return 0;
}
