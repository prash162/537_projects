#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

int extern errno;

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
char * savepointer1;
char * savepointer2;
int id=0;
int rpipe[2];
int fileon=0;
int pipeon=0;
int pstat;


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
pipeon=0;
fileon=0;
int len=strlen(parse2[nm]);
char * temp=malloc(len);
temp=parse2[nm];



if((strchr(temp,'|'))!=NULL )
{
pipeon=1;
}

char* tok3;
int picnt=0;
int nt;
for(nt=0;nt<strlen(parse2[nm]);nt++ )
{
if((strncmp(temp,"|",1))==0)
{
picnt++;
}
temp++;
}
temp=parse2[nm];


if((strchr(parse,'|'))!=NULL )
{
pstat=pipe(rpipe);


if (pstat==-1)
{
printerror();
}
}

int pipecount=0;

//char * temp1;
char* temp1[2];


if ((strchr(temp,'>'))!=NULL)
{
 int cnt=0; 
char * savepointer3;
temp1[cnt]=strtok_r(temp,">",&savepointer3);

while(temp1[cnt]!=NULL)
{
cnt++;
temp1[cnt]=strtok_r(NULL,">",&savepointer3);

}

fileon=1;
}

else
{
temp1[0]=temp;
}

//printf(" da:  %s : %s \n",temp1[0],temp);


tok3=strtok_r(temp1[0],"|",&savepointer1);


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


tok3=strtok_r(NULL,"|",&savepointer1);

  //PIPE    
 
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
          if(pipeon==1)        
             {
              if(pipecount != (picnt+1))  
                  {
                    if(pipecount==0)
                    {
                    dup2(rpipe[1],1);
                    close(rpipe[0]);
                    }


                    else if(pipecount == picnt)
                    {
                    dup2(rpipe[0],0);
                    close(rpipe[1]);
                    }

                    else
                    {
                    close(rpipe[1]);
                    dup2(rpipe[0],STDIN_FILENO);
                    close(rpipe[0]);
                    dup2(rpipe[1],STDOUT_FILENO);
                    }

                  }
             }


                if(fileon==1)
                {
//                   printf("%s\n",temp1[1]);

                      temp1[1]= strtok(temp1[1]," ");

                   printf("%s\n",temp1[1]);

                      close(STDOUT_FILENO);
                      open(temp1[1],O_CREAT | O_WRONLY | O_TRUNC,S_IRWXU);
                }
                  
                    execvp(argv[0],argv);
                     printerror();
                     exit(0);
                    }
        

                else if(id>0) //parent
                   {    
                        if((strchr(parse,'+')==NULL) && pipeon!=1)
                        {
                       (void)wait(NULL);
                        //  (void)(waitpid(0,&status,0)!=getpid());                
                        }
                        
                        
                       else
                        {
                              if(((strchr(parse,'+')!=NULL)  && (nm==count-1)) && (pipeon!=1) )
                                  
                             {
                                   
                                  while ((id = wait(&status)) != -1);
                                 
                             }               
                        }
            

                     
                   }
               else
                 { 
                   printerror();
                    exit(0);

                 }
        }


if(pipeon==1 )
{pipecount++;
//while ((id = wait(&status)) != -1);

}
}
nm++;
if((pipeon==1)   ) 
{
close(rpipe[0]);close(rpipe[1]);
while ((id = wait(&status)) != -1);
}

}


}
return 0;
}
