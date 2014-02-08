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

void quit()      // quit function
{
exit(0);
}

void pwd()
{
char *path;
path=(char*) malloc(256);
path=getcwd(path,256);
printf("%s\n",path);
}

void cd()
{
char *env = (char*)malloc(8);
env=getenv("HOME");  
int w;
w=chdir(env);
if(w==-1)
  {
  error();
  }

}


int main(int argc , char *argv[])   // main
{

int id =fork(); 

while(1)
{
  
  if (id==0) //child
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
printf(" the number of arguments are %d\n",count);             // 






tok=strtok(parse," ");   // Actual parsing to find arguments
while(tok!=NULL)    
{
tok=strtok(NULL," ");
}                          //           






    
    if(parse==NULL)
          {error();}

       if(strncmp(parse,"quit",4) ==0)
      {
       quit();
      }
      else if(strncmp(parse,"pwd",3)==0)
      {
      pwd();
      }
     
       else if(strncmp(parse,"cd",2)==0)
       {
       cd();
       }




  }

  else if(id>0) //parent
  {(void)wait(NULL);
    break;
  }
  else
  {error();}
}
return 0;
}
