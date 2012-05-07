/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 9	:	ParFork.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It creates 10 threads that compresses and writes a segment of the input file to the output file.
 * 					If the Fork processes reaches 30, it waits for the children to complete and then forks again.
 * 					The Segment is made for every newline character or white space.
 *
 * EXECUTION	:	./ParThread <Input File> <Output File>
 *
 * DATE			:	25 FEB 2011
 *
 ******************************************************************************************************************/


#include"osheaders.h"

void * Compress(void *);
char ipfile[MAXSIZE];
char opfile[MAXSIZE];
char charbuf[MAXLEN];
char *segment[1000];
char counter[10];
char c;
char *ch;
int fd1, fd2;
int i=0,j=0,s=0;
int segcount;
int n,w;
int times=0;


//the arguments in this structure are passed to the thread
struct thread_arguments {
char t[10000];
};

/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	<Input File> <Output File>
 * 					Both the filenames must be string passed through argv[1] and argv[2]
 *
 * Description	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It creates thread if it is not the end of file and each child calls the Compress function.
 * 					If the fork count is >30, it waits and starts forking again.
 * 					Segments are created if the read character is a newline or whitespace.
 *
 *
 ******************************************************************************************************************/

int main(int argc, char **argv) {
	int rc;
	pthread_t T[10];
	struct thread_arguments my_arguments1[10];//Objects for the structure is declared
	int count;
	void* status1;


	//Initializing thread defaults
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_setscope(&attr1, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_JOINABLE);


	if (argc != 3)//checking for number of arguments
	{
		printf("\nHey argument must be 3!!");
		printf("\nThe correct format is ./ParThread <inputfilename> <outputfilename>\n");

	} else {
		printf("\nYou have given correct number of Arguments\n");
		strncpy(ipfile, argv[1], MAXSIZE - 1);//Storing the input and output file name from arguments
		strncpy(opfile, argv[2], MAXSIZE - 1);
		printf("\n Input File\t:%s\n OutputFile\t:%s\n", ipfile, opfile);

		fd1 = open(ipfile, O_RDONLY);
		if (fd1 == -1) {
			printf("\nCannot open file : %s\n", ipfile);
		}
		fd2 = open(opfile, O_CREAT | O_TRUNC |O_APPEND|O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd2 > 0)
		{
			printf("\n***** File created successfully *****\n");
		}


		static int l=0;
		count=0;
		while (l==0)
		{
			++times;
			memset(charbuf,'\0',MAXLEN);
			int j=0;
			while(n = read(fd1, &c, 1) != 0)
			{
				if (c == 10||c==32)
				{
					charbuf[j] = c;
					s++;
					j = 0;
					break;
				}
				else
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
			for(i=0;i<strlen(charbuf);i++)
				my_arguments1[count].t[i]=charbuf[i];
			my_arguments1[count].t[i]='\0';

			//Multiple threads are created and arguments are passed
			rc = pthread_create(&T[count],&attr1,Compress,&my_arguments1[count]);
			if (rc)
			{
				printf("ERROR; Return code from pthread_create(t1) is %d\n", rc);
				exit(-1);
			}
			count++;
			//If the thread count is > 10 or if it is the end of the file
			if(count==10 || l==1)
			{
				int k=0;
				while(count!=0)
				{
					rc=pthread_join(T[k], &status1);//Waiting for the threads to complete execution
					if(rc)
					{
						printf("ERROR; Return code from pthread_create(t1) is %d\n", rc);
						exit(-1);
					}
					count--;
					k++;
				}
			}
		}
	}
	printf("\n**** Program Successfully Compressed your file ****\n\n");
}
/*****************************************************************************************************************
 *
 *	Function	:	Compress
 *
 *	Parameters	:	 where FD : File Descriptors (int)where the buffer is each
 *					Segment from the file
 *
 *	Description :	Gets the thread arguments. Reads each character, check for the constraints
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
void * Compress(void *args)
{
	struct thread_arguments *a;
	a = (struct thread_arguments *)args;
	char plus[1],minus[1];
	plus[0]=43;
	minus[0]=45;
	char counter[100];
	int i,j,w,n=1,count=1;
	char c;
	size_t m=strlen(a->t);
	for(i=0;i<=m;i++)
	{
		if(i<=0)
		{
			if (a->t[i] == 10)
			{
				w = write(fd2, (void *) (&a->t[i]), 1);
			}
			else if (a->t[i] == 32)
			{
				w = write(fd2, (void *) (&a->t[i]), 1);
			}
		}//end of if
		else
		{
			if((a->t[i]==a->t[i-1])&&(a->t[i]!=10)&&(a->t[i]!=32))
			{
				count++;
			}
			else if((count<16))
			{
				for(j=0;j<count;j++)
				{
					w=write(fd2,(void *)(&a->t[i-1]),1);
				}
				count=1;
			}
			else if(count>=16)
			{
				sprintf(counter,"%d",count);
				int countsize=strlen(counter);
				if(a->t[i-1]==49)
				{
					w=write(fd2,(void *)(&plus[0]),1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,(void *)(&plus[0]),1);
				}
				else
				{
					w=write(fd2,(void *)(&minus[0]),1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,(void *)(&minus[0]),1);
				}
				count=1;
			}
			else if(a->t[i]==10)
			{
				w=write(fd2,(void *)(&a->t[i]),1);
				count=1;
			}
			else if(a->t[i]==32)
			{
				w=write(fd2,(void *)(&a->t[i]),1);
				count=1;
			}
		}//End of else if
		continue;
	}
	pthread_exit(NULL);
}
