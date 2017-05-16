/*
*
* sharedMemory.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/
 
#include "sharedMemory.h"

int shm_id;
int rc_id;

game * createAttachShm(key_t key) {
	game * shm;
	if((shm_id = shmget(key, sizeof(game), IPC_CREAT | 0666)) <= 0) {
		perror("Error: Shared Memory init\n");
		exit(1);
	}
	
	if((shm = (game *) shmat(shm_id, NULL, 0)) == NULL) {
		perror("Error: shared memory attach\n");
		shmctl(shm_id, IPC_RMID, NULL);
		exit(1);
	}
	
	return shm;
}

game * attachShm(key_t key) {
	game * shm;
	if((shm_id = shmget(key, sizeof(game), 0)) <= 0) {
		perror("Error: shared memory not init\n");
		exit(1);
	}
	
	if((shm = (game *) shmat(shm_id, NULL, 0)) == NULL) {
		perror("Error: shared memory attach\n");
		shmctl(shm_id, IPC_RMID, NULL);
		exit(1);
	}
	
	return shm;
}

void * destroyShm() {
	if((shmctl(shm_id, IPC_RMID, NULL)) < 0) {
		perror("Error: shared memory not destroyed\n");
		exit(1);
	}
}

void * detachShm(tablejeu * shm) {
	if((shmdt(shm)) < 0) {
		perror("Error: shared memory not detach\n");
		exit(1);
	}
}

int * createAttachRc(key_t key) {
	int * shm;
	if((rc_id = shmget(key, sizeof(int), IPC_CREAT | 0666)) <= 0) {
		perror("Error: Shared Memory init\n");
		exit(1);
	}
	
	if((shm = (int *) shmat(rc_id, NULL, 0)) == NULL) {
		perror("Error: shared memory attach\n");
		exit(1);
	}
	
	return shm;
}

int * attachRc(key_t key) {
	int * shm;
	if((rc_id = shmget(key, sizeof(int), 0)) <= 0) {
		perror("Error: shared memory not init\n");
		exit(1);
	}
	
	if((shm = shmat(rc_id, NULL, 0)) == NULL) {
		perror("Error: shared memory attach\n");
		exit(1);
	}
	
	return shm;
}

void * destroyRc() {
	if((shmctl(rc_id, IPC_RMID, NULL)) < 0) {
		perror("Error: shared memory not destroyed\n");
		exit(1);
	}
}

void * detachRc(int * shm) {
	if((shmdt(shm)) < 0) {
		"Error: shared memory not detach\n"
		exit(1);
	}
}
