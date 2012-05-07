/*****************************************************************************************************************
 *
 * NAME 		: 	VINU CHARANYA ATHANGUDI PURUSHOTHAMAN
 * PERSON # 	:	37648013
 * PROGRAM ##	:	Compare.c
 * HEADER FILE	:	osheaders.h
 *
 * DESCRIPTION	:	Program takes two arguments from the command line <Input File> <Output File>
 * 					It Compares both the files character by Character and says if both files are same
 *
 * EXECUTION	:	./Compare <Input File> <Output File>
 *
 * DATE			:	25 JAN 2011
 *
 ******************************************************************************************************************/

#include "osheaders.h"
int main(int argc, char **argv)
{

	char * SourceFile;
	char * OutputFile;
	int t;
	char c,c1;
	t=0;
	size_t fsource,fdest;
	if(argc != 3)
			{
				printf("Please provide valid arguments of Source and Destination Files\n");
				return 0;
			}
		SourceFile = argv[1];
		OutputFile = argv[2];
		FILE *finp,*fout;
		finp= fopen(SourceFile, "r");
		fout= fopen(OutputFile, "r");

		fseek(finp,0,SEEK_END);
		fsource = ftell(finp);
		rewind(finp);

		fseek(fout,0,SEEK_END);
		fdest = ftell(fout);
		rewind(fout);

			while(!feof(finp) )
			{
				c= getc(finp);
				c1= getc(fout);
				if(c!=c1)
				{
					 t=1;
				}
			}

			printf("\nNumber of Character in Input File\t: %lu\n",fsource);
			printf("\nNumber of Character in Output File\t: %lu\n",fdest);

			if (t==0)
			{
				printf("\n\n*****Success Your Input and Output files are similar*****\n\n");
			}
			else
			{
				printf("\n\n*****Failure. Your Input and Output Files are different*****\n\n");
			}


}
