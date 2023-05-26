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

void* philosopherDining(void* pNo);
void waitRandomTime(float minTime, float maxTime);

int sem_id;
struct sembuf sops[5];

int main(void) {
	union semun arg;
	unsigned short csticks[5];
	pthread_t pid[NUM_THREADS];
	
	sem_id = semget(SEMKEY, 5, (IPC_CREAT | IPC_EXCL | 0666));

	if (sem_id < 0) {
		perror("Cannot create semaphore.\n");
		exit(1);
	}	

	for (int i = 0; i < 5; i++)
	    csticks[i] = 1;

	arg.array = csticks;

	if (semctl(sem_id, 0, SETALL, arg) == -1) {
	    perror("semctl");
	    exit(1);
	}

	pthread_create(&pid[PHILOSOPHER_ONE], NULL, philosopherDining, (void*)PHILOSOPHER_ONE);
	pthread_create(&pid[PHILOSOPHER_TWO], NULL, philosopherDining, (void*)PHILOSOPHER_TWO);
	pthread_create(&pid[PHILOSOPHER_THREE], NULL, philosopherDining, (void*)PHILOSOPHER_THREE);
	pthread_create(&pid[PHILOSOPHER_FOUR], NULL, philosopherDining, (void*)PHILOSOPHER_FOUR);
	pthread_create(&pid[PHILOSOPHER_FIVE], NULL, philosopherDining, (void*)PHILOSOPHER_FIVE);

	pthread_join(pid[PHILOSOPHER_ONE], NULL);
	pthread_join(pid[PHILOSOPHER_TWO], NULL);
	pthread_join(pid[PHILOSOPHER_THREE], NULL);
	pthread_join(pid[PHILOSOPHER_FOUR], NULL);
	pthread_join(pid[PHILOSOPHER_FIVE], NULL);

	return 0;
}

void* philosopherDining(void* pNo) {
	intptr_t philosopherNo = (intptr_t)pNo;
	
	int right_stick = philosopherNo;
	int left_stick = (philosopherNo + 1) % 5; 

	while(1) {
		waitRandomTime(0.1, 5.0);

		printf("Philosopher %ld wants to eat. \n\n", ((long)philosopherNo + 1));
		
		sops[right_stick].sem_num = right_stick;
		sops[right_stick].sem_op = -1;
		sops[right_stick].sem_flg = 0;
		
		sops[left_stick].sem_num = left_stick;
		sops[left_stick].sem_op = -1;
		sops[left_stick].sem_flg = 0;
		
		if(semop(sem_id, &sops[philosopherNo], 2) < 0) {
			perror("Semop error! \n");
			exit(1);
		}
			
		printf("Philosopher %ld is going to eat. \n\n", ((long)philosopherNo + 1));
			
		waitRandomTime(1.0, 3.0);
		
		sops[right_stick].sem_op = 1;
		sops[left_stick].sem_op = 1;
		
		if(semop(sem_id, &sops[philosopherNo], 2) < 0) {
			perror("Semop error! \n");
			exit(1);
		}
		
		printf("Philosopher %ld is done eating, now going to think. \n\n", ((long)philosopherNo + 1));
	}

	return NULL;
}

void waitRandomTime(float minTime, float maxTime) {
	float randomTime = ((float)rand() / RAND_MAX) * (maxTime - minTime) + minTime;

	struct timespec sleepTime;
	sleepTime.tv_sec = (time_t)randomTime;
	sleepTime.tv_nsec = (long)((randomTime - sleepTime.tv_sec) * 1e9);

	nanosleep(&sleepTime, NULL);
}

