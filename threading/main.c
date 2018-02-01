#include "threading.h"

pthread_mutex_t Input, Output;
pthread_t t[THREADS];

int main(int argc, char** argv) {
	pthread_attr_t attr;
	//Create the three threads
	pthread_attr_init(&attr);
	// Set attributes to allow joinable threads
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&Input, NULL);
	pthread_mutex_init(&Output, NULL);

	if (pthread_create(&t[1], &attr, keyboard, NULL)) {
		puts("Could not create thread: keyboard");
		exit(1);
	}
	puts("Created thread: keyoard");

	if (pthread_create(&t[2], &attr, inverter, NULL)) {
		puts("Could not create thread: inverter");
		exit(1);
	}
	puts("Created thread: inverter");

	 if(pthread_create(&t[3], &attr, printer, NULL)) {
	 puts("Could not create thread: printer");
	 exit(1);
	 }
	 puts("Created thread: printer");

	pthread_join(t[1], NULL);

	return 0;
}
