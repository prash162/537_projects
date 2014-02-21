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

void pwd(char * argv2[])   //pwd func
{
	char *path;
	path=(char*) malloc(256);
	path=getcwd(path,256);
	path= strcat(path,"\n");

		if(!argv2[1])
		   write(STDOUT_FILENO,path, strlen(path));
		else
		  {printerror();}
}

void cd(char* argv[])
{
  char *env = (char*)malloc(256);
	 if (env==NULL)
 	 {
	    printerror();
 	 }
 
    if(argv[1]==NULL)
    {
	env=getenv("HOME");  
        int w;
        w=chdir(env);
	    if(w==-1)
             {
      	     printerror();
      	     }
    }
  
    else if(argv[1][0]!='~')
   {
   strcpy(env,argv[1]);
   int w;
   w=chdir(env);
  	 if(w==-1)
  	 {
  	 printerror();
  	 }
  }
   else 
   {
    printerror();
   }

}




int main(int argc , char *argv[])   // main
{
char * savepointer1;
char * savepointer2;

char * savepointer3;
int id=0;
int rpipe[2];
int lpipe[2];
int fileon=0;
int filerr=0;
int pipeon=0;
//int pipeerr=0;
int pstat;
int pstat1;
int iter;
int lines=3;
char * store[lines];
int cnti=0;
int cnt;
//int quit=0;
//int cd1=0;
//int pwd1=0;
FILE * myfile;



if(argc==2)
   {

      myfile = fopen(argv[1], "r");
      if(myfile==NULL) 
		{printerror();
		exit(1);
		}
  long n;
  fseek(myfile,0L,SEEK_END);
   

   n=ftell(myfile);
	 if (n==0)		   
	{
	exit(0);	
		}

fseek(myfile,0L,SEEK_SET);
     char * temp1=(char *)malloc(n);
		if (temp1==NULL)
		{printerror();
		exit(0);           
}

   int ch;
       lines=0;
  
   fclose(myfile);
   
myfile = fopen(argv[1], "r");
   do
   {
       ch = fgetc(myfile);
             if(ch == '\n')
                lines++;
   } while (ch != EOF);
 fclose(myfile);  
  
myfile = fopen(argv[1], "r+");
  int num=0;
  char * line;

if(n>=2)
{
   while((line=fgets(temp1,n,myfile))!=NULL)
    {
        
      store[num]=strdup(line);
	
      num++;
    }
 }

else
{   
write(STDOUT_FILENO,"\n", 1);
exit(0);
      }  

  fclose(myfile);
 
    free(temp1);
   }


iter=0;
while(1)
{
//if(argc==1)
// printf("537sh> "); 

 char* parse;
  parse=(char*)malloc(512*(sizeof(char)));

  if (parse==NULL)
  {printerror();}


char * parse3=(char *)malloc(512);

if(parse3==NULL)
{printerror();}


if(argc==1)
{

  parse=fgets(parse,512,stdin);
if(parse == NULL)
{
printerror();
}
 parse3=strncpy(parse3,parse,(strlen(parse)-1));
 parse3[strlen(parse)-1]= '\0';
}

else if(argc==2)
{

if(iter!=lines)  
strcpy(parse,store[iter]);

if(strlen(parse) > 512)
{
write(STDOUT_FILENO, parse, strlen(parse));
printerror();
iter++;
continue;
}

else if(strlen(parse) == 0)
{
exit(0);
}



if((strchr(parse,'\n'))==NULL)
{
parse3=strncpy(parse3,parse,(strlen(parse)));
parse3[strlen(parse)]= '\0';
}

else
{
parse3=strncpy(parse3,parse,(strlen(parse)-1));
parse3[strlen(parse)-1]= '\0';

}
write(STDOUT_FILENO, parse3, strlen(parse3));

write(STDOUT_FILENO,"\n",1);

}


else
{
printerror();
exit(1);
}
  
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
;
  
count++;



char* argv[8];
char * parse2[count];
int mulissue=0;

if((strchr(parse3,'+')!=NULL) && ((strchr(parse3,';')!=NULL)))
{
printerror();
mulissue=1;
}

else if ((strchr(parse3,';')!=NULL))
{  
  int nm=0;
const char * p=parse3;
int l=0;
int semi=0;


 for(l=0;l<strlen(parse3);l++) 
{
 if( (strncmp(p,";",1))==0    )
{
semi++;
}
p++; 
}

if(semi==(strlen(parse3)))
{
exit(0);
}

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


else if((strchr(parse3,'+')!=NULL) && (strchr(parse3,'+')) )
{
printerror();
exit(0);
}

else
{
  
  parse2[0]=parse3;  }


int nm=0; 

pid_t status;

while(nm<=(count-1) )
{

  pipeon=0;
fileon=0;
int len=strlen(parse2[nm]);

char * temp=(char*)malloc(len*(sizeof(char)));

if(temp==NULL)
{
printerror();
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
picnt++;
temp=parse2[nm];



if((strchr(temp,'|'))!=NULL )
{
pipeon=1;
}


int pipecount=0;

char* temp1[2];

if ((strchr(temp,'>'))!=NULL)
{
 cnt=0; 
temp1[cnt]=strtok_r(temp,">",&savepointer3);

while(temp1[cnt]!=NULL)
{

cnt++;
temp1[cnt]=strtok_r(NULL,">",&savepointer3);

}

cnti=0;
char * tok7= strtok(temp1[1]," 	");
{
      while(tok7!=NULL)
      {
          cnti++;      
         tok7= strtok(NULL," 	");

      }

}

fileon=1;
if ((cnt > 2) || (cnti > 1) || (cnti ==0) )
{filerr=1;


fileon=0;
}


}

else
{
temp1[0]=temp;
}



int ipipe = 0;
  char *pch=strchr(parse,'|');
    while (pch!=NULL) {
          ipipe++;
              pch=strchr(pch+1,'|');
                }

tok3=strtok_r(temp1[0],"|",&savepointer1);
int picount=0;
    while(tok3!=NULL)
{

if(pipeon==1)
{ 
pstat=pipe(rpipe);

if (pstat==-1)
{
printerror();
}

}

if(pipeon==1)
{ 
pstat1=pipe(lpipe);

if (pstat1==-1)
{
printerror();
}

}

 
char * toktmp=tok3;
{
  int l=0;
  tok=strtok_r(toktmp,"	 ",&savepointer2);   // Actual parsing to find arguments

  while(tok!=NULL)    
 {


  argv[l]=strdup(tok);
 
 tok=strtok_r(NULL,"	 ",&savepointer2);
  l++;
    }
  argv[l]=NULL;
}


tok3=strtok_r(NULL,"|",&savepointer1);
int argzero=0;
  //PIPE   
  if (argv[0]==NULL)
{
argzero =1;
}

if((strncmp(argv[0],"quit",4) ==0) && (argzero ==0))   // issue with quit have to give it twice sometimes
    {
      
          
     if((strchr(parse,'+')==NULL) )
     { //quit=1;
       exit(0);

     }     
      
     else if (filerr==1)
     {
     printerror();
     exit(1);
     }

     else
     {printerror();
     }
       
    }      
       
   else if((strncmp(argv[0],"pwd",3)==0) && (argzero==0)) 
        {
     
     if((strchr(parse,'+')==NULL))
     { 
       pwd(argv);}      

     
     else if (filerr==1)
     {
     printerror();
     }
     
     
     else
     {
      //pwd1=1; 
       printerror();     
     }

        break;
        }

  else if ((strncmp(argv[0],"cd",2)==0)&& (argzero==0))
          {
         
      
     if((strchr(parse,'+')==NULL))
     { 
       cd(argv);}      
    
     else if (filerr==1)
     {
     printerror();
     }
     
     else
     {
       //cd1=1;
       printerror();
    
     }
     
          break;
          }
         
else 
   argzero=0;
    {
         id=fork();
              if(id==0)//child
                    {      
		            
                               if((pipeon ==1) && (pipecount!=ipipe) )
				{


				close(rpipe[0]);
			       	dup2(rpipe[1],1);	
					}

				
                    		  close(rpipe[0]);
                    		close(rpipe[1]);
	

                if((fileon==1)  && ( picount == ipipe))
                { 

                      temp1[1]= strtok(temp1[1]," ");


                      close(STDOUT_FILENO);

                    int f=  open(temp1[1],O_CREAT | O_WRONLY | O_TRUNC,S_IRWXU);
				if(f==-1)
					{ printerror();}
				               
 }
                  if ((mulissue!=1) &&  (filerr!=1)  ){
                    execvp(argv[0],argv);
                    printerror();}

                  else
                  {printerror();}

                     exit(1);
                    }
        

                else if(id>0) //parent
                   {    

			if((pipeon==1) )
			{   
				
			
			       close(rpipe[1]);
			       dup2(rpipe[0],0);	
                             
			

				if( pipecount==picnt)
                       	 	 while ((id = wait(&status)) != -1);
			
                    		close(rpipe[0]);
                    		close(rpipe[1]);
			}	


                        if(((strchr(parse,'+')==NULL) && pipeon!=1) )
                        {
                      
                        {
                                  while ((id = wait(&status)) != -1);
                        }
                        }
                    



                       else
                        {
                 if((((strchr(parse,'+')!=NULL)  && (nm==count-1))  && (pipeon!=1)))
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
while ((id = wait(&status)) != -1);
}

else
{
pipecount=0;
}
picount++;


close(rpipe[0]);
close(rpipe[1]);



}
pipeon=0;
picount =0;
nm++;

filerr=0;

}
iter++;
 if(argc==2)
{ if(iter==lines)
    {
    exit(0);
    }
}

}

return 0;
}
