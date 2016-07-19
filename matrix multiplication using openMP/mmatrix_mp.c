/**********************************************************************************************************************************************

NAME			: matrix.c 

AUTHOR			: THRINAI BATCHU

PROGRAM DESCRIPTION	: This program deals with taking input from .dat file and perform matrix multiplication using openMP

***********************************************************************************************************************************************/
#include <omp.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#define val 1000

 int a[val][val];
 int b[val][val];
 int c[val][val];
 int i, j, n, k, count = 0;
 int num;
 int chunk = 500;


int checking(char **);	
int lchecking(char **);
void *thread(void *); /* the thread */

int checking(char **array)
{
	FILE *fp;
	FILE *fpl;
	FILE *fps;
	fp = fopen(array[1], "r");
	fpl = fopen(array[1], "r");
	fps = fopen(array[1], "r");
	char s;
	int morder;
	fscanf(fp, "%d", &morder);
   for(s= fgetc(fps);s!='\n';s= fgetc(fps)) 
   {
	if(!isdigit(s))
	{
		printf("Invalid entry please enter positive integer without space charecters\n");
		exit(1);
	}
   }
     

       if((s= fgetc(fpl)))
         {
          if(!isdigit(s))
           {
            printf("Invalid matrix order please enter valid matrix order and matrix\n");
            exit(1);
            }
          }


       int linecount = 0, mcount;
	while(1)
	{
		mcount = 0;
		
	    for(s= fgetc(fps);s!='\n';s= fgetc(fps)) 
    	{
			
			if(s == EOF)
			break;
	 		if( !isdigit(s) && s != ' ' && s != '-' )
	  		{
	    		printf("\nInvalid entry at Line: %d it has charecters please enter positive integer values with single space charecters\nNo extra space at EOL\n",linecount+1);
				exit(1);
	  		}
			if(s == ' ')
				mcount++;			
		}
		if(s == EOF)
			break;

		linecount++;
	}
	if (linecount != 2*morder)
	{
		printf("Invalid matrix please check the number of lines\n");
		exit(1);
	}
   fclose(fp);	
return 0;

}



int lchecking(char **array)
{
    FILE *fpl;
	FILE *fps;
	fpl = fopen(array[1], "r");
	fps = fopen(array[1], "r");
	int morder;
    char buffer[10000];
	char *pbuff = NULL;
	char s;
    int rcount = 0;
	long int value;
	
   fscanf(fpl, "%d", &morder);
   for(s= fgetc(fps);s!='\n';s= fgetc(fps)) 
   {
	  if(!isdigit(s))
	    {
	  	  printf("Invalid matrix order please enter positive integer without space charecters\n");
	  	  exit(1);
	    }
   }
while (1) 
 {
    if (!fgets(buffer, sizeof buffer, fps)) 
	      break;
    pbuff = buffer;
   	rcount = 0;
	  
    while (1) 
     {
		if (*pbuff == '\n' || *pbuff == EOF )
		{
			break;	
		}		
		if(rcount > morder)
		{
			printf("Please check the matrix row order it must be without extra or few charecters\n No extra space at EOL\n");
		    exit(1);
		}
	     value = strtol(pbuff, &pbuff, 10);
      rcount++; 
     }
	if(rcount != morder)
    {
      printf("Please check the matrix row order it must be without extra or few charecters\nNo extra space at EOL\n");
        exit(1);
    }
   }
  return 0;
}


int main(int argc, char **argv)
{
    int tid; 
    FILE *file;
    
    if(argc > 2)
	{
		printf("Too many arguments please enter only one path\n");
		exit(1);
	}
	if((file = fopen(argv[1], "r"))==NULL)       /* open a text file for reading */
	{     
		printf("File or Directory doesn't exist\n");
		exit(1); //couldn't open the requested file!
	
	}
    fscanf(file, "%1d", &n);	
    
	num = n*n;
    
    int mcount;
    checking(argv);
	lchecking(argv);
    
 #pragma omp parallel shared (a,b,c,num,chunk) private(tid,i,j,k)
 {   
 void omp_set_num_threads(int num);
 tid = omp_get_thread_num();

	 //Initializing  array "c"
  #pragma omp for schedule (static, chunk)
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
     c[i][j]= 0;
   //Entering the values to array "a"
   #pragma omp for schedule (static, chunk) 
	 for (i = 0; i < n; i++)
	{
        for (j = 0; j < n; j++)
	 {
            //Use lf format specifier, %c is for character
            if (!fscanf(file, "%d", &a[i][j])) 
	    	{
              printf("Invalid input\n");	
	    	  exit(1);
	    	  break; 
            }	 
     }   
	}

  	//Entering the values to array "b"
	#pragma omp for schedule (static, chunk)
    for( i = 0; i<n ; i++)
	{ 
	for(k = 0; k < n; k++)
	{
    	 //Use lf format specifier, %c is for character
            if (!fscanf(file, "%d", &b[i][k]))
       		 {
                printf("Invalid input 2\n");
              	exit(1); 
		        break;
             } 	
	}
    }
    
 #pragma omp for schedule (static, chunk)
  for (i=0; i<n; i++)    
    {
       for(j=0; j<n; j++)       
      for (k=0; k<n; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
 }
   //Print out the resultant matrix
   printf("Resultant matrix using OpenMP is\n");
   for(i = 0; i < n; i++) 
   {
      for(j = 0; j < n; j++) 
	  {
         printf("%d\t", c[i][j]);
      }
      printf("\n");
   }
    
    fclose(file);
    

return 0;
}
