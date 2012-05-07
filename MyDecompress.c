/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM 2	:	MyDecompress.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 			Opens the Input File and creates the Output File using System call 'open'
 * 			Passes the File Descriptors for the input and the output file to the Decompression Function
 *
 * EXECUTION	:	./MyDecompress <Input File> <Output File>
 *
 * DATE			:	28 JAN 2011
 *
 ******************************************************************************************************************/

#include "osheaders.h"
char ipfile[MAXSIZE];
char opfile[MAXSIZE];


char ch = '\0', c;
char p = 43;
char m = 45;
char counter[100];
char zero=48;
char one = 49;

int i, j, k, w, n = 1, count = 1, v = 0,l=0;

/*****************************************************************************************************************
 *
 * Function 	: 	Main
 *
 * Parameters	:	<Input File> <Output File>
 * 					Both the filenames must be string passed through argv[1] and argv[2] *
 *
 * Description	:	Opens the Input File and Creates the Output File if not existing using System Call 'open'
 * 					Calls the Decompression <InputFile FD> <OutputFile FD> where FD : File Descriptors (int)
 *
 ******************************************************************************************************************/


int main(int argc, char **argv) {
	int filedes1, filedes2;
	if (argc != 3)//checking for number of arguments
	{
		printf("\nHey argument must be 3!!");
		printf(
				"\nThe correct format is ./MyDecompress <inputfilename> <outputfilename>\n");
	}
	else
	{
		printf("\nYou have given correct number of Arguments\n");
		strncpy(ipfile, argv[1], MAXSIZE - 1);//Storing the input and output file name from arguments
		strncpy(opfile, argv[2], MAXSIZE - 1);
		printf("\n Input File\t: %s\n Output File\t: %s\n", ipfile, opfile);

		filedes1 = open(ipfile, O_RDONLY);

		if (filedes1 == -1)
		{
			printf("\nCannot open file : %s\n", ipfile);
			exit(0);
		}

		filedes2 = open(opfile, O_CREAT | O_TRUNC| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

		if(filedes2>0)
		{
			printf("\n**** File created successfully ****\n");
		}

		Decompression(filedes1, filedes2);
		printf("\n**** Program Successfully Decompressed your file ****\n\n");
		close(filedes1);
		close(filedes2);
		return 0;
	}
}//End of Main

/*****************************************************************************************************************
 *
 *	Function	:	Decompression
 *
 *	Parameters	:	 <InputFile FD> <OutputFile FD> where FD : File Descriptors (int)
 *
 *	Description :	Gets the file descriptors. Reads first character.
 *					If it is whitespace or newline assigns it to ch. (ch will be the previous read character.)
 *					Calls the write function which Decompresses and write to the file.
 *
 ******************************************************************************************************************/

void Decompression(int fd1, int fd2) {
	while(l==0)
	{
		if((n=read(fd1,&c,1))==0)
		{
			if(i==0)
			{
				printf("\n*****The File is Empty. Nothing can be written*****\n");
				break;
			}
			else
			{
				l=1;
			}
		}
		else
		{
			writefile(fd1,fd2);
		}
		++i;

	}//End of while

}//End of Decompression

/*****************************************************************************************************************
 *
 *	Function	:	WriteFile
 *
 *	Parameters	:	<InputFile FD> <OutputFile FD> where FD : File Descriptors (int)
 *
 *	Description :	Gets the file descriptors. Reads each character, check for the constraints and Compresses.
 *					Write the Decompressed contents to the output File using System Call 'write'.
 *
 *	Constraints	:	whitespace 	:	Write to file
 *					newline		:	Write to file
 *					1			:	If the sequence of 1 is greater than 16, have count, write '+count+'
 *					0			:	If the sequence of 1 is greater than 16, have count, write '-count-'
 *					If the count of 1 or 0 is less than 16 write as many 1's or 0's to the file.
 *
 *					The characters are checked using ascii vallue :
 *
 *					'1' = 49 ; '0' = 48 ; ' ' = 32 ; ''\n' = 10 ; '+' = 43 ; '-' = 45
 *
 ******************************************************************************************************************/

void writefile(int fd1, int fd2)
{
	/*
	 * Writes to the file if the read character is 1,0,' ','\n'
	 */
	if ((c == 10))
	{
		w = write(fd2, (&c), 1);
	}
	else if ((c == 32))
	{
		w = write(fd2, &c, 1);
	}
	else if (c == 49)
	{
		w = write(fd2, &c, 1);
		count = 1;
	}
	else if (c == 48)
	{
		w = write(fd2, &c, 1);
		count = 1;
	}
	/*
	 * If it is '+' or '-' parses the following string to integer and prints as many number of 1's or 0's
	 */
	else if (c == 43)
	{
		memset(counter, '\0', 100);
		n=read(fd1,&c,1);
		for (i = i + 1, v = 0; (c != 43); ++i, ++v)
		{
			counter[v] = c;
			n=read(fd1,&c,1);
		}
		int counti = atoi(counter);
		for (k = 0; k < counti; k++)
		{
			w = write(fd2, &one, 1);
		}
	}
	else if (c == 45)
		{
			memset(counter, '\0', 100);
			n=read(fd1,&c,1);
			for (i = i + 1, v = 0; (c != 45); ++i, ++v)
			{
				counter[v] = c;
				n=read(fd1,&c,1);
			}
			int counti = atoi(counter);
			for (k = 0; k < counti; k++)
			{
				w = write(fd2, &zero, 1);
			}
		}
}
