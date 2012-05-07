#include "osheaders.h"

char ipfile[MAXLEN];
char opfile[MAXLEN];

int main(int argc,char **argv)
{
	int filedes1,filedes2;
	if(argc!=3)//checking for number of arguments
		{
			printf("\nHey argument must be 3!!");
			printf("\nThe correct format is ./MyCompress <inputfilename> <outputfilename>\n");
			//exit(0);
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
			Compression(filedes1,filedes2);
			close(filedes1);
			close(filedes2);
			return 0;
		}
}//End of Main

void Compression(int fd1,int fd2)
{
	char buf[MILLION];
	char plus[1],minus[1];
	plus[0]=43;
	minus[0]=45;
	char counter[100];
	int i,j,w,n=1,count=1;
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
				printf("\nYour File size is too large for compression.\n");
			}
			else
			{

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
						if(buf[i-1]==49)
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
			}
			//End of for
			printf("\n****File Successfully Compressed\n*****");
		}// End of Else
}//End of Compression


