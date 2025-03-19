#include "utils.hpp"

struct Memory* shmptr; 
void handler(int signum) 
{ 
	printf("From User1: "); 
    std::cout << shmptr->buff;
} 

int main() 
{ 
	int shm_id; 
	int sem_id; 

	shm_id = shmget(MEMORY_KEY, sizeof(struct Memory), IPC_CREAT | 0666); 
    sem_id = semget(SEM_KEY, 1, 0666);
	shmptr = (struct Memory*) shmat(shm_id, NULL, 0); 
	shmptr->pid2 = getpid(); 

	signal(SIGUSR2, handler); 
	while (1) { 
        waitSemaphore(sem_id);
		fgets(shmptr->buff, 100, stdin); 
        signalSemaphore(sem_id);
		kill(shmptr->pid1, SIGUSR1); 
	} 

	shmdt((void*)shmptr); 

	return 0; 
} 

