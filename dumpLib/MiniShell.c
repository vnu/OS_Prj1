/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 6	:	MiniShell.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program Forks a child to execute argument less commands like a UNIX Shell.
 * 					It forks a child process.
 * 					Using execlp, it executes the command array to run the given shell command
 *
 * EXECUTION	:	./MiniShell
 *
 * DATE			:	12 FEB 2011
 *
 ******************************************************************************************************************/
#include "osheaders.h"
char inp[25];
char *cmd[5];

/*****************************************************************************************************************
 *
 * Function 	: 	prompt
 *
 * Parameters	:	NONE
 *
 * Description	:	It displays the prompt 'MiniShell>' and gets the input from the user and calls parseLine
 *
 *
 ******************************************************************************************************************/

static void prompt()
{
	printf("\nMiniShell > ");
	fgets(inp,25,stdin);
	inp[strlen(inp)-1]='\0';
	parseLine(inp);
}

/*****************************************************************************************************************
 *
 * Function 	: 	parseLine
 *
 * Parameters	:	<line> which is the input given by the user at MiniShell.
 *
 * Description	:	It parses the input and stores it in the cmd[]
 *
 *
 ******************************************************************************************************************/

int parseLine(char * line) {
char * p;
int count = 0;
p = strtok(line, " ");
while (p && strcmp(p,"|") != 0) {
cmd[count] = p;
count++;
p = strtok(NULL," ");
}
}

/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	NONE
 *
 * Description	:	This Program Forks a child, and executes the argument-less shell command through execlp in the child.
 * 					It forks a child every time a command is given to execute it.
 * 					It exits if 'exit' is given.
 *
 *
 ******************************************************************************************************************/
int main(int argc,char **argv)
{
	prompt();

	pid_t ForkPID;

	while(strcmp(inp,"exit")!=0)
	{
		ForkPID = fork();
	switch (ForkPID) {
	case -1: printf("Error: Failed to fork.\n"); break;
	case 0:
		if (execlp(cmd[0],cmd[0], NULL) == -1) {
		printf("Error: running command: '%s'\n Please check your command using help\n\n",cmd[0]);
		exit(0);
		}
	break;

	default:
		waitpid(ForkPID,NULL,0);
		prompt();
	}
	}


}

