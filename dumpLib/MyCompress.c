/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 1	:	MyCompress.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					Opens the Input File and creates the Output File using System call 'open'
 * 					Passes the File Descriptors for the input and the output file to the Compression Function
 *
 * EXECUTION	:	./MyCompress <Input File> <Output File>
 *
 * DATE			:	28 JAN 2011
 *
 ******************************************************************************************************************/

#include "osheaders.h"

char ipfile[MAXSIZE];
char opfile[MAXSIZE];
char ch='\0',c;
char p=43;
char m=45;
char counter[100];

int j=0,w,l=0;
int i=0,count=0,n;

/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	<Input File> <Output File>
 * 					Both the filenames must be string passed through argv[1] and argv[2] *
 *
 * Description	:	Opens the Input File and Creates the Output File if not existing using System Call 'open'
 * 					Calls the Compression <InputFile FD> <OutputFile FD> where FD : File Descriptors (int)
 *
 ******************************************************************************************************************/

int main(int argc,char **argv)
{
	int filedes1,filedes2;
	if(argc!=3)//checking for number of arguments
		{
			printf("\nHey argument must be 3!!");
			printf("\nThe correct format is ./MyCompress <inputfilename> <outputfilename>\n");
		}
	else
		{
			printf("\nYou have given correct number of Arguments\n\n");
			strncpy(ipfile,argv[1],MAXSIZE-1);//Storing the input and output file name from arguments
			strncpy(opfile,argv[2],MAXSIZE-1);
			printf(" InputFile\t: %s\n OutputFile\t: %s\n",ipfile,opfile);

			filedes1=open(ipfile,O_RDONLY);

			if(filedes1==-1)
				{
					printf("\nCannot open file : %s\n",ipfile);
				}

			filedes2=open(opfile,O_CREAT|O_TRUNC|O_RDWR,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

			if(filedes2>0)
			{
				printf("\n**** File created successfully ****\n");
			}

			Compression(filedes1,filedes2);//Calling the function
			printf("\n**** Program Successfully Compressed your file ****\n\n");
			close(filedes1);
			close(filedes2);
			return 0;
		}
}//End of Main


/*****************************************************************************************************************
 *
 *	Function	:	Compression
 *
 *	Parameters	:	 <InputFile FD> <OutputFile FD> where FD : File Descriptors (int)
 *
 *	Description :	Gets the file descriptors. Reads first character.
 *					If it is whitespace or newline assigns it to ch. (ch will be the previous read character.)
 *					Calls the write function which compresses and write to the file.
 *
 ******************************************************************************************************************/

void Compression(int fd1,int fd2)
{
	while(l==0)
	{
		if((n=read(fd1,&c,1)==0))
		{
			//Checks whether the file is empty!!
			if(i==0)
			{
				printf("\n*****The File is Empty. Nothing can be written*****\n");
				break;
			}
			else //Checks for the first character to be " " or "\n" and assigns it to ch
			{
				l=1;
				ch=c;
				writefile(fd1,fd2);
				break;
			}

		}
		else
		{
			writefile(fd1,fd2);

		}
		++i;
	}//End of While
}// End of Compression;


/*****************************************************************************************************************
 *
 *	Function	:	WriteFile
 *
 *	Parameters	:	<InputFile FD> <OutputFile FD> where FD : File Descriptors (int)
 *
 *	Description :	Gets the file descriptors. Reads each character, check for the constraints and Compresses.
 *					Write the Compressed contents to the output File using System Call 'write'.
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

void writefile(int fd1,int fd2)
{
		//This if checks for the first character. either writes are start assigning the count
		if((i==0)||(count<1))
		{
			if (c == 10)
			{
				w = write(fd2, &c, 1);
				ch=c;
			}
			else if (c == 32)
			{
				w = write(fd2, &c, 1);
				ch=c;
			}
			else if((c==49)||(c==48))
			{
				count=1;
				ch=c;
			}
		}//end of if

		//checks for the above given constraints

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
						w=write(fd2,&ch,1);
					}
					count=1;
				}
				else if(ch==48)
				{
					for(j=0;j<count;j++)
					{
						w=write(fd2,&ch,1);
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
					w=write(fd2,&p,1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,&p,1);
					count=1;
					if((c==48))
					{
						ch=c;
					}

				}
				else
				{
					w=write(fd2,&m,1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,&m,1);
					count=1;
					if((c==49))
					{
						ch=c;
					}
				}
			}
			if((c==10)&&(l!=1))
			{
				w=write(fd2,&c,1);
				ch=c;
				count=1;
			}
			else if((c==32)&&(l!=1))
			{
				w=write(fd2,&c,1);
				ch=c;
				count=1;
			}
		}//End of else*/
}


