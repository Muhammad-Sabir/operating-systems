#include "header.h"

void* philosopherDining(void* pNo);
void waitRandomTime(float minTime, float maxTime);

int sem_id;
struct sembuf sops[5];

int main(void) {
	union semun arg;
	unsigned short csticks[5];
	pthread_t pid[NUM_THREADS];
	
	sem_id = semget(SEMKEY, 5, 0666);

	if (sem_id < 0) {
		perror("Cannot create semaphore.\n");
		exit(1);
	}
		
	arg.array = csticks;

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

	while(1) {
		waitRandomTime(0.1, 5.0);

		printf("Philosopher %ld wants to eat. \n\n", ((long)philosopherNo + 1));
		
		int right_stick = philosopherNo;
		int left_stick = (philosopherNo + 1) % 5; 
		
		sops[right_stick].sem_num = right_stick;
		sops[right_stick].sem_op = -1;
		sops[right_stick].sem_flg = 0;
		
		sops[left_stick].sem_num = left_stick;
		sops[left_stick].sem_op = -1;
		sops[left_stick].sem_flg = 0;
		
		if(semop(sem_id, &sops[philosopherNo], 2) < 0) {
			perror("Semop error");
			exit(1);
		}
			
		printf("Philosopher %ld is going to eat. \n\n", ((long)philosopherNo + 1));
			
		waitRandomTime(1.0, 3.0);
		
		sops[right_stick].sem_op = 1;
		sops[left_stick].sem_op = 1;
		
		if(semop(sem_id, &sops[philosopherNo], 2) < 0) {
			perror("Semop error");
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

