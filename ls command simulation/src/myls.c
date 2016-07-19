

/*
************************************************************************************************************************************************

NAME	: myls.c

AUTHOR 	: THRINAI BATCHU

DESCRIPTION	: 

*************************************************************************************************************************************************/ 



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
#include "../include/myls.h"
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>


int myls()
{ 

	DIR* pd = opendir(".");
	struct dirent *cur1;
	
	printf("\n");
	while (cur1 = readdir(pd)) 
	{
	    if (cur1->d_name[0] != '.') 
		{
	    
		printf("%s    ",cur1->d_name);	
		}        
	}
	printf("\t"); 
	printf("\n");
}

int myls2(char *source) 

{
	DIR *dr;
	struct dirent *cur;
    dr = opendir(source);
     
	if(dr)
	{printf("%s:\n",source); 
	while ((cur = readdir(dr)) != NULL)
        {
	
	  if(cur->d_name[0] != '.')
                {	
			printf("%s    ",cur->d_name);
				}
	
		}
    printf("\n"); 
	}

	else if( access(source, F_OK) != -1)
	{
		printf("%s    ",source);
	}

	else
	{
	printf("%s:\n",source); 
	printf("No such directory or file exists!!!\n");
	}


printf("\n");
}
int myls3(char *source) 

{
		DIR *dr;
		struct dirent *cur;
    	dr = opendir(source);
		struct stat fi; 
	    long int total_size = 0; 		 
		//printf("%s:\n",source);
		size_t sourcelen = strlen(source);	
		char *path = malloc(strlen(source)+1);
		strcpy(path,source);	
		int tot_size = 0;	
	if(dr)
	{printf("\n");
	while ((cur = readdir(dr)) != NULL)
        {
	
	  if(cur->d_name[0] != '.')
                {	
		  			free(path);	
					path = malloc(sourcelen + strlen(cur->d_name) + 2);	
					if(path != NULL)
					strcpy(path,"");
				  	strcat(path,source);
					strcat(path,"/");
					strcat(path,cur->d_name);	
		     		stat(path, &fi);
					//printf("%s    ",cur->d_name);
					printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
  					 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
  			 		 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
 			  		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
  			 		 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
 			  		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
			   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
  			 		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
  				  	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
  			 		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");	
					 printf("\t%d", (int)fi.st_nlink); 
		 
					 struct passwd *pass = getpwuid(fi.st_uid);
					 printf("\t%s",pass->pw_name);
					 struct group * pass2 = getgrgid(fi.st_gid);
					 printf("\t%s",pass2->gr_name); 
					 printf("\t%d",(int)fi.st_size);
				   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
					 int len_c_mtime = strlen(c_mtime) - 1;
					 c_mtime[len_c_mtime] = '\0';		 
  			    	   printf("\t%s", c_mtime);
					 printf("\t%s", cur->d_name);
					 printf("\n"); 
		  			tot_size = tot_size + (int)fi.st_blocks;
	  			}
	
		}
    printf("\n"); 
	printf("total size = %d", tot_size);
		printf("\n");
	}
}



int mylsh()

{


printf("\n");
printf("Default : It will print files in current directory\n");
printf("      h : All the options which myls supports\n");
printf("      s : List file size in blocks\n");
printf("      l : Long list\n");
printf("      R : List subdirectories recursively\n");
printf("      t : Sort by content modification time\n");
printf("      tc: Sort by status modification time\n");
printf("      tu: Sort by access time\n");
printf("      S : Sort by file size in decreasing order\n");

}



int mylss(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
int l = 0,j=0,k=0; 
if(tot_count == 2)
{
 	struct stat fi;
        long int total_size = 0;
        DIR* pd = opendir(".");
        struct dirent *cur;
    printf("\n");
        while (cur = readdir(pd))
        {
	   if (cur->d_name[0] != '.')
                {
          stat(cur->d_name, &fi);
                  printf("%s  ",cur->d_name);
                  printf("%ld  ",(fi.st_blocks/2));
                  total_size = total_size + fi.st_blocks;
                }
        }
        printf("\ntotal_size = %ld \n", (total_size/2));
        printf("\t");
 
    printf("\t");
        printf("\n");

}
else if(dirs){
	int i = 2;
  while(i < tot_count )
     { 
		DIR *dr;
		struct dirent *cur;
		struct stat fi; 
	    long int total_size = 0; 		 
	    dr = opendir(all_paths[current]);
       if(dr)
		{
		printf("%s:\n",all_paths[current]);
		size_t sourcelen = strlen(all_paths[current]);	
		char *path = malloc(strlen(all_paths[current])+1);
		strcpy(path,all_paths[current]);	
		while ((cur = readdir(dr)) != NULL)
	        {

		  if(cur->d_name[0] != '.')
	                {
				free(path);	
				path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(path != NULL)
				strcpy(path,"");
			  	strcat(path,all_paths[current]);
				strcat(path,"/");
				strcat(path,cur->d_name);	
				if(stat(path, &fi) == -1)
	                       { 
	        							}	
				else
				{
					
				printf("%s  ",cur->d_name);
				printf("%ld  ",fi.st_blocks);
				total_size = total_size + fi.st_blocks;
				}
			}
	        }
	        printf("\ntotal_size = %ld \n", total_size);
	
	   }
	  else if( access(all_paths[current], F_OK) != -1)
		{
		  	stat(all_paths[current], &fi);
		  	printf("%d   ",(int)fi.st_blocks);
			printf("%s\n",all_paths[current]);
		}
	   else
	   {printf("%s:\n",all_paths[current]);
		   printf("No such directory found!!!\n");
	   }
 current++; 
	i++; 
 }	
 }		
else
{

        printf("\nNo such directory found\n");

}
}

int mylsl(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
if(tot_count == 2)
{ 
	struct stat fi;
	struct stat * buf;
	struct passwd * pass;
        long int total_size = 0;
        DIR* pd = opendir(".");
        struct dirent *cur;
        printf("\n");
        while (cur = readdir(pd))
        {
	   if (cur->d_name[0] != '.')
                {
          	  stat(cur->d_name, &fi);
		   if(strcmp(all_paths[1],"-ls") == 0)
		   {
			   printf("%d\t",(int)fi.st_blocks);
		   }
         printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
  		 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
   		 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
    	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
		 printf("\t%d", (int)fi.st_nlink); 
		 
		 pass = getpwuid(fi.st_uid);
		 printf("\t%s",pass->pw_name);
		 struct group * pass2 = getgrgid(fi.st_gid);
		 printf("\t%s",pass2->gr_name); 
		 printf("\t%d",(int)fi.st_size);
	   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 int len_c_mtime = strlen(c_mtime) - 1;
		 c_mtime[len_c_mtime] = '\0';		 
         printf("\t%s", c_mtime);
		 printf("\t%s", cur->d_name);
		 printf("\n"); 
		 total_size = total_size + fi.st_blocks;
            }
        
		}
        printf("\ntotal_size = %ld\n", (total_size/2));
     	printf("\t");
        printf("\n");

}
else if(dirs)
{
	int i = 2;
  while(i < tot_count )
     { 
		DIR *dr;
		struct dirent *cur;
		struct stat fi; 
	    long int total_size = 0; 
	    dr = opendir(all_paths[current]);
       if(dr)
		{
		printf("%s:\n",all_paths[current]); 
		size_t sourcelen = strlen(all_paths[current]);	
		char *path = malloc(strlen(all_paths[current])+1);
		strcpy(path,all_paths[current]);	
		while ((cur = readdir(dr)) != NULL)
	        {		
		  if(cur->d_name[0] != '.')
	                {
				free(path);	
				path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(path != NULL)
					strcpy(path,"");
			    strcat(path,all_paths[current]);
				strcat(path,"/");
				strcat(path,cur->d_name);	
				if(stat(path, &fi) == -1)
	                       { 
	              	
							}	
				else
				{
						if(strcmp(all_paths[1],"-ls") == 0)
		   				 {
			   				printf("%d\t",(int)fi.st_blocks);
		 				  }
					    printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
       			        printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
                 		printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
                		printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
                 		printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
                 		printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
                 		printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
                 		printf( (fi.st_mode & S_IROTH) ? "r" : "-");
                 		printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
                 		printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
                 		printf("\t%d", (int)fi.st_nlink);
                 		struct passwd * pass = getpwuid(fi.st_uid);
                 		printf("\t%s",pass->pw_name);
                 		struct group * pass2 = getgrgid(fi.st_gid);
                 		printf("\t%s",pass2->gr_name);
                 		printf("\t%d",(int)fi.st_size);
                  		char *c_mtime = asctime(localtime((&fi.st_mtime)));
                 		int len_c_mtime = strlen(c_mtime) - 1;
                 		c_mtime[len_c_mtime] = '\0';
                 		printf("\t%s", c_mtime);
                 		printf("\t%s", cur->d_name);
				total_size = total_size + fi.st_blocks;
				printf("\n");	
				}
			}
	        }
	        printf("\ntotal_size = %ld \n", total_size);
			free(path);
	   }
	  else if( access(all_paths[current], F_OK) != -1)
		{
		  
					 stat(all_paths[current], &fi);
					 printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
  		 			 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
   		 			 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
  			 		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
   					 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
 			  		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
  			 		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   					 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
  				  	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
			   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
					 printf("   %d", (int)fi.st_nlink); 
		 
				 struct passwd *pass = getpwuid(fi.st_uid);
				 printf("   %s",pass->pw_name);
				 struct group * pass2 = getgrgid(fi.st_gid);		
				 printf("   %s",pass2->gr_name); 
				 printf("   %d",(int)fi.st_size);
	   	 		char *c_mtime = asctime(localtime((&fi.st_mtime)));
				 int len_c_mtime = strlen(c_mtime) - 1;
				 c_mtime[len_c_mtime] = '\0';		 
         		printf("   %s", c_mtime);
		 		printf("   %s", cur->d_name);
				printf("   %s",all_paths[current]);
				 printf("\n"); 				
	  }
	   else
	   {
		   printf("%s:\n",all_paths[current]);
		   printf("No such directory found!!!\n");
	   }
 current++; 
	i++; 
 }	
 }	

else
{

        printf("\nNo such directory found\n");

}
}

int mylsR(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
	
if(tot_count == 2)
{
	struct stat fi;
	char cwd[1024];
    long int total_size = 0;
    DIR* pd = opendir(".");
	struct dirent *cur;
	struct dirent *cur1;
	
	printf("\n");
	printf(".:\n");
	while (cur = readdir(pd))
		{
	   	if (cur->d_name[0] != '.')
           {
        	printf("%s  ",cur->d_name);
			}
		}
	printf("\n");        
	if (getcwd(cwd, sizeof(cwd)) != NULL)
       mylsR_rec(cwd);
    else
       perror("getcwd() error");
}
else if(dirs)
{
int i = 2;
  while(i < tot_count )
     { 
		DIR *dr;
	  	dr = opendir(all_paths[current]);
		if(dr)
			{
				myls2(all_paths[current]);
				mylsR_rec2(all_paths[current], all_paths);
			}
	  	else if( access(all_paths[current], F_OK) != -1)
			{
					printf("\n%s\n",all_paths[current]);	
			}
	  	else
		{
			printf("\n%s:\n No Such directory or file exists!!!\n",all_paths[current]); 
		}
  		current++;
	  	i++;
  		}
}
	
}
	  
int mylsR_rec(char *path)
{
		DIR *dr;
		struct dirent *cur;
		struct stat fi;  
	    dr = opendir(path);
       if(dr)
		{
		size_t sourcelen = strlen(path);	
		char *cur_path = malloc(strlen(path)+1);	
		while ((cur = readdir(dr)) != NULL)
	        {
			  if(cur->d_name[0] != '.')
                {
				strcpy(cur_path,path);
				free(cur_path);	
				cur_path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(cur_path != NULL)
				strcpy(cur_path,"");
			    strcat(cur_path,path);
				strcat(cur_path,"/");
				strcat(cur_path,cur->d_name);	
				stat(cur_path, &fi);
	           
				if(S_ISDIR(fi.st_mode)) 
					{
					 	printf("./%s\n",cur->d_name);
						myls3(cur_path);
						mylsR_rec(cur_path);
					}	
				} 	
			}
		   printf("\n");
	   	free(cur_path);
	    }
}


int mylsR_rec2(char *path, char **all_paths)
{
		DIR *dr;
		struct dirent *cur;
		struct stat fi;  
	    dr = opendir(path);
		int sourcelen = strlen(path);	
		char *cur_path = malloc(strlen(path)+1);
		strcpy(cur_path,path);
		while ((cur = readdir(dr)) != NULL)
	        {
			  if(cur->d_name[0] != '.')
                {
				
				free(cur_path);	
				cur_path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(cur_path != NULL)
				strcpy(cur_path,"");
			    strcat(cur_path,path);
				strcat(cur_path,"/");	
				strcat(cur_path,cur->d_name);	
				stat(cur_path, &fi);
	           
				if(S_ISDIR(fi.st_mode)) 
					{
					 	printf("\n%s\n",cur_path);
			
							myls3(cur_path);
						    mylsR_rec2(cur_path, all_paths);
			
					}	
				  else
				  {
					//  printf("\nhi\n");
				  }
				} 	
			}
}

int mylslR(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
	
if(tot_count == 2)
{
	struct stat fi;
	char cwd[1024];
    long int total_size = 0;
    DIR* pd = opendir(".");
	struct dirent *cur;
	struct dirent *cur1;
	while (cur = readdir(pd))
		{
	   	if (cur->d_name[0] != '.')
           {
        	
			
		  stat(cur->d_name, &fi);
         printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
  		 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
   		 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
    	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
		 printf("\t%d", (int)fi.st_nlink); 
		 
		 struct passwd *pass = getpwuid(fi.st_uid);
		 printf("\t%s",pass->pw_name);
		 struct group * pass2 = getgrgid(fi.st_gid);
		 printf("\t%s",pass2->gr_name); 
		 printf("\t%d",(int)fi.st_size);
	   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 int len_c_mtime = strlen(c_mtime) - 1;
		 c_mtime[len_c_mtime] = '\0';		 
         printf("\t%s", c_mtime);
		 printf("\t%s", cur->d_name);
		 printf("\n"); 
		 total_size = total_size + fi.st_blocks;
		 //printf("%s  ",cur->d_name);
			}
		}
	printf("\n");        
	if (getcwd(cwd, sizeof(cwd)) != NULL)
       mylslR_rec(cwd);
    else
       perror("getcwd() error");
}
else if(dirs)
{
	struct stat fi;
    long int total_size = 0;
 	struct dirent *cur;
    DIR *dr; 
	char *cur_path = malloc(strlen(all_paths[current])+1);
	int source_len = strlen(all_paths[current]);
    int i = 2;
	strcpy(cur_path,"path");
	
  while(i < tot_count)
     { 
	 
	  	dr = opendir(all_paths[current]);  			
	  if(dr)
			{		  
		  printf("%s\n",all_paths[current]);
		while ((cur = readdir(dr)) != NULL)
		{
			if(cur->d_name[0] != '.')
                {
			free(cur_path);	
	  			int sourcelen = strlen(all_paths[current]);
				cur_path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(cur_path != NULL)
				strcpy(cur_path,"");
			    strcat(cur_path,all_paths[current]);
				strcat(cur_path,"/");
				strcat(cur_path,cur->d_name);	
				stat(cur_path, &fi);

		 printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
  		 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
   		 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
    	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
		 printf("\t%d", (int)fi.st_nlink); 
		 
		 struct passwd *pass = getpwuid(fi.st_uid);
		 printf("\t%s",pass->pw_name);
		 struct group * pass2 = getgrgid(fi.st_gid);
		 printf("\t%s",pass2->gr_name); 
		 printf("\t%d",(int)fi.st_size);
	   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 int len_c_mtime = strlen(c_mtime) - 1;
		 c_mtime[len_c_mtime] = '\0';		 
         printf("\t%s", c_mtime);
		 printf("\t%s", cur->d_name);
		 printf("\n"); 
		 total_size = total_size + fi.st_blocks;
			}
		}
		  printf("total size = %ld\n", total_size); 
		 
		 // myls3(all_paths[current]);
		 mylslR_rec2(all_paths[current], all_paths);  
	  }
	  	else if( access(all_paths[current], F_OK) != -1)
			{
			
								stat(all_paths[current], &fi);

					 printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
  		 			 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
   		 			printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
  			 		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
   					 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
    	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
		 printf("   %d", (int)fi.st_nlink); 
		 
		 struct passwd *pass = getpwuid(fi.st_uid);
		 printf("   %s",pass->pw_name);
		 struct group * pass2 = getgrgid(fi.st_gid);
		 printf("   %s",pass2->gr_name); 
		 printf("   %d",(int)fi.st_size);
	   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 int len_c_mtime = strlen(c_mtime) - 1;
		 c_mtime[len_c_mtime] = '\0';		 
         printf("   %s", c_mtime);
		 printf("   %s", cur->d_name);
		printf("   %s",all_paths[current]);
		 printf("\n"); 					
			}
	  	else
		{
			printf("%s:\nNo Such directory or file exists!!!\n",all_paths[current]); 
		}
  		current++;
	  	i++;
  		}
}
	
}
	  
int mylslR_rec(char *path)
{
		DIR *dr;
		struct dirent *cur;
		struct stat fi;  
	    dr = opendir(path);
       if(dr)
		{
		size_t sourcelen = strlen(path);	
		char *cur_path = malloc(strlen(path)+1);	
		while ((cur = readdir(dr)) != NULL)
	        {
			  if(cur->d_name[0] != '.')
                {
				strcpy(cur_path,path);
				free(cur_path);	
				cur_path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(cur_path != NULL)
				strcpy(cur_path,"");
			    strcat(cur_path,path);
				strcat(cur_path,"/");
				strcat(cur_path,cur->d_name);	
				stat(cur_path, &fi);
	           
				if(S_ISDIR(fi.st_mode)) 
					{
					 	printf("./%s\n",cur->d_name);
						myls3(cur_path);
						mylsR_rec(cur_path);
					}	
				} 	
			}
		   printf("\n");
	   	free(cur_path);
	    }
}


int mylslR_rec2(char *path, char **all_paths)
{
		DIR *dr;
		struct dirent *cur;
		struct stat fi;  
	    dr = opendir(path);
		int sourcelen = strlen(path);	
		char *cur_path = malloc(strlen(path)+1);
		strcpy(cur_path,path);
		while ((cur = readdir(dr)) != NULL)
	        {
			  if(cur->d_name[0] != '.')
                {
				
				free(cur_path);	
				cur_path = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(cur_path != NULL)
				strcpy(cur_path,"");
			    strcat(cur_path,path);
				strcat(cur_path,"/");	
				strcat(cur_path,cur->d_name);	
				stat(cur_path, &fi);
	           
				if(S_ISDIR(fi.st_mode)) 
					{
					 	printf("\n%s\n",cur_path);
			
							myls3(cur_path);
						    mylsR_rec2(cur_path, all_paths);
			
					}	
				  else
				  {
					//  printf("\nhi\n");
				  }
				} 	
			}
}
	



int mylsS(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
	
if(tot_count == 2)
{
	struct stat fi;
	char cwd[1024];
        long int total_size = 0;
        DIR* pd = opendir(".");
	struct dirent *cur;
	struct node *start = NULL;
	char *path1 = malloc(strlen(all_paths[0])+1);
	int sourcelen;	
	strcpy(path1,"");
	printf("\n");
	printf(".:\n");
	if(pd)
	{
	getcwd(cwd, sizeof(cwd));	
	sourcelen = strlen(cwd);	
	while (cur = readdir(pd))
		{
	   	if (cur->d_name[0] != '.')
			{
           			free(path1);	
				path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(path1 != NULL)
				strcpy(path1,"");
			  	strcat(path1,cwd);
				strcat(path1,"/");
				strcat(path1,cur->d_name);	
				if(stat(path1, &fi) == -1)
               	                { 
	              		//	printf("error \n");
				}	
				else
				{
					
				insertAtTheBegin(&start, cur->d_name, (long)fi.st_size);
				bubbleSort(start);				
				
				}
			}		
		}
	        

	}
printList(start);
printf("\n");
}
else if(dirs)
{
int i = 2;
  while(i < tot_count )
     { 
		DIR *dr;
	  	dr = opendir(all_paths[current]);
		struct stat fi;
		char *path1 = malloc(strlen(all_paths[current])+1);
		struct dirent *cur;
		struct node *start = NULL;
		int sourcelen = strlen(all_paths[current]);
	  	//printf("\n%s:\n ", all_paths[current]);
		if(dr)
			{
			//printf("entered if(dr) \n");
			   {	
				while (cur = readdir(dr))
				{
				   	if (cur->d_name[0] != '.')
					{
    			       	free(path1);	
						path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
						if(path1 != NULL)
						strcpy(path1,"");
					  	strcat(path1,all_paths[current]);
						strcat(path1,"/");
						strcat(path1,cur->d_name);	
						if(stat(path1, &fi) == -1)
		               	                { 
			              		
										}	
						else
						{
							
						insertAtTheBegin(&start, cur->d_name, (long)fi.st_size);
						bubbleSort(start);				
						
						}
					}		
				}	        
			}
    	    	    }
	  	else if( access(all_paths[current], F_OK) != -1)
			{
				printf("%s\n    ",all_paths[current]);		
			}
		else
			{
				
				printf("\n%s:\nNo such file or directory exists !!!\n ",all_paths[current]);
			}
  		current++;
	  	i++;
  		printList(start);
		printf("\n");
		}
}
	
}
	  


void insertAtTheBegin(struct node **start_ref, char *path, long int size)
{

    struct node *ptr1 = (struct node*)malloc(sizeof(struct node));
    ptr1->path = path;
   	ptr1->size = size;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}
/* Function to print nodes in a given linked list */

void printList(struct node *start)
{
    struct node *temp = start;
   
    while (temp!=NULL)
    {
        //printf("%ld   ", temp->size);
	printf("%s   ", temp->path);
        temp = temp->next;
   
     }
}

/* Bubble sort the given linked lsit */
void bubbleSort(struct node *start)
{
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;
 
    /* Checking for empty list */
    if (ptr1 == NULL)
        return;
 
    do
    {
        swapped = 0;
        ptr1 = start;
 
        while (ptr1->next != lptr)
        {
            if (ptr1->size < ptr1->next->size )
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b)
{
    int temp = a->size;
    a->size = b->size;
    b->size = temp;

   char *path = a->path;
   a->path = b->path;
   b->path = path;

   time_t ti = a-> time;
   a->time = b->time;
   b->time = ti;

	char *full = a->full_path;
	a->full_path = b->full_path;
	b->full_path = full;


}


void insertAtTheBegin1(struct node **start_ref, char *path, time_t time)
{
    struct node *ptr1 = (struct node*)malloc(sizeof(struct node));
    ptr1->path = path;
    ptr1->time = time;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}

void bubbleSortt(struct node *start)
{
    int swapped =1, i;
    struct node *ptr1;
    struct node *lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
        {
            if (ptr1->time < ptr1->next->time)
            { 
				swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

int mylst(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
if(tot_count == 2)
{
	struct stat fi;
	char cwd[1024];
    long int total_size = 0;
    DIR* pd = opendir(".");
	struct dirent *cur;
	struct node *start = NULL;
	struct tm     *tm;	
	char *path1 = malloc(strlen(all_paths[0])+1);
	int sourcelen;
	char datestring[256];	
	strcpy(path1,"");
	printf("\n");
	printf(".:\n");
	if(pd)
	{
	getcwd(cwd, sizeof(cwd));	
	sourcelen = strlen(cwd);	
	while (cur = readdir(pd))
		{
	   	if (cur->d_name[0] != '.')
			{
           		free(path1);	
				path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(path1 != NULL)
				strcpy(path1,"");
			  	strcat(path1,cwd);
				strcat(path1,"/");
				strcat(path1,cur->d_name);	
				if(stat(path1, &fi) == -1)
               	                { 
								}	
				else
				{
				tm = localtime(&fi.st_mtime);
				strftime(datestring, sizeof(datestring), "%Y.%m.%d %T", tm);
				if(strcmp(all_paths[1],"-t") == 0)
				{			
					insertAtTheBegin1(&start, cur->d_name,fi.st_mtime);	
					bubbleSortt(start);
				}
				else if(strcmp(all_paths[1],"-tc") == 0)
				{
					insertAtTheBegin1(&start, cur->d_name,fi.st_ctime);
					bubbleSortt(start);
				}
				else if(strcmp(all_paths[1],"-tu") == 0)
				{
				
					insertAtTheBegin1(&start, cur->d_name,fi.st_atime);								
					bubbleSortt(start);				
				
				}
			}		
		}
	        

	}
printList(start);
printf("\n");
}
}
else if(dirs)
{
//	printf("\n Entered mylst if \n ");

int i = 2;
  while(i < tot_count )
     { 
		DIR *dr;
	  	dr = opendir(all_paths[current]);
		struct stat fi;
		char *path1 = malloc(strlen(all_paths[current])+1);
		struct dirent *cur;
		struct tm *tm;
		char datestring[256];
		struct node *start = NULL;
		int sourcelen = strlen(all_paths[current]);
		if(dr)
			{
			   {	
				while (cur = readdir(dr))
				{
				   	if (cur->d_name[0] != '.')
					{
					
    			       			free(path1);	
						path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
				
						if(path1 != NULL)
						strcpy(path1,"");
					  	strcat(path1,all_paths[current]);
						strcat(path1,"/");
						strcat(path1,cur->d_name);	
						if(stat(path1, &fi) == -1)
		               	                { 
			              		//	printf("error \n");
						}	
						else
						{
						tm = localtime(&fi.st_mtime);
						strftime(datestring, sizeof(datestring), "%Y.%m.%d %T", tm);
	//			         printf("%s:\n",all_paths[1]); 
							
						if(strcmp(all_paths[1],"-t") == 0)
						{				
						insertAtTheBegin1(&start, cur->d_name,fi.st_mtime);
						}
						else if(strcmp(all_paths[1],"-tc") == 0)
						{
							insertAtTheBegin1(&start, cur->d_name,fi.st_ctime);
						}
						else if(strcmp(all_paths[1],"-tu") == 0)
						{
							insertAtTheBegin1(&start, cur->d_name,fi.st_atime);
						}								
						bubbleSortt(start);
						
						}
					}		
				}	        
			}
    	    	    }
	  	else if( access(all_paths[current], F_OK) != -1)
			{
				printf("%s\n    ",all_paths[current]);		
			}
		else
			{
				printf("%s:\nNo such file or directory exists !!!\n ", all_paths[current]);
			}
  		current++;
	  	i++;
  		printList(start);
		printf("\n");
		}
}
	
}
	


int mylslt(int tot_count, char **all_paths, int dirs)
{
	
int current = 2;
if(tot_count == 2)
{
	struct stat fi;
	char cwd[1024];
    long int total_size = 0;
    DIR* pd = opendir(".");
	struct dirent *cur;
	struct node *start = NULL;
	struct tm     *tm;	
	char *path1 = malloc(strlen(all_paths[0])+1);
	int sourcelen;
	char datestring[256];	
	strcpy(path1,"");
	char full_path[1000];
	printf("\n");
	if(pd)
	{
		//printf("\nHello\n");
	getcwd(cwd, sizeof(cwd));	
	sourcelen = strlen(cwd);
		//printf("\nHello 2 \n");
	while (cur = readdir(pd))
		{
		
	   	if (cur->d_name[0] != '.')
			{
			
           		free(path1);	
				path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(path1 != NULL)
				strcpy(path1,"");
			  	strcat(path1,cwd);
				strcat(path1,"/");
				strcat(path1,cur->d_name);	
				if(stat(path1, &fi) == -1)
               	                { 
								}	
				else
				{
				tm = localtime(&fi.st_mtime);
				strftime(datestring, sizeof(datestring), "%Y.%m.%d %T", tm);
				if(strcmp(all_paths[1],"-lt") == 0)
				{	
					strcpy(full_path,path1);
					
					insertAtTheBeginlt(&start, cur->d_name, cwd, fi.st_mtime);		
				//	printf("\nFull_path %s:\n",full_path); 
					bubbleSortt(start);
				}
			}		
		}
	        

	}
printListlt(start);
printf("\n");
}
}	
	
else if(dirs)
{
	int i = 2;
while (i < tot_count)
{
	struct stat fi;	
    long int total_size = 0;
    DIR* pd = opendir(all_paths[current]);
	struct dirent *cur;
	struct node *start = NULL;
	struct tm     *tm;	
	char *path1 = malloc(strlen(all_paths[2])+1);
	int sourcelen;
	char datestring[256];	
	strcpy(path1,all_paths[current]);
	char full_path[1000];
	printf("\n");
	if(pd)
	{
	while (cur = readdir(pd))
		{
		
	   	if (cur->d_name[0] != '.')
			{
			
           		free(path1);	
				path1 = malloc(sourcelen + strlen(all_paths[current]) + 2);	
				if(path1 != NULL)
				strcpy(path1,"");
			  	strcat(path1,all_paths[current]);
				strcat(path1,"/");
				strcat(path1,cur->d_name);	
				if(stat(path1, &fi) == -1)
               	                { 
								}	
				else
				{
				tm = localtime(&fi.st_mtime);
				strftime(datestring, sizeof(datestring), "%Y.%m.%d %T", tm);
				if(strcmp(all_paths[1],"-lt") == 0)
					{	
						strcpy(full_path,path1);		
						insertAtTheBeginlt(&start, cur->d_name, all_paths[current], fi.st_mtime);		
						//printf("\nFull_path %s:\n",full_path); 
						bubbleSortt(start);
					}
				}		
			}
	        

		}
		printListlt(start);
		printf("\n");
	}
	else if( access(all_paths[current], F_OK) != -1)
	{		
		 stat(all_paths[current],&fi);
		 printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
		 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
		 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
  		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
 		 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
    	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
		 printf("\t%d\t", (int)fi.st_nlink); 
		 struct passwd *pass = getpwuid(fi.st_uid);
		 printf("%s\t",pass->pw_name);
		 struct group * pass2 = getgrgid(fi.st_gid);
		 printf("%s\t",pass2->gr_name); 
		 printf("%d\t",(int)fi.st_size);
	   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 int len_c_mtime = strlen(c_mtime) - 1;
		 c_mtime[len_c_mtime] = '\0';		 
         printf("%s\t", c_mtime);		
		 printf("%s\t\n",all_paths[current]);		
		 
	}
	else
	{
		printf("%s:\nNo such file or directory found !!! \n",all_paths[current]);
	}
current++;
	i++;
	
}
}

}
void insertAtTheBeginlt(struct node **start_ref, char *path,char *full_path, time_t time)
{
    struct node *ptr1 = (struct node*)malloc(sizeof(struct node));
    ptr1->path = path;
	//printf("\nFile name %s:\n",path);
	ptr1->full_path = full_path;
    //printf("\nFull_path %s:\n",full_path);
	ptr1->time = time;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}

void printListlt(struct node *start)
{
    struct node *temp = start;
    struct stat fi;
	int tot_size = 0;
	char *path1 = malloc(*(temp->full_path)+10);
	//printf("\nFull_path %s:\n",temp->full_path);
    while (temp!=NULL)
    {
		strcpy(path1,"");
		strcat(path1,temp->full_path);
		strcat(path1,"/");
		strcat(path1,temp->path);
		//printf("\npath1 is %s:\n",path1);
		stat(path1,&fi);

		 printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
		 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
		 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
  		 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
 		 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   		 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
   		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
    	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   		 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");
		 printf("\t%d\t", (int)fi.st_nlink); 
		 
		 struct passwd *pass = getpwuid(fi.st_uid);
		 printf("%s\t",pass->pw_name);
		 struct group * pass2 = getgrgid(fi.st_gid);
		 printf("%s\t",pass2->gr_name); 
		 printf("%d\t",(int)fi.st_size);
	   	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 int len_c_mtime = strlen(c_mtime) - 1;
		 c_mtime[len_c_mtime] = '\0';		 
         printf("%s\t", c_mtime);		
   	     printf("%s\t", temp->path);
        temp = temp->next;
		printf("\n");
   		tot_size = tot_size +(int)fi.st_blocks;
     }
	printf("\ntotal size = %d\n", tot_size);
}
	  


int mylslS(int tot_count, char **all_paths, int dirs) 

{
int current = 2;
	
if(tot_count == 2)
{
	struct stat fi;
	char cwd[1024];
        long int total_size = 0;
        DIR* pd = opendir(".");
	struct dirent *cur;
	struct node *start = NULL;
	char *path1 = malloc(strlen(all_paths[0])+1);
	int sourcelen;	
	strcpy(path1,"");
	printf("\n");
	printf(".:\n");
	if(pd)
	{
	getcwd(cwd, sizeof(cwd));	
	sourcelen = strlen(cwd);	
	while (cur = readdir(pd))
		{
	   	if (cur->d_name[0] != '.')
			{
           	    free(path1);	
				path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
				if(path1 != NULL)
				strcpy(path1,"");
			  	strcat(path1,cwd);
				strcat(path1,"/");
				strcat(path1,cur->d_name);	
				if(stat(path1, &fi) == -1)          
				{ 
	              		//	printf("error \n");
				}	
				else
				{
					
				insertAtTheBeginlS(&start, cur->d_name, cwd, (long)fi.st_size);
				bubbleSortlS(start);				
				
				}
			}		
		}
	        

	}
printListlt(start);
printf("\n");
}
else if(dirs)
{
int i = 2;
  while(i < tot_count )
     { 
		DIR *dr;
	  	dr = opendir(all_paths[current]);
		struct stat fi;
		char *path1 = malloc(strlen(all_paths[current])+1);
		struct dirent *cur;
		struct node *start = NULL;
		int sourcelen = strlen(all_paths[current]);
	  	//printf("\n%s:\n ", all_paths[current]);
		if(dr)
			{
			//printf("entered if(dr) \n");
			   	
				while (cur = readdir(dr))
				{
				   	if (cur->d_name[0] != '.')
					{
    			       	free(path1);	
						path1 = malloc(sourcelen + strlen(cur->d_name) + 2);	
						if(path1 != NULL)
						strcpy(path1,"");
					  	strcat(path1,all_paths[current]);
						strcat(path1,"/");
						strcat(path1,cur->d_name);	
						if(stat(path1, &fi) == -1)
		               	                { 
			              		
										}	
						else
						{
							
						insertAtTheBeginlS(&start, cur->d_name, all_paths[current], (long)fi.st_size);
						bubbleSortlS(start);				
						
						}
					}		
				}	        
		printListlt(start);	
    	  }
	  	else if( access(all_paths[current], F_OK) != -1)
			{
				stat(all_paths[current],&fi);
					
				 printf( (S_ISDIR(fi.st_mode)) ? "d" : "-");
				 printf( (fi.st_mode & S_IRUSR) ? "r" : "-");
				 printf( (fi.st_mode & S_IWUSR) ? "w" : "-");
  				 printf( (fi.st_mode & S_IXUSR) ? "x" : "-");
 				 printf( (fi.st_mode & S_IRGRP) ? "r" : "-");
   				 printf( (fi.st_mode & S_IWGRP) ? "w" : "-");
   				 printf( (fi.st_mode & S_IXGRP) ? "x" : "-");
  		 		 printf( (fi.st_mode & S_IROTH) ? "r" : "-");
   			 	 printf( (fi.st_mode & S_IWOTH) ? "w" : "-");
   				 printf( (fi.st_mode & S_IXOTH) ? "x" : "-");	
				 printf("\t%d\t", (int)fi.st_nlink); 
		 
				 struct passwd *pass = getpwuid(fi.st_uid);
				 printf("%s\t",pass->pw_name);	
				 struct group * pass2 = getgrgid(fi.st_gid);
				 printf("%s\t",pass2->gr_name); 
				 printf("%d\t",(int)fi.st_size);
	 		  	 char *c_mtime = asctime(localtime((&fi.st_mtime)));
		 		int len_c_mtime = strlen(c_mtime) - 1;
				 c_mtime[len_c_mtime] = '\0';		 
    		     printf("%s\t", c_mtime);		
				printf("%s\n    ",all_paths[current]);		
			}
		else
			{
				printf("\n%s:\nNo such file or directory exists !!!\n ",all_paths[current]);
			}

	    current++;
	  	i++;
  		printf("\n");
		}


}
	
}
	  
void insertAtTheBeginlS(struct node **start_ref, char *path,char *full_path, long int size)
{
    struct node *ptr1 = (struct node*)malloc(sizeof(struct node));
    ptr1->path = path;
	ptr1->full_path = full_path;
	ptr1->size = size;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}


void bubbleSortlS(struct node *start)
{
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = start;
 
        while (ptr1->next != lptr)
        {
	            if (ptr1->size < ptr1->next->size )
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
