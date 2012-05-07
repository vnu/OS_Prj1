#include "osheaders.h"
char ipfile[MAXLEN];
char opfile[MAXLEN];

int main(int argc,char **argv)
{
	int filedes1,filedes2;
	if(argc!=3)//checking for number of arguments
		{
			printf("\nHey argument must be 3!!");
			printf("\nThe correct format is ./MyDecompress <inputfilename> <outputfilename>\n");
		}
	else
		{
			printf("You have given correct number of Arguments\n");
			strncpy(ipfile,argv[1],MAXLEN-1);//Storing the input and output file name from arugments
			strncpy(opfile,argv[2],MAXLEN-1);
			printf(" ip:%s\n op:%s\n",ipfile,opfile);
			filedes1=open(ipfile,O_RDONLY);
			if(filedes1==-1)
				{
					printf("\nCannot open file : %s\n",ipfile);
				}
			filedes2=open(opfile,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR|S_IRWXU|S_IRGRP|S_IROTH);
			Decompression(filedes1,filedes2);
			printf("\nProgram Successfully Decompressed your file \n");
			close(filedes1);
			close(filedes2);
			return 0;
		}
}//End of Main

void Decompression(int fd1,int fd2)
{
	char buf[MILLION];
	char plus[1],minus[1];
	char binary[2];
	binary[0]=48;
	binary[1]=49;
	plus[0]=43;
	minus[0]=45;
	char counter[100];
	int i,j,k,w,n=1,count=1,v=0;
	char c;
	size_t m=0;

	while(n!=0)
			{
				n=read(fd1,&c,1);
				if(n==1)
				{
					buf[m]=c;
					++m;
				}
			}//End of while

			printf("\nTotal file characters: %lu",m);

			if(m>=MILLION)
			{
				printf("\nYour File size is too large for Decompression.\n");
			}
			else
			{

			for(i=0;i<=m;i++)
			{

					if (buf[i] == 10)
					{
						w = write(fd2, (void *) (&buf[i]), 1);
					}
					else if (buf[i] == 32)
					{
						w = write(fd2, (void *) (&buf[i]), 1);
					}
					else if(buf[i]==49)
					{
						w = write(fd2, (void *) (&buf[i]), 1);
						count = 1;
					}
					else if (buf[i] == 48)
					{
						w = write(fd2, (void *) (&buf[i]), 1);
						count = 1;
					}
					else if(buf[i]==43)
					{
						memset(counter,'\0',100);
						for(i=i+1,v=0;(buf[i]!=43)&&(i!=(m+1));++i,++v)
						{
							counter[v]=buf[i];
						}

						int counti=atoi(counter);

						for(k=0;k<counti;k++)
						{

							w = write(fd2, (void *)(&binary[1]), 1);

						}
					}
					else if(buf[i]==45)
					{
						memset(counter,'\0',100);
						for(i=i+1,v=0;(buf[i]!=45)&&(i!=(m+1));++i,++v)
						{
							counter[v]=buf[i];
						}

						int counti=atoi(counter);

						for(k=0;k<counti;k++)
						{

							w = write(fd2, (void *)(&binary[0]), 1);

						}
					}

			}
			//End of for
			printf("\n****File Successfully Decompressed*****\n");
			//printf("\nTotal file characters: %lu",m);
		}// End of Else
}//End of Compression

