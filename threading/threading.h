/*
 * threading.h
 *
 *  Created on: 2 May 2017
 *      Author: Anders
 */

#ifndef THREADING_H_
#define THREADING_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 3

void *keyboard (void * arg);
void *inverter (void *arg);
void *printer (void * arg);

extern pthread_mutex_t Input;
extern pthread_mutex_t Output;


#endif /* THREADING_H_ */
