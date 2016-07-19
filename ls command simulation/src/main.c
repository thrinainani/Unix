/*
************************************************************************************************************************************************

NAME		: main.c
AUTHOR		: THRINAI BATCHU
DESCRIPTION	:

*************************************************************************************************************************************************/

#include <stdio.h>
#include<stdlib.h>
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
#define BUFFERSIZ 1024 
#define COPYMORE 0644
#include "../include/myls.h"
int count;
int main(int argc, char **argv)
{
int option;

//char *source = argv[2];
count = optind + 1;
int dirs = 0,i=1,j=1;
int enumber = 1;
int def=0,sflag = 0, lflag = 0, Rflag = 0,tflag = 0, Sflag = 0,cflag = 0, uflag = 0; 
// printf("\n your optind %d \n", optind);
//  printf("\n your argc %d \n", argc);

struct stat s;
stat(argv[i],&s);
while(j < argc) 
{

	if(stat(argv[i], &s) == -1) 
	{
		i++;
		j++;
	}

	else
	{
		i++;
		dirs++;
		j++;
	}
}
	
	if(argc > 2)
printf("\nYou entered '%d' existing directories\n\n", dirs);

while((option= getopt(argc, argv, "cuhslRtS")) != -1)
	switch(option)
	{
	case 'h':
	
		def =1;
		mylsh();		
	break;	
	case 's':
		sflag = 1;
		def = 1;
		
	break;

	case 'l':
		lflag = 1;
		def = 1;
		
	break;
	
	case 'R':
		Rflag = 1;
		def = 1;
		
	break;

	case 't':
		tflag = 1;
		def = 1;
	break;
	case 'c':
		cflag = 1;
		def = 1;
	break;
	case 'u':
		uflag = 1;
		def = 1;
	break;
	case 'S':
		def = 1;
		Sflag = 1;
		
	break;		
	
	case '?':
			printf("Usage: Wrong usage of arg\n");
            exit (1);


	}

	if(tflag == 1)
	{
		if(lflag == 0)
			{
			if( (cflag == 1 )|| (uflag == 1) || (tflag == 1) )
				{
				//if(  (strcmp(argv[1],"-t")) || (strcmp(argv[1],"-tc")) || (strcmp(argv[1],"-tu")) )
					mylst(argc, argv, dirs);		
				}
			}
	}
	
	if(lflag == 1 )
	{
		if(Rflag == 1)
		{
			mylslR(argc, argv,dirs);
		}
		else if((Rflag == 0) && (tflag == 0) && (Sflag == 0) && (sflag == 1))
		{
			//printf("\n\n hi  \n\n");
			mylsl(argc, argv, dirs);	
		}
		
		else if(tflag == 1)
		{
		     mylslt(argc, argv, dirs);
		}
		
		else if(Sflag == 1)
		{
			//printf("\n\n hi  \n\n");
			mylslS(argc, argv, dirs);
		}
	
	
	
	}
	
	if(Rflag == 1 )
	{
		if(lflag == 0)
			{
			mylsR(argc, argv, dirs);
			}
	}
	
	if(sflag == 1)
	{
		if(lflag == 0)
		{
			mylss(argc, argv, dirs);
		}
	}
	if(Sflag == 1)
	{
		if(lflag == 0)
		{
			mylsS(argc, argv, dirs);
		}
	}
	
	
	
	
	if(argc == 1)
      		  myls();

	if( ((argc - dirs) == 1)  || (def == 0) )
	{

		while(enumber < argc)	 
		{
     		   	myls2(argv[enumber++]);			 				
		}
	}
return 0;
}








