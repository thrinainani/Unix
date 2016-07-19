/*
************************************************************************************************************************************************

NAME		: myls.h
AUTHOR		: THRINAI BATCHU
DESCRIPTION	:

*************************************************************************************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>

/* strucre for a node */
struct node
{
    time_t time;
    long int size;
    char *path;
	char *full_path;
    struct node *next;
};



int myls();

int mylsh();

int mylss(int tot_size, char **all_paths, int dirs); 

int myls2(char *);

int mylss2();

int mylslR(int, char **, int);

int myls3(char *);

int mylss(int , char **, int ); 

int mylsl(int , char **, int );

int mylsR(int , char **, int );

int mylsR_rec(char *);

int mylslR_rec2(char *, char **);
	
int mylsS(int , char **, int );	

int mylst(int , char **, int );

int mylslt(int , char **, int );

int mylslS(int , char **, int );



/* Function to insert a node at the begining of a linked lsit */
void insertAtTheBegin(struct node **, char *, long int );
 
/* Function to bubble sort the given linked lsit */
void bubbleSort(struct node *);
 
/* Function to swap data of two nodes a and b*/
void swap(struct node *, struct node *);
 
/* Function to print nodes in a given linked list */
void printList(struct node *);

void insertAtTheBegin1(struct node **, char *, time_t );

void insertAtTheBeginlt(struct node **, char *,char *, time_t);


void insertAtTheBeginlS(struct node **, char *,char *, long int);


void printListlt(struct node *);


void bubbleSortlS(struct node *);
