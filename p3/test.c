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

printf("============\n");
Mem_Dump();
printf("============\n");

printf("free 100\n");
int a=Mem_Free(ptr );


printf("============\n");
Mem_Dump();
printf("============\n");

printf("free 250\n");
int b=Mem_Free(ptr3);

printf("============\n");
Mem_Dump();
printf("============\n");

printf("alloc 150\n");
void * ptr7=Mem_Alloc(150);


printf("============\n");
Mem_Dump();
printf("============\n");


printf("free 450\n");
int c=Mem_Free(ptr5 );



printf("============\n");
Mem_Dump();
printf("============\n");

printf("free 200\n");
int d=Mem_Free(ptr2 );


printf("============\n");
Mem_Dump();
printf("============\n");


void * ptr8=Mem_Alloc(345);

printf("allocating 345 \n");

printf("============\n");
Mem_Dump();
printf("============\n");

printf("free 350\n");
int e=Mem_Free(ptr4);


printf("============\n");
Mem_Dump();
printf("============\n");

printf("free 500\n");
int f=Mem_Free(ptr6 );



printf("============\n");
Mem_Dump();
printf("============\n");


printf("free 150\n");
int m=Mem_Free(ptr7 );

printf("============\n");
Mem_Dump();
printf("============\n");


int p=Mem_Free(ptr8 );

printf("============\n");
Mem_Dump();
printf("============\n");
return 0;
}
