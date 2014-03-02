#include "mem.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char * argv[])
{
(void) Mem_Init(20000,1);

void * ptr =Mem_Alloc(100);
void * ptr2=Mem_Alloc(200);
void * ptr3=Mem_Alloc(250);
void * ptr4=Mem_Alloc(350);
void * ptr5=Mem_Alloc(450);
void * ptr6=Mem_Alloc(500);



int a=Mem_Free(ptr );


printf("============\n");
Mem_Dump();
printf("============\n");

int b=Mem_Free(ptr3);

printf("============\n");
Mem_Dump();
printf("============\n");

int c=Mem_Free(ptr5 );

printf("============\n");
Mem_Dump();
printf("============\n");

int d=Mem_Free(ptr2 );

printf("============\n");
Mem_Dump();
printf("============\n");

int e=Mem_Free(ptr4);


printf("============\n");
Mem_Dump();
printf("============\n");
int f=Mem_Free(ptr6 );



printf("============\n");
Mem_Dump();
printf("============\n");

return 0;
}
