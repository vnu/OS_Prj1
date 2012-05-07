#ifndef _OSHEADERS_H_
#define _OSHEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>


#define MAXCHILD 30
#define MAXSIZE 1000
#define MAXLEN 10000
#define MILLION 1000000

void Decompression(int ,int );
void Compression(int ,int );
void writefile(int ,int );
void Compress(char *,int);
void Forking();
void PipeCompress();
void PipeWrite();
void FileWrite();

char* Parsing(int);

int parseLine(char *);
int parseline(char *,char **);

#endif /*OSHEADER_H_*/
