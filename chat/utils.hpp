#pragma once
#include <signal.h> 
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/shm.h> 
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <unistd.h> 

#define MEMORY_KEY 1111
#define SEM_KEY 1234

void signalSemaphore(int semid);
void waitSemaphore(int semid);

struct Memory { 
	char buff[100]; 
	int pid1, pid2;
}; 

