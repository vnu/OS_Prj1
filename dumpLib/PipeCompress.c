/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 4	:	PipeCompress.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It forks two child process and both child communicate through a pipe.
 * 					The first child, reads from the input file, compresses it and writes to the pipe
 * 					The second child reads from the pipe and writes to the output file.
 *
 * EXECUTION	:	./PipeCompress <Input File> <Output File>
 *
 * DATE			:	29 JAN 2011
 *
 ******************************************************************************************************************/

#include "osheaders.h"

int fd1,fd2;
int mypipe[2];
char ipfile[MAXSIZE];
char opfile[MAXSIZE];
int i=0,count=0,n;
char ch='\0',c;
char p=43;
char m=45;
char counter[100];
int j=0,w,l=0;
pid_t ForkPID1;

/*****************************************************************************************************************
 *
 *	Function	:	PipeCompress
 *
 *	Parameters	:	NONE
 *
 *	Description :	Reads first character from input file descriptor.
 *					If it is whitespace or newline assigns it to ch. (ch will be the previous read character.)
 *					Calls the write function which compresses and write to the pipe.
 *
 ******************************************************************************************************************/

void PipeCompress()
{
	while(l==0)
	{
		if((n=read(fd1,&c,1)==0))
		{
			if(i==0)
			{
				printf("\n***** The File is Empty. Nothing can be Read or Written *****\n");
				break;
			}
			else
			{
				l=1;
				ch=c;
				PipeWrite();
				break;
			}
		}
		else
		{
			PipeWrite();
		}
		++i;
	}
	printf("\n**** File Successfully Compressed ****\n");
}// End of Compression;

/*****************************************************************************************************************
 *
 *	Function	:	PipeWrite
 *
 *	Parameters	:	NONE
 *
 *	Description :	Reads each character from input file descriptor, check for the constraints and Compresses.
 *					Write the Compressed contents to the pipe.
 *
 *	Constraints	:	whitespace 	:	Write to pipe
 *					newline		:	Write to pipe
 *					1			:	If the sequence of 1 is greater than 16, have count, write '+count+'
 *					0			:	If the sequence of 1 is greater than 16, have count, write '-count-'
 *					If the count of 1 or 0 is less than 16 write as many 1's or 0's to the pipe.
 *
 *					The characters are checked using ascii vallue :
 *
 *					'1' = 49 ; '0' = 48 ; ' ' = 32 ; ''\n' = 10
 *
 ******************************************************************************************************************/

void PipeWrite()
{
		if((i==0)||(count<1))
		{
			if (c == 10)
			{
				w = write(mypipe[1], &c, 1);
				ch=c;
			}
			else if (c == 32)
			{
				w = write(mypipe[1], &c, 1);
				ch=c;
			}
			else if ((c == 49) || (c == 48))
			{
				count = 1;
				ch = c;
			}

		}//end of if
		else
		{
			if((c==ch)&&(c!=10)&&(c!=32)&&(l!=1))
			{
				++count;
				ch=c;
			}
			else if((count<16))
			{
				if(ch==49)
				{
					for(j=0;j<count;j++)
					{
						w=write(mypipe[1],&ch,1);
					}
					count=1;
				}
				else if(ch==48)
				{
					for(j=0;j<count;j++)
					{
						w=write(mypipe[1],&ch,1);
					}
					count=1;
				}
				if((c==49)||(c==48)&&(l!=1))
				{
					ch=c;
				}
			}
			else if((count>=16))
			{
				sprintf(counter,"%d",count);
				int countsize=strlen(counter);
				if(ch==49)
				{
					w=write(mypipe[1],&p,1);
					w=write(mypipe[1],(void *)(counter),countsize);
					w=write(mypipe[1],&p,1);
					count=1;

					if((c==48))
					{
						ch=c;
					}
				}
				else
				{
					w=write(mypipe[1],&m,1);
					w=write(mypipe[1],(void *)(counter),countsize);
					w=write(mypipe[1],&m,1);
					count=1;
					if((c==49))
					{
						ch=c;
					}
				}
			}
			if((c==10)&&(l!=1))
			{
				w=write(mypipe[1],&c,1);
				ch=c;
				count=1;
			}
			else if((c==32)&&(l!=1))
			{
				w=write(mypipe[1],&c,1);
				ch=c;
				count=1;
			}
		}//End of else if*/
}

/*****************************************************************************************************************
 *
 *	Function	:	FileWrite
 *
 *	Parameters	:	NONE
 *
 *	Description :	Read characters from pipe in the second forked child and writes it to the Output File Descriptor
 *
 ******************************************************************************************************************/

void FileWrite()
{
	while(read(mypipe[0],&c,1)>0)
	{
		write(fd2,&c,1);
	}


}
/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	<Input File> <Output File>
 * 					Both the filenames must be string passed through argv[1] and argv[2]
 *
 * Description	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It forks two child process and both child communicate through a pipe.
 * 					The first child, reads from the input file, compresses it and writes to the pipe
 * 					The second child reads from the pipe and writes to the output file.
 *
 *
 ******************************************************************************************************************/


int main(int argc,char **argv)
{
	if (argc != 3)//checking for number of arguments
	{
		printf("\nHey argument must be 3!!");
		printf(
				"\nThe correct format is ./PipeCompress <inputfilename> <outputfilename>\n");
		//exit(0);
	} else {
		printf("\n\nYou have given correct number of Arguments\n");
		strncpy(ipfile, argv[1], MAXSIZE - 1);//Storing the input and output file name from arguments
		strncpy(opfile, argv[2], MAXSIZE - 1);
		printf("\n InputFile\t: %s\n Output File\t: %s\n", ipfile, opfile);

		fd1 = open(ipfile, O_RDONLY);
		if (fd1 == -1) {
			printf("\nCannot open file : %s\n", ipfile);
		}
		fd2 = open(opfile, O_CREAT | O_TRUNC | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd2 > 0)
		{
			printf("\n**** File created successfully ****\n");
		}

		if (pipe(mypipe))//Check if pipe is created
		{
			printf("\n Sorry, Your pipe Failed \n");
			return (0);
		}

		else {
			pid_t ForkPID;
			ForkPID = fork();

			switch (ForkPID) {
			case -1:
				printf("Error: Failed to fork.\n");
				break;
			case 0:
				close(mypipe[0]);//This child only writes from pipe so input pipe is closed
				PipeCompress();
				break;

			default:

				ForkPID1 = fork();//Second child

				switch (ForkPID1) {
				case -1:
					printf("Error: Failed to fork.\n");
					break;
				case 0://This child only reads from pipe so output pipe is closed
					close(mypipe[1]);
					FileWrite();
					break;

				default://Closes both the pipes and waits for the both children to complete before exiting
					close(mypipe[0]);
					close(mypipe[1]);
					waitpid(ForkPID, NULL, 0);
					waitpid(ForkPID1, NULL, 0);
					printf("Fork executed successfully\n");
				}

			}
		}
	}
}
