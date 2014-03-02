#include "mem.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

typedef struct freelist
{
int size;
struct freelist * next;
}list;


int globalDebug;
list * Head=NULL;




int Mem_Init(int sizeOfRegion,int debug)
{
globalDebug=debug;
int size;
float remainder;
int multiple=getpagesize();
remainder=sizeOfRegion % multiple;

	if ( remainder==0.0f )
	  {size=sizeOfRegion;}

	else
 	  {size=sizeOfRegion+multiple-remainder;}


int fd =open("/dev/zero",O_RDWR);
list *ptr =mmap(NULL,size, PROT_READ | PROT_WRITE,MAP_PRIVATE,fd,0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}


ptr->size=size;
ptr->next=NULL;

Head = ptr;

}

void *Mem_Alloc(int size)
{
void * allocate;
void * temp;
int sizeAlloc;
int remainder;
remainder=size % 4;

	if ( remainder==0.0f )
	  {sizeAlloc=size;}

	else
 	  {sizeAlloc=size+4-remainder;}



		list * traverse=Head;
		list * prev =Head;	
		int i=0;
		while(traverse!=NULL)
		{
			
			if((traverse->size) >= (sizeAlloc + sizeof(list)) )
				{
					if(i==0)
					{
						if(traverse->size == (sizeAlloc+ sizeof(list)))
						{
							Head= traverse->next;	
						}
						
						else
						{
							list * newHead=Head;
							
							Head = (void*)Head + sizeAlloc + sizeof(list);		
							Head->size = (newHead-> size)-sizeAlloc- sizeof(list);
							Head->next=newHead->next;
				                        newHead->size = sizeAlloc;
							allocate=(void *)newHead + sizeof(list);
						}
						
			
					}					


					else
					{
						
					}

	
					
					break;
				
				}
			traverse = traverse->next; 
			i++;
		}

		if(traverse==NULL)
		{perror("No space");
		return NULL;
		}
		else
		{
			//printf("allocate %p\n",allocate);
			return  ( allocate );
		}


}

int Mem_Free(void *ptr)
{
//printf("free %p \n",(void*)ptr);

//printf("Head size  %d \n", Head->size);

list * header = (void *) ptr - sizeof(list);
list * traverse=Head;

printf("header size  %d \n", header->size);
while(traverse!=NULL)
{
	if (traverse->next==NULL)
	{
		traverse->next=header;
		traverse->next->next=NULL;
		
	}

traverse=traverse->next;
}

//COALACE
list * lhead=Head;
list *prev_lhead=Head;
int i=0;
int service=0;
while(lhead!=NULL)
{
list * trav=Head;
list * prev_trav=Head;
int sizetemp = lhead->size;

	int j=0;
	while(trav!=NULL)
	{   list * temp =lhead;

		if( ( ((void*)temp+sizeof(list)+ sizetemp)  ==  ((void*)trav))  )
		{
		//printf("Outer= %d , Outer_prev =%d , inner =%d, inner_prev =%d\n",(lhead->size), (prev_lhead -> size), (trav->size),(prev_trav->size));
		//printf("outer = %d ,inner =%d\n",i,j);

		    if(i>j)
		    {
				
						//printf("ENTER\n");
					if(  trav == prev_trav)
					{
					//	printf("ENTER\n");
							Head=Head->next;		  	
							trav->next=NULL;
							lhead->size= lhead->size + trav->size + sizeof(list);
							service=1;
					}
					else
					{
							prev_trav->next= trav->next;
							trav->next=NULL;
							lhead->size= lhead->size + trav->size + sizeof(list);
							service=1;
					}




			}

		    else if(i<j)
		    {
				if (((lhead)->next) == trav )
				{
					lhead->next=trav->next;
					trav->next=NULL;
					lhead->size= lhead->size + trav->size + sizeof(list); 	
					service=1;
				}
	
				else
				{
					prev_trav->next= trav->next;
					trav->next=NULL;
					lhead->size= trav->size + lhead->size + sizeof(list);	
					service=1;
				}



		   }
			




	
		}	
	
		if(j!=0)
		{prev_trav = prev_trav->next;}
		trav=trav->next;
		j++;
	}


if(i!=0)
{ prev_lhead =prev_lhead->next; }
lhead= lhead-> next;
i++;

if(service ==1)
{
lhead=Head;
prev_lhead=Head;
i=0;
}
service=0;
}
//COALACE END




}



void Mem_Dump()
{
list * traverse=Head;
	while(traverse!=NULL)
	{
		printf("size if -> %d , address -> %p\n",traverse->size, (void*)traverse);
		traverse = traverse->next; 
	}

}




