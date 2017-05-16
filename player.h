/*
* socket.h
* ROCHEZ Arnaud et PIRARD Delanoe, série 1
*
*/

#if !defined(_SERVER_H_)
#define _SERVER_H_

#include "socket.h"
#include "utilities.h"
#include "sharedMemory.h"

#include <signal.h>

void err_handler(int unused);
void int_handler(int unused);

#endif
