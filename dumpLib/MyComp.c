#include "osheaders.h"

char ipfile[MAXLEN];
char opfile[MAXLEN];

int main(int argc,char **argv)
{
	char buf[MILLION];
	char plus[1],minus[1];
	plus[0]=43;
	minus[0]=45;

	char counter[10];
	int fd1,fd2,i,j,n=1,count=1,w;
	//size_t n;
	char c;
	int end;
	size_t m=0;
	if(argc!=3)//checking for number of arguments
	{
		printf("\nHey argument must be 3!!");
		printf("\nThe correct format is ./MyCompress <inputfilename> <outputfilename>\n");
	}
	else
	{
		printf("You have given correct number of Arguments\n");
		strncpy(ipfile,argv[1],MAXLEN-1);//Storing the input and output file name from arugments
		strncpy(opfile,argv[2],MAXLEN-1);
		printf(" ip:%s\n op:%s\n",ipfile,opfile);
		fd1=open(argv[1],O_RDONLY);
		fd2=open(argv[2],O_CREAT|O_RDWR,S_IRUSR|S_IWUSR|S_IRWXU|S_IRGRP|S_IROTH);

		while(n!=0)
		{
			n=read(fd1,&c,1);
			if(n==1)
			{
				buf[m]=c;
				++m;
			}
		}
		printf("Value of M : %lu",m);
		close(fd1);

		if(fd1==-1)
		{
			printf("\nCannot open file : %s\n",argv[1]);
		}
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
				//continue;
			}
			else
			{
				if((buf[i]==buf[i-1])&&(buf[i]!=10)&&(buf[i]!=32))
				{
					count++;
					//continue;
				}
				else if((count<16))
				{
					for(j=0;j<count;j++)
					{
						int k =i-1;
						printf("\n Value of k and in buf :%d\t%c\n",k,buf[k]);
						w=write(fd2,(void *)(&buf[k]),1);
					}
					count=1;
					printf("\nI came here");

				}
				else if(count>=16)
				{
					sprintf(counter,"%d",count);
					int countsize=strlen(counter);

					printf("\n I am in hello greater than 16 :%s,%d",counter,countsize);

					if(buf[i-1]==48)
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

					printf("\n I am in greater than 16 :%d",count);
					count=1;
				}
				else if(buf[i]==10)
				{
					printf("\nI am writing a new line now \n");
					w=write(fd2,(void *)(&buf[i]),1);
					count=1;
					//continue;
				}
				else if(buf[i]==32)
				{
					printf("\nI am writing a blank space now \n");
					w=write(fd2,(void *)(&buf[i]),1);
					count=1;
					//continue;
				}
				printf("\nI also came here \n");
			}

			printf("\nValue of i at the end :%d",i);
			continue;
		}//End of for

	}
		//opening the file


}//Main

