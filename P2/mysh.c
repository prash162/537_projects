#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void printerror()      //error function
{
char error_message[30] = "An error has occurred\n";
int n=write(STDERR_FILENO, error_message, strlen(error_message));
if(n==-1)
{
printerror();
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
int id=0;
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
//parse2[nm]=strncpy(parse2[nm],parse,(strlen(parse)-1));
//int nm=0;
//while(nm<=count)


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
 // int nm=0;
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

//printf("%d\n",count);

int nm=0; 
//while lop required here
while(nm<=(count-1) )
{

  printf("========\n");
{
  int l=0;
  tok=strtok(parse2[nm]," ");   // Actual parsing to find arguments
  while(tok!=NULL)    
  {
  argv[l]=strdup(tok);
  tok=strtok(NULL," ");
  l++;
    }
  argv[l]=NULL;
}
//printf("%s\n",parse);

  
      
 
   if(strncmp(argv[0],"quit",4) ==0)   // issue with quit have to give it twice sometimes
       {
          exit(0);      
        }

   else if(strncmp(argv[0],"pwd",3)==0)  
        {
        pwd();
        }

  else if (strncmp(argv[0],"cd",2)==0)
          {
          cd(argv);          
          }
         
else 
       {      
         id=fork();
              if(id==0)//child
                    {   
                      
                     execvp(argv[0],argv);
                     printerror();
                    }
        

                else if(id>0) //parent
                   {
                  
                        pid_t status;
                      
                        if((strchr(parse,'+')==NULL))
                        {while(waitpid(0,&status,0)!=id);}
                        
                      nm++;        
                    
                    
           //         continue;
                      

                   }
               else
                 { 
                   printerror();
                    break; 
                 }
        }
  
  }
pid_t status;
if((strchr(parse,'+')!=NULL))
{while(waitpid(0,&status,0)!=id);}
  // printf("========\n");
//continue;
   }
return 0;
}
