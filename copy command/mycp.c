/** mycp.c uses for cpoy files and copy multiple files to target directory ***/


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#define BUFFERSIZE 1024
#define COPYMORE 0644
int main(int ac, char *av[])
{
	int input_fd,output_fd1,output_fd2;
	if(ac==3)
	{
		char *source = av[1];
		char *dest = av[2];
		struct stat check;
		int i;
		int result = access (dest, F_OK);	// F_OK tests existence also (R_OK,W_OK,X_OK)for readable, writeable, executable
		
		if(result<0)
		{	
			printf("Destination file doesnot exist we want to create file %d \n",result);
		}
		lstat(av[2], &check);	
		printf("%s is given destination!!\n",dest);   
		printf("%s is given source!!\n",source); 
		if(( input_fd = open(source, O_RDONLY,0777))<0)
		{ 
			perror("\n \n \n Input doesnot exist: \n ");
		}
		else
		{	
			printf("Copying file to file\n");
			if((output_fd1 = open(dest,O_WRONLY))>0)
			{
				char y; 
				printf("source file is not empty do you wana override it: ");
				scanf("%s",&y);	
				if(y=='n')
				{
					return 0;	
				}
				else if(y=='y')
				{
					char buf[8192];
					size_t result = read(input_fd, &buf[0], sizeof(buf));
					write(output_fd1, &buf[0], result) == result;
					return 0;
				}
			}
			else
			{	
				if (S_ISDIR(check.st_mode))
				{					
						access(dest,W_OK);
						if(EACCES == errno)
				         {
							printf("error with permission access");
							exit(0);
						 }
						strcat(dest, "/");
						strcat(dest, source);
						if((output_fd1=open(dest,O_WRONLY,0777))>0)
						{
							char y; 
							printf("source file is not empty do you wana override it: ");
							scanf("%s",&y);	
							if(y=='n')
							{
								return 0;	
							}
							else if(y=='y')
							{
								char buf[8192];
								size_t result = read(input_fd, &buf[0], sizeof(buf));
								write(output_fd1, &buf[0], result) == result;
								return 0;
							}
							
						}
						else
						{
							
							output_fd1=open(dest,O_CREAT|O_WRONLY,0777);
							char buf[8192];
							size_t result = read(input_fd, &buf[0], sizeof(buf));
							printf("you file size is: %zd\n", result);
							write(output_fd1, &buf[0], result) == result;
							return 0;
						}	
				}
					
				else
				{
					output_fd1=open(dest,O_CREAT|O_WRONLY,0777);
					char buf[8192];
					size_t result = read(input_fd, &buf[0], sizeof(buf));
					printf("you file size is: %zd\n", result);
					write(output_fd1, &buf[0], result) == result;
					return 0;
						
		
				}				
			}
		}						
	}

else if(ac>3)
{
	struct stat check;	
	int i,count=ac-1;
	printf("your ac value is %d \n",ac);
	char *dest1 = av[count];
	char *dest;
	lstat(dest1, &check);
	dest=malloc(strlen(av[ac-1])+1);
	strcat(dest,av[count]);
	if(!(S_ISDIR(check.st_mode)))
	{
		printf("Dir created\n \n \n");
		mkdir(dest,0777);
	}
	
	for(i=count-1;i>=1;i--)
	{
		if(( input_fd = open(av[i], O_RDONLY))<0)
		{ 
			perror("\n \n \n Input doesnot exist: \n ");
			continue;
		}
		else 	
		{
	        access(dest,W_OK);
			if(EACCES == errno)
			{
				printf("error with permission access");                         
				exit(0);
			}
			
			free(dest);
			dest=malloc(strlen(av[i])+strlen(av[ac-1])+2);
			strcat(dest,av[count]);
			strcat(dest, "/");
			strcat(dest, av[i]);
			if((output_fd1=open(dest,O_WRONLY))>0)
			{
				char y; 
				printf("source file is not empty do you wana override it: ");
				scanf("%s",&y);	
				if(y=='n')
				{	
				}
				else if(y=='y')
				{
					char buf[8192];
					size_t result = read(input_fd, &buf[0], sizeof(buf));
					write(output_fd1, &buf[0], result);
				}							
			}
			else
			{							
				output_fd1=open(dest,O_CREAT|O_WRONLY,0777);
				char buf[8192];
				size_t result = read(input_fd, &buf[0], sizeof(buf));
				write(output_fd1, &buf[0], result);	
			}	
						
		}
	}
}

	else
	{
		printf("usage: wrong source and destination\n");
		exit(1);
	}
}
