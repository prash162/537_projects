#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void error()      //error function
{
char error_message[30] = "An error has occurred\n";
write(STDERR_FILENO, error_message, strlen(error_message));
}



void pwd()
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
  error();
  }

if(argv[1]==NULL)
{env=getenv("HOME");  }

else
{

  strcpy(env,argv[1]);
 // strncpy(env,argv[1],(strlen(argv[1])-1));
}

int w;
w=chdir(env);

if(w==-1)
  {
  error();
  }
}




int main(int argc , char *argv[])   // main
{



while(1)
{
  
   
 printf("537sh> "); 
  char* parse;
  parse=(char*)malloc(512*(sizeof(char)));
  if (parse==NULL)
  {error();}
   
parse=fgets(parse,512,stdin);  
  
char const* p=parse;
char const* q=parse;
q++;
    
char * tok;
int count=0;


int k;
for(k=0;(k<(strlen(parse)+1));k++)                            // To find number of arguments in the string
{
  if((((strncmp(p," ",1)))!=0) && ((strncmp(q," ",1))==0) )
   { 
   count++;
   }
    p++;
    q++;
}
count++;
 
char* argv[8];


char * parse2=malloc(512);
parse2=strncpy(parse2,parse,(strlen(parse)-1));

if((strchr(parse2,';')==NULL ) || (strchr(parse2,'+')==NULL ))
{
  int l=0;
  tok=strtok(parse2," ");   // Actual parsing to find arguments

  while(tok!=NULL)    
  {
   // printf("%s\n",tok);
  argv[l]=strdup(tok);
  tok=strtok(NULL," ");
  l++;
    }
  argv[l]=NULL;
} 
  
  int id;      

   
         //   id =fork();

  
   if(strncmp(argv[0],"quit",4) ==0)   // issue with quit have to give it twice sometimes
       {

          exit(0);      
        }

   else 
       {      
         id=fork();
              if(id==0)//child
                    {         
                            
                         if(strncmp(argv[0],"pwd",3)==0)
                             {
                                   pwd();
                              }
     
                          else if(strncmp(argv[0],"cd",2)==0)
                             {
                                cd(argv);
                             }
 
                             else
                                {   
                              execvp(argv[0],argv);
                                 error();
                                }
                     } 

                else if(id>0) //parent
                   {
                  
                        pid_t status;
                    while(waitpid(0,&status,0)!=id);
                    
               //    while( waitpid(0, &status, WEXITED)!=id);
                   }
               else
                 {  error();}

         }           
}
return 0;
}
