/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 3	:	ForkCompress.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 			It forks a child process.
 * 			Using execlp, it calls the MyCompress.c program to Compress the Input File and writes to Output File
 *
 * EXECUTION	:	./ForkCompress <Input File> <Output File>
 *
 * DATE			:	28 JAN 2011
 *
 ******************************************************************************************************************/
	#include "osheaders.h"

/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	<Input File> <Output File>
 * 					Both the filenames must be string passed through argv[1] and argv[2] *
 *
 * Description	:	This Program Forks a child, and calls the My Compress through execlp in the child.
 * 					Compresses the file and writes the output to the Output File through the Child processes
 *
 *
 ******************************************************************************************************************/


int main(int argc,char **argv)
{

	pid_t ForkPID;
	ForkPID = fork();

	switch (ForkPID) {
	case -1: printf("Error: Failed to fork.\n"); break;
	case 0:
		//In Child using execlp it calls MyCompress
		execlp("./MyCompress", "./MyCompress", argv[1],argv[2], NULL);
	break;

	default:
		//Parent process is executed here. It waits for the child to complete before exiting
		waitpid(ForkPID,NULL,0);
		printf("Fork executed successfully\n");
	}


}
