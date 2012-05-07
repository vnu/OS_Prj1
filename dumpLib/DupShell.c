/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 8	:	DupShell.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program Forks a child to execute commands with arguments like a UNIX Shell.
 * 					It forks child processes for every input to the MoreShell>.
 * 					Using execlp, it executes the command array to run the given shell command
 *
 * EXECUTION	:	./DupShell
 *
 * DATE			:	13 FEB 2011
 *
 ******************************************************************************************************************/
#include "osheaders.h"
char inp[25];
char *cmd1[5];
char *cmd2[5];
int f;
int mypipe[2];
/*****************************************************************************************************************
 *
 * Function 	: 	prompt
 *
 * Parameters	:	NONE
 *
 * Description	:	It displays the prompt 'MoreShell>' and gets the input from the user and calls parseLine
 * 					It parses if the given command has a pipe and pass it to parseline as seperate arguments.
 *
 *
 ******************************************************************************************************************/


static void prompt()
{
	printf("\nDupShell > ");
	fgets(inp,25,stdin);
	inp[strlen(inp)-1]='\0';
	int count =0;
	char line1[5];

	if(strchr(inp,'|')!=NULL)

	{
	f=1;
	char *t[2];
	char *p;
	p = strtok(inp, "|");
	while (p) {
	t[count] = p;
	count++;
	p = strtok(NULL,"|");
	}
	parseline(t[0],cmd1);
	parseline(t[1],cmd2);
	}

	else
	{
		f=0;
		parseline(inp,cmd1);
	}
}

/*****************************************************************************************************************
 *
 * Function 	: 	parseline
 *
 * Parameters	:	<line> which is the input given by the user at MoreShell.
 *
 * Description	:	It parses the input and stores it in the cmd[]
 *
 *
 ******************************************************************************************************************/
int parseline(char * line , char * cmd[]) {
char * p;
int count = 0;
p = strtok(line, " ");
while (p && strcmp(p,"|") != 0) {
cmd[count] = p;
count++;
p = strtok(NULL," ");
}
cmd[count]=NULL;
return count;
}
/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	NONE
 *
 * Description	:	It forks two child process and uses pipe to execute command lines connected with pipes.
 * 					It uses dup2 to redirect IO.
 *
 *
 *
 ******************************************************************************************************************/


int main(int argc,char **argv)
{
	prompt();

	pid_t ForkPID,ForkPID1;

	while(strcmp(inp,"exit")!=0)
	{
		if (pipe(mypipe)) {
					printf("\n Sorry, Your pipe Failed \n");
					return (0);
				}


		ForkPID = fork();
	switch (ForkPID) {
	case -1: printf("Error: Failed to fork.\n"); break;
	case 0:

			if(f==1)
			{
			dup2(mypipe[1],STDOUT_FILENO);//this command redirects the outpue of the executed command into the pipe
			close(mypipe[0]);
			close(mypipe[1]);
			}
			if (execvp(cmd1[0],cmd1) == -1) {
		printf("Error: running command: '%s'\n",cmd1[0]);
		exit(0);
		}
			exit(0);


	break;

	default:
		ForkPID1 = fork();
		switch (ForkPID1) {
			case -1: printf("Error: Failed to fork.\n"); break;
			case 0:
				dup2(mypipe[0],STDIN_FILENO); //this command reads from the pipe and execvp executes it
				close(mypipe[0]);
				close(mypipe[1]);
				if(f==1)
				{
				if (execvp(cmd2[0],cmd2) == -1) {
				printf("Error: running command: '%s'\n",cmd2[0]);
				exit(0);
				}
				}
				exit(0);
			break;

			default:
				close(mypipe[0]);
				close(mypipe[1]);
				waitpid(ForkPID,NULL,0);
				waitpid(ForkPID1,NULL,0);
				prompt();
			}
	}
	}


}

