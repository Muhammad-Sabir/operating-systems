// Operations' Symbolic Constants
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

// Memory
#define SIZE 100

void loadProgram(int *memory, int memorySize);
void display(int *memory, int memorySize, int acc, int instCounter, int instRegister, int opCode, int operand);