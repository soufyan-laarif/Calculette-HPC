#include <stdio.h>
#include<unistd.h> /* read, write */
#include<stdlib.h>
#include<wait.h>
#include<sys/types.h> /* pid_t */
#include<sys/ipc.h>
#include<sys/sem.h>
typedef int Semaphore [2] ;
void CreerSem(key_t cle, int N);
void InitSem(int N, int V);
void P (int N);
void V (int N);
void DetruireSem();
void message(int i, char* s);
