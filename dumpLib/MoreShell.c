/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 7	:	MoreShell.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program Forks a child to execute commands with arguments like a UNIX Shell.
 * 					It forks child processes for every input to the MoreShell>.
 * 					Using execlp, it executes the command array to run the given shell command
 *
 * EXECUTION	:	./MoreShell
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
 * Description	:	It displays the prompt 'MoreShell>' and gets the input from the user and calls parseLine
 *
 *
 ******************************************************************************************************************/

static void prompt()
{
	printf("\nMoreShell > ");
	fgets(inp,25,stdin);
	inp[strlen(inp)-1]='\0';
	parseLine(inp);
}
/*****************************************************************************************************************
 *
 * Function 	: 	parseLine
 *
 * Parameters	:	<line> which is the input given by the user at MoreShell.
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
		if (execvp(cmd[0],cmd) == -1) {
		printf("Error: running command: '%s'\n",cmd[0]);
		exit(0);
		}
	break;

	default:
		waitpid(ForkPID,NULL,0);
		prompt();
	}
	}


}

