#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
int extern errno;

void printerror()      //error function
{
char error_message[30] = "An error has occurred\n";
int n=write(STDERR_FILENO, error_message, strlen(error_message));
if(n==-1)
{
printerror();
//exit(0);
}
}

void pwd()   //pwd func
{
char *path;
path=(char*) malloc(256);
path=getcwd(path,256);
printf("%s\n",path);
}

void cd(char* argv[])
{
char *env = (char*)malloc(256);
  if (env==NULL)
  {
  printerror();
  }

if(argv[1]==NULL)
{env=getenv("HOME");  }

else
{
  strcpy(env,argv[1]);
}

int w;
w=chdir(env);

if(w==-1)
  {
  printerror();
  }
}




int main(int argc , char *argv[])   // main
{
char * savepointer1;
char * savepointer2;
int id=0;
int fd[2];
while(1)
{
 printf("537sh> "); 
  char* parse;
  parse=(char*)malloc(512*(sizeof(char)));
  if (parse==NULL)
  {printerror();}
   
parse=fgets(parse,512,stdin);  
  
char const* p=parse;
char const* q=parse;
q++;
    
char * tok;
int count=0;



int k;
for(k=0;(k<(strlen(parse)+1));k++)                            // To find number of arguments in the string
{  
  if ((strchr(parse,';')!=NULL))
  {
  if((((strncmp(p,";",1)))==0) && ((strncmp(q,";",1))!=0) )
   { 
   count++;
   }
    p++;
    q++;
  }


  if ((strchr(parse,'+')!=NULL))
  {
  if((((strncmp(p,"+",1)))==0) && ((strncmp(q,"+",1))!=0) )
  {
  count++;
  }
    p++;
    q++;
  }

}

  
count++;



char* argv[8];
char * parse2[count];
char * parse3=malloc(512);

parse3=strncpy(parse3,parse,(strlen(parse)-1));

//  int nm=0;
if ((strchr(parse3,';')!=NULL))
{  
  int nm=0;
  tok=strtok(parse3,";");

    while(tok!=NULL)
    {
    parse2[nm]=tok;
    tok=strtok(NULL,";");
    nm++;
    }
}

else if((strchr(parse3,'+')!=NULL))
{

  int nm=0;
 
  tok=strtok(parse3,"+");
    while(tok!=NULL)
    {
    parse2[nm]=tok;
    tok=strtok(NULL,"+");
    nm++;
    }
}

else
{  parse2[0]=parse3;  }


int nm=0; 

pid_t status;
while(nm<=(count-1) )
{


int len=strlen(parse2[nm]);
char * temp=malloc(len);
temp=parse2[nm];

char* tok3;
 


    tok3=strtok_r(temp,"|",&savepointer1);

    while(tok3!=NULL)
{ 
 

char * toktmp=tok3;
{
  int l=0;
  tok=strtok_r(toktmp," ",&savepointer2);   // Actual parsing to find arguments


  while(tok!=NULL)    
 {


  argv[l]=strdup(tok);
  tok=strtok_r(NULL," ",&savepointer2);
  l++;
    }
  argv[l]=NULL;
}

;
tok3=strtok_r(NULL,"|",&savepointer1);

  
      
 
   if(strncmp(argv[0],"quit",4) ==0)   // issue with quit have to give it twice sometimes
       {
          exit(0);      
        }

   else if(strncmp(argv[0],"pwd",3)==0)  
        {
        pwd();
        break;
        }

  else if (strncmp(argv[0],"cd",2)==0)
          {
          cd(argv);
          break;
          }
         
else 
       {      
         id=fork();


              if(id==0)//child
                    {   
                      
               //   printf("id of child is: %d\n", getpid());                      
                     execvp(argv[0],argv);
                     printerror();
                     exit(0);
                    }
        

                else if(id>0) //parent
                   {
                  
                 // printf("id of parent is: %d\n", getpid());                      
                        
                        if((strchr(parse,'+')==NULL))
                        {(waitpid(-1,&status,0)!=getpid());                
                        }

                        else
                        {
                              if((strchr(parse,'+')!=NULL)  && (nm==count-1) )
                                  
                             {
                               //printf("%d:%d\n",nm,count);
                               int l;
                                for(l=0;l<count;l++)
                                {  (void) waitpid(0,&status,0);
                                  }
                             
                             }               
                        
                        }


                   //      {while(waitpid(-1,&status,0)!=id);}                
                   }
                   
               else
                 { 
                   printerror();
                    exit(0);

                 }
        }

}
nm++;

}



}
return 0;
}
