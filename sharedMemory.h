/*
*
* sharedMemory.h
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#ifndef _SHAREDMEMORY_H_
#define _SHAREDMEMORY_H_

#include "utilities.h"
#include <sys/ipc.h>
#include <sys/shm.h>


#define KEY 15
#define KEY_RC 16

game * createAttachShm(key_t key);
game * attachShm(key_t key);
void * destroyShm();
void * detachShm(game * shm);
int * createAttachRc(key_t key);
int * attachRc(key_t key);
void * destroyRc();
void * detachRc(int * shm);

#endif