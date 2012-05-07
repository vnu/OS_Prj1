/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 5	:	ParFork.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It forks maximum of 30 child process each child process compress and writes a segment of the input file.
 * 					If the Fork processes reaches 30, it waits for the children to complete and then forks again.
 * 					The Segment is made for every newline character or white space.
 *
 * EXECUTION	:	./ParFork <Input File> <Output File>
 *
 * DATE			:	25 FEB 2011
 *
 ******************************************************************************************************************/

#include "osheaders.h"

char ipfile[MAXSIZE];
char opfile[MAXSIZE];
char charbuf[MAXLEN];
char *segment[1000];
char counter[10];
char c;
char *ch;

int i=0,j=0,s=0;
int segcount;
int n,w;
int times=0;
pid_t ForkPID;

/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	<Input File> <Output File>
 * 					Both the filenames must be string passed through argv[1] and argv[2]
 *
 * Description	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It forks child process if it is not the end of file and each child calls the Compress function.
 * 					If the fork count is >30, it waits and starts forking again.
 * 					Segments are created if the read character is a newline or whitespace.
 *
 *
 ******************************************************************************************************************/

int main(int argc, char **argv) {
	int fd1, fd2;
	int fcount =0;
	static int l=0;

	if (argc != 3)//checking for number of arguments
	{
		printf("\nHey argument must be 3!!");
		printf("\nThe correct format is ./ParFork <inputfilename> <outputfilename>\n");

	}
	else
	{
		printf("\n\nYou have given correct number of Arguments\n");
		strncpy(ipfile, argv[1], MAXSIZE - 1);//Storing the input and output file name from arguments
		strncpy(opfile, argv[2], MAXSIZE - 1);
		printf("\n InputFile\t: %s\n OutputFile\t: %s\n", ipfile, opfile);

		fd1 = open(ipfile, O_RDONLY);
		if (fd1 == -1) {
			printf("\nCannot open file : %s\n", ipfile);
		}
		fd2 = open(opfile, O_CREAT | O_TRUNC | O_APPEND |O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd2 > 0)
		{
			printf("\n***** File created successfully *****\n");
		}
		while (l==0)
		{
			++times;
			memset(charbuf,'\0',MAXLEN);
			j=0;
			while(n = read(fd1, &c, 1) != 0)
			{
				if (c == 10||c==32)//If the read character it a ' 'or '\n' the loop breaks making charbuf segment
				{
					charbuf[j] = c;
					s++;
					j = 0;
					break;
				}
				else// If it is not whitespace or newline keeps writing the file to buffer
				{
					charbuf[j] = c;
					j++;
				}
			}
			if(n==0)
			{
				charbuf[++j]='\0';
				l=1;
			}
			ForkPID = fork();
			fcount++;
			switch (ForkPID)
			{
			case -1:
					printf("Error: Failed to fork.\n");
					break;
			case 0://Calls the Compress function.
					Compress(charbuf,fd2);
					exit(0);
					break;
			default:// Checks whether fork count is >30  or end of file and waits accordingly
					if (fcount >30)
					{
						while (fcount != 3)//If > 30 wait till it becomes 3
						{
							wait(&ForkPID);
							fcount--;
						}
					}
					else if(l==1)
					{
						while (fcount!=0) //If end of file wait till it is completed.
						{
							wait(&ForkPID);
							fcount--;
						}
					}
			}
		}
	}
	printf("\nTotal Child Process Created\t: %d\n",times);
	printf("\n**** Program Successfully Compressed your file ****\n\n");
	close(fd1);
	close(fd2);
	return 0;
}

/*****************************************************************************************************************
 *
 *	Function	:	Compress
 *
 *	Parameters	:	<Segment Buffer> <OutputFile FD> where FD : File Descriptors (int)where the buffer is each
 *					Segment from the file
 *
 *	Description :	Gets the file descriptor and Buffer. Reads each character from Buffer, check for the constraints
 *					and Compresses. Write the Compressed contents to the output File using System Call 'write'.
 *
 *	Constraints	:	whitespace 	:	Write to file
 *					newline		:	Write to file
 *					1			:	If the sequence of 1 is greater than 16, have count, write '+count+'
 *					0			:	If the sequence of 1 is greater than 16, have count, write '-count-'
 *					If the count of 1 or 0 is less than 16 write as many 1's or 0's to the file.
 *
 *					The characters are checked using ascii vallue :
 *
 *					'1' = 49 ; '0' = 48 ; ' ' = 32 ; ''\n' = 10
 *
 ******************************************************************************************************************/

void Compress(char *buf,int fd2)
{
	char plus[1],minus[1];
	plus[0]=43;
	minus[0]=45;
	char counter[100];
	int i,j,w,n=1,count=1;
	char c;
	size_t m=strlen(buf);
	for(i=0;i<=m;i++)
	{
		if(i<=0)
		{
			if (buf[i] == 10)
			{
				w = write(fd2, (void *) (&buf[i]), 1);
			}
			else if (buf[i] == 32)
			{
				w = write(fd2, (void *) (&buf[i]), 1);
			}
		}//end of if
		else
		{
			if((buf[i]==buf[i-1])&&(buf[i]!=10)&&(buf[i]!=32))
			{
				count++;
			}
			else if((count<16))
			{
				for(j=0;j<count;j++)
				{
					w=write(fd2,(void *)(&buf[i-1]),1);
				}
				count=1;
			}
			else if(count>=16)
			{
				sprintf(counter,"%d",count);
				int countsize=strlen(counter);
				if(buf[i-1]==49)//If it is 1 and count >16
				{
					w=write(fd2,(void *)(&plus[0]),1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,(void *)(&plus[0]),1);
				}
				else//If it is 0 and count >16
				{
					w=write(fd2,(void *)(&minus[0]),1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,(void *)(&minus[0]),1);
				}
				count=1;
			}
			else if(buf[i]==10)
			{
				w=write(fd2,(void *)(&buf[i]),1);
				count=1;
			}
			else if(buf[i]==32)
			{
				w=write(fd2,(void *)(&buf[i]),1);
				count=1;
			}
		}//End of else if
		continue;
	}//End of for
}//End of Compress


