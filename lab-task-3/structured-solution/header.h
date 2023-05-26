#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#define PHILOSOPHER_ONE 0
#define PHILOSOPHER_TWO 1
#define PHILOSOPHER_THREE 2
#define PHILOSOPHER_FOUR 3
#define PHILOSOPHER_FIVE 4

#define NUM_THREADS 5

#define SEMKEY 456

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};
