#include "mem.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#pragma pack(push,1)
typedef struct freelist
{
int size;
struct freelist * next;
}list;

#pragma pack(pop)

int globalDebug;
list * Head=NULL;
list *allocHead=NULL;

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
list* prev1;
list* curr1;
int check=0;
void * allocate;
list* allocateTemp;
void * temp;
int sizeAlloc;
int remainder;
remainder=size % 4;

	if ( remainder==0.0f )
	  {sizeAlloc=size;}

	else
 	  {sizeAlloc=size+4-remainder;}

		list * traverse=Head;
		list * traverse_prev=Head;
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
							traverse->next=NULL;
							Head= traverse->next;	
						}
						
						else
						{
							list * newHead=Head;
							
							Head = (void*)Head + sizeAlloc + sizeof(list);		
							Head->size = (newHead-> size)-sizeAlloc- sizeof(list);
							Head->next=newHead->next;
				                        newHead->size = sizeAlloc;
							newHead->next =NULL;
							allocateTemp=newHead;
							allocate=(void *)newHead + sizeof(list);
						}
						
							break;
					}					

					else
					{

							list * newHead=traverse;
							traverse = (void*)traverse + sizeAlloc + sizeof(list);		
							traverse_prev->next=traverse;
							traverse->size = (newHead-> size)-sizeAlloc- sizeof(list);
							traverse->next=newHead->next;
				                        newHead->size = sizeAlloc;
							newHead->next =NULL;
							allocateTemp=newHead;
							allocate=(void *)newHead + sizeof(list);
							prev1= traverse_prev;
							curr1=traverse;
							if((curr1->size) < (prev1->size) )
							{check=1;}
							break;	
					}
				}
			if(i!=0)
			{traverse_prev=traverse_prev->next;}
			traverse = traverse->next; 
			i++;
		}

		if(traverse==NULL)
		{perror("No space");
		return NULL;
		}
		else
		{
				list* tr=Head;
				list* tr_next=tr->next;
				int l=0;	
				while((tr_next!=NULL) && (check==1))
				{
					if(l==0)
					{
						if( (curr1->size) < (tr->size))
						{
							list * temp=curr1->next;
							curr1->next=tr;
							Head=curr1;
							prev1->next=temp;
							check=0;
						}

						else if(((curr1->size ) > (tr->size) ) && (( curr1->size) <= (tr_next->size))  )
						{
							
							list * temp= curr1->next;
							curr1->next=tr_next;
							tr->next=curr1;
							prev1->next=temp;
							check=0;
						}	
					}	
	
					else
					{
						if(((curr1->size ) > (tr->size) ) && (( curr1->size) <= (tr_next->size))  )
						{
							list * temp= curr1->next;
							curr1->next=tr_next;
							tr->next=curr1;
							prev1->next=temp;
						check=0;
						}	

					}
				tr=tr->next;
				tr_next=tr_next->next;
				l++;
				}

//  alloctaed list handler
				if(allocHead==NULL)
				{allocHead=allocateTemp;
				 allocHead->next=NULL;	
				}	
			
				else
				{
					list* allocTrav=allocHead;
					while(allocTrav!=NULL)	
					{
						if (allocTrav->next==NULL)
						{
							allocTrav->next=allocateTemp;
							allocateTemp->next=NULL;
							break;
						}	
					allocTrav=allocTrav->next;
					}
				}
			return  ( allocate );
		}
}

int Mem_Free(void *ptr)
{
list * header = (void *) ptr - sizeof(list);
list * traverse=Head;
list * trav_alloc=allocHead;
//allocate list handler
while(trav_alloc!=NULL)
{
	if(header == allocHead)
	{
		allocHead=allocHead->next;
		header->next=NULL;
		break;
	}

        else if((trav_alloc->next) == header)
	{
		trav_alloc->next=header->next;
		header->next=NULL;
		break;
	}
trav_alloc=trav_alloc->next;
}

//freelist handler
int size_to_free= header->size;
int k=0;
while( (traverse!=NULL) )
{
list * traverse_next= traverse->next;
		if(k==0)
		{
			if ( size_to_free <  (traverse->size))
			{
				header->next=Head;
				Head=header;
			}

			else if(((size_to_free) > (traverse->size))   &&  ( (size_to_free) <= (traverse_next->size)  ))
			{
				traverse->next= header;
				header->next=traverse_next;
			}
		}
		else
		{
			if(((size_to_free) > (traverse->size))   &&  ( (size_to_free) <= (traverse_next->size)  ))
			{
				traverse->next= header;
				header->next=traverse_next;
			}
		}
traverse=traverse->next;
k++;
}

//COALACE
list * lhead=Head;
list *prev_lhead=Head;
int i=0;
int service=0;
list* saveList;
list* savePrev;
while(lhead!=NULL)
{

int isHead=0;
int isGreater=0;
list * trav=Head;
list * prev_trav=Head;
int sizetemp = lhead->size;
	int j=0;
	while(trav!=NULL)
	{   list * temp =lhead;
		if( ( ((void*)temp+sizeof(list)+ sizetemp)  ==  ((void*)trav))  )
		{ 
		    if(i>j)
		    {
					if(  trav == prev_trav)
					{
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
	
			if(lhead==Head)
			{isHead=1;}
		if((lhead->next)!=NULL)
			{if( (lhead->size)> (lhead->next->size))
				{isGreater=1;}
				saveList=lhead;
				savePrev=prev_lhead;}
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
//changed part start
int complete=0;
list* tra=saveList;
list* tra_prev=saveList;
int sizecomp= saveList->size;
int count=0;
while((tra!=NULL) && (complete==0))
{
	if((isHead==1) && (isGreater==1))
	{
		if(sizecomp < (tra->size) )
		{		
			Head=Head->next;
			tra_prev->next=saveList;
			saveList->next=tra;

		}
	}

	else if((isHead==0) && (isGreater==1))
	{
		if(sizecomp < (tra->size))
		{
			savePrev->next=saveList->next;	
			tra_prev->next=saveList;
			saveList->next=tra;
		}


	}
tra=tra->next;
if(count!=0)
{tra_prev=tra_prev->next;}
count++;
}




//changed part end
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
		printf(" FREE LIST ;size if -> %d , address -> %p\n",traverse->size, (void*)traverse);
		traverse = traverse->next; 
	}

/*list * traverseA=allocHead;
	while(traverseA!=NULL)
	{
		printf(" ALLOCLIST :size if -> %d , address -> %p\n",traverseA->size, (void*)traverseA);
		traverseA = traverseA->next; 
	}
*/
}




