/**********************************************************************************************************************************************

NAME			: matrix.c 

AUTHOR			: THRINAI BATCHU

PROGRAM DESCRIPTION	: This program deals with taking input from .dat file and passes the corresponding parametrers to threads

***********************************************************************************************************************************************/
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#define val 1000
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

struct node 
{
   int i; /* row */
   int j; /* column */
};

int a[val][val];
int b[val][val];
int c[val][val];
int checkcount,q, i, j, n, k, z = 1, check,value;

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
	if(!fscanf(fp, "%d", &morder))
	{
		printf("please the matrix order\n");
		exit(1);
	}
	
	       if((s= fgetc(fpl)))
         {
          if(!isdigit(s))
           {
            printf("Invalid matrix order please enter valid matrix order and matrix\n");
            exit(1);
            }
          }


	 for(s= fgetc(fps);s!='\n';s= fgetc(fps)) 
   {
	if(!isdigit(s))
	{
		printf("Invalid entry please enter positive integer without space charecters\n");
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
	    		printf("\nInvalid entry at Line: %d it has charecters please enter positive integer values with single space charecters\n",linecount+1);
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
    errno = 0;
    FILE *fpl;
	FILE *fps;
	fpl = fopen(array[1], "r");
	fps = fopen(array[1], "r");
	int morder;
	 char buffer[10000];
	char *pbuff = NULL;
	char s;
  int rcount = 0;
  fscanf(fpl, "%d", &morder);
   for(s= fgetc(fps);s!='\n';s= fgetc(fps)) 
   {
	  if(!isdigit(s))
	    {
	  	  printf("Invalid matrix order please enter positive integer without space charecters\n");
	  	  exit(1);
	    }
   }
	long int value;
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

int  main(int argc, char **argv)
{
    FILE *file;
    //struct resultcount result;
	int count = 0,mcount,lcount;
	int *mlcount;

	if(argc > 2)
	{
		printf("Too many arguments please enter only one path\n");
		exit(1);
	}

	if((file = fopen(argv[z], "r"))==NULL)       /* open a text file for reading */
	{     
		printf("File or Directory doesn't exist\n");
		exit(1); //couldn't open the requested file!
	
	} 
		checking(argv);
		lchecking(argv);
	int check = fscanf(file, "%d", &n);
     	if(check == 0 ) 
		{
			printf("Invalid input please enter positive integer value\n"); 
		    return 0;
		}
	    if(n <= 0) 
		{
			printf("Invalid input matrix order must be greater than 0 value\n"); 
		    return 0;
		}

	//Entering the values to array "a"
    for (i = 0; i < n; i++)
	{
        for (j = 0; j < n; j++)
	     {		
            //Use lf format specifier, %c is for character
            if (!fscanf(file, "%d", &a[i][j])) 
	    	{
              printf("Invalid input at first matrix\n");	
	    	  exit(1); 
            }		
         }   
	}
	//Entering the values to array "b"
    for( i = 0; i<n ; i++)
	{ 
	for(k = 0; k < n; k++)
	  {
    	 //Use lf format specifier, %c is for character
            if (!fscanf(file, "%d", &b[i][k]))
       		 {
                printf("Invalid input at second matrix\n");
              	exit(1); 		       
             } 
	  }
    }
	int ch;	
    printf("Resultant matrix is\n\n");
    pthread_t tid[n*n];       //Thread ID
	for(i = 0; i < n; i++) 
   {
      for(j = 0; j < n; j++) 
	  {
         //Assign a row and column for each thread
         struct node *data = (struct node *) malloc(sizeof(struct node));
         data->i = i;
         data->j = j;
         /* Now create the thread passing it data as a parameter */ 
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
         pthread_create(&tid[count],&attr,thread,data);
	     count++;
      }
   }
	
	for( i = 0; i< n*n ; i++)
	{
		//Make sure the parent waits for all thread to complete
         pthread_join(tid[i], NULL);
	}
   //Print out the resultant matrix
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


//The thread will begin control in this function
void *thread(void *tid) 
{
   struct node *data = tid; // the structure that holds our data
   int l, sum = 0; //the counter and sum

   //Row multiplied by column
   for(l = 0; l< n; l++)
   {
      sum += a[data->i][l] * b[l][data->j];
       
   }
   //assign the sum to its coordinate
   c[data->i][data->j] = sum;

   //Exit the thread
   pthread_exit(0);
}
