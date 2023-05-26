#include "header.h"

int main(void) {
	int sem_id;
	union semun arg;
	unsigned short csticks[5];
	
	sem_id = semget(SEMKEY, 5, (IPC_CREAT | IPC_EXCL | 0666));

	if (sem_id < 0)
		perror("Cannot create semaphore.\n");
	else {
		for (int i = 0; i < 5; i++)
		    csticks[i] = 1;

		arg.array = csticks;

		if (semctl(sem_id, 0, SETALL, arg) == -1) {
		    perror("semctl");
		    exit(1);
		}
	}

	return 0;
}
