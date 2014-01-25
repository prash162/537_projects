#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<limits.h>
extern int errno;

//HI i am lenovo XD

struct save{
int files;
int index[files];
int counta[files];
};


int count(char const *string,char const *string1)   //function to count number of instances
{
 char const *p=string;
 int count;
 for (count=0; (p=strstr(p,string1)) ;++count)
  {
     if(!p)
       break;
    p++;

}
return count;
}



int main(int argc, char *argv[])    // MAIN
{
int nfile;
char buf[PATH_MAX + 1];

struct save sav;



char buf2[PATH_MAX + 1];
 if (argc>0)             //get number files
 {nfile= atoi(argv[1]);}
 else
 {
 nfile=0;}

int temp= 3+ nfile + 1;

 if((argc == temp || argc == temp-1))   // CORRECT NUMBER OF ARGUMENTS CASE
 { 
    int i;
    if(argv[temp-1])              // Check if any input file is same as output file
     { 
       // char *res=realpath(argv[temp-1],buf);
      for(i=0; i<nfile;i++)
 	{
	  
//	 if(strcmp(argv[3+i], argv[temp-1]) == 0)
         if(strcmp((realpath(argv[3+i],buf2)),(realpath(argv[temp-1],buf))) == 0)
            {
                    fprintf(stderr, "Input and output file must differ\n");
		     exit(1);
                     }
	}
     }
    
sav.files=nfile;
// all condition satisfied so start
int val;
int val2= 2+ nfile;
 for(val=3;(val<= val2);val++ )
{
	FILE *file = fopen(argv[val],"rb");
	 if(errno!=0)
	 {
	  fprintf(stderr,"Error: Cannot open file 'input.txt'\n");
	  exit(1);
	 }

	char *f1;
	long sz;
	fseek(file,0L,SEEK_END);
	sz=ftell(file);
	fseek(file,0L,SEEK_SET);


	f1=(char*)malloc(sz);
 
	  if(f1==NULL)   // IF MALLOC FAILS
	  {
	  fprintf(stderr,"Malloc failed\n");
	  exit(1);
	  }
        size_t num;
       num=fread(f1,sz,1,file);
         
	int counter;

	counter= count(f1,argv[2]);
        
	printf("%s =  %d\n",argv[val],counter);
	fclose(file);
}


	 }

 else                                 //WRONG NUMBER OF ARGUMENTS CASE
 {                    
 printf("Usage: search <input-number> <key-word> <input-list> <output>\n");
 exit(1);
 }
//free(f1);
return 0;
}
