#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<limits.h>
extern int errno;

struct save{
int index;
int counta;

};


int count(char const *string,char const *string1)   //function to count number of instances
{
 char const * p=string;
 int count;
 for (count=0; (p=strstr(p,string1)) ;++count)
  {
     if(!p)
       break;
    p=p+ strlen(string1);     // CHANGE MADE HERE CHECK THIS PREVIOUSLY P++

}
return count;
}



int main(int argc, char *argv[])    // MAIN
{
int nfile;
char buf[PATH_MAX + 1];
FILE *f2;

char buf2[PATH_MAX + 1];
 if (argc>1)     //CHeck this part it should probably be argc>1                    //get number files
 {nfile= atoi(argv[1]);}
 else
 {
 nfile=0;}

struct save sav[nfile];

int temp= 3+ nfile + 1;

 if((argc == temp || argc == temp-1))   // CORRECT NUMBER OF ARGUMENTS CASE
 { 
    int i;
    if(argv[temp-1])              // Check if any input file is same as output file
     {

       f2=fopen(argv[temp-1],"a+");
   
       if(errno!=0)
         {
         fprintf(stderr,"Error: Cannot open file '%s'\n",argv[temp-1]);
         exit(1);
         }

      for(i=0; i<nfile;i++)
 	{
         if(strcmp((realpath(argv[3+i],buf2)),(realpath(argv[temp-1],buf))) == 0)
            {
                    fprintf(stderr, "Input and output file must differ\n");
		     exit(1);
                     }
	}

        fclose(f2);
     }
    

// all condition satisfied so start
int val;
int val2= 2+ nfile;
 for(val=3;(val<= val2);val++ )
{
	FILE *file = fopen(argv[val],"rb");
	 if(errno!=0)
	 {
	  fprintf(stderr,"Error: Cannot open file '%s'\n",argv[val]);
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
        sav[val-3].index=val;
        sav[val-3].counta=counter;
        
//	printf("%s =  %d\n",argv[val],counter);
	fclose(file);
}

int j;
int k;

for(k=0;k<nfile;k++)
{
  for(j=0;j<nfile-1;j++)
  {   
    if( (sav[j].counta) < (sav[j+1].counta))
    {
      int temp= sav[j+1].counta;
      sav[j+1].counta = sav[j].counta;
       sav[j].counta=temp;

       int temp2= sav[j+1].index;
      sav[j+1].index = sav[j].index;
       sav[j].index=temp2;
    
    }
  }
}

  if(argv[temp-1]) 
  {

  f2=fopen(argv[temp-1],"w");
if (errno!=0)
  {
   fprintf(stderr,"Error: Cannot open file '%s'\n",argv[temp-1]);
   exit(1);
   }

  int l;
  for(l=0;l<nfile;l++)
  {
  fprintf(f2,"%d %s\n",(sav[l].counta), (argv[(sav[l].index)]));
  }
     fclose(f2);
  }

  else  
  {
  int m;  
   for(m=0;m<nfile;m++)
   {
   printf("%d %s\n",(sav[m].counta), (argv[(sav[m].index)]));
   }
  }


}

	
else                                 //WRONG NUMBER OF ARGUMENTS CASE
 {                    
 fprintf(stderr,"Usage: search <input-number> <key-word> <input-list> <output>\n");
 exit(1);
 }
//free(f1);
return 0;
}
