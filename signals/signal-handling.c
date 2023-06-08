#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_handler(int signo) {
	printf("Calling from signal handler\n");
}

int main(void){
	struct sigaction act;
	int count, count2;
	count = count2 = 0;
	double sum = 0;
	double x;

	for (;count < 1000000000; ++count) {
		for (;count2 < 100000000; ++ count2) {
			x = (rand() + 0.5) / (RAND_MAX + 1.0);
			sum += sin(x);
		}
	}
	
	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	if ((sigaction(SIGINT, &act, NULL)== -1)) {
		perror("Failed to set SIGINT handler\n");
		return 1;
	}
	printf("Signal handler installed for SIGINT\n");
	
	sum = 0;
	count = count2 = 0;

	for (;count < 1000000000; ++count) {
		for (;count2 < 100000000; ++ count2) {
			x = (rand() + 0.5) / (RAND_MAX + 1.0);
			sum += sin(x);
		}
	}

	sigset_t signal_set;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGSEGV);
	sigprocmask(SIG_BLOCK, &signal_set, NULL);
	printf("SIGSEGV blocked\n");
	kill(0, SIGSEGV);
	sum = 0;
	count = count2 = 0;

	
	for (;count < 1000000000; ++count) {
		for (;count2 < 100000000; ++ count2) {
			x = (rand() + 0.5) / (RAND_MAX + 1.0);
			sum += sin(x);
		}
	}
	printf("Going to unblock SIGSEGV \n");
	sigprocmask(SIG_UNBLOCK, &signal_set, NULL);
	printf("Unblocked SIGSEGV \n");
	
	return 0;
}
