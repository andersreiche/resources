#include "threading.h"
char s_in[1000], s_out[1000], s[1000];
;
int DataInFlag, DataOutFlag;
extern pthread_mutex_t Input;
extern pthread_mutex_t Output;

void* keyboard(void* arg) {
	puts("keyoard: reporting in...");

	while (1) {

		int c = 0;
		gets(s);

		// Grab the mutex key
		if (pthread_mutex_lock(&Input) == 0) {
			if (DataInFlag == 0) {
				while (s[c] != '\0') {
					s_in[c] = s[c];
					c++;
				}
				DataInFlag = 1;
			}
		}
		fflush(stdout);
		pthread_mutex_unlock(&Input); // put the key back
	}
	puts("keyboard: returned 0");
	return 0;
}

void* inverter(void* arg) {
	puts("inverter: reporting in...");

	while (1) {
		// Grab the mutex key
		if (pthread_mutex_lock(&Input) == 0
				&& pthread_mutex_lock(&Output) == 0) {
			if (DataInFlag == 1) {
				int c = 0;
				while (s[c] != '\0') {
					if (s_in[c] >= 'A' && s_in[c] <= 'Z') {
						s_in[c] += 32;
						s_out[c] = s_in[c];
						DataInFlag = 0;
						DataOutFlag = 1;
						c++;
					} else if (s_in[c] >= 'a' && s_in[c] <= 'z') {
						s_in[c] -= 32;
						s_out[c] = s_in[c];
						DataInFlag = 0;
						DataOutFlag = 1;
						c++;
					} else {
						c++;
					}
				}
				s_out[c] = '\0';
			}
		}
		fflush(stdout);
		pthread_mutex_unlock(&Input); // put the key back
		pthread_mutex_unlock(&Output); // put the key back
		usleep(1000);
	}
	puts("inverter: returned 0");
	return 0;
}

void* printer(void* arg) {
	puts("printer: reporting in...");
	while (1) {
		// Grab the mutex key
		if (pthread_mutex_lock(&Output) == 0) {
			if (DataOutFlag == 1) {
				printf("%s", s_out);
				DataOutFlag = 0;
			}
		}
		fflush(stdout);
		pthread_mutex_unlock(&Output); // put the key back
		usleep(1000);
	}
	puts("printer: returned 0");
	return 0;
}
