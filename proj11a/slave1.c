#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>


int sprsln(char*);
int status;
struct sigaction act;
char **msg;

void my_handler(int sig){

 printf("%s\n",*(msg+sig));
 
}

int main(){

   act.sa_handler= my_handler;
   sigemptyset(&act.sa_mask);
   sigaction(SIGINT,&act,NULL);
   act.sa_flags=0;
   act.sa_flags|=SA_RESTART;

   status=0; 
   msg=(char**)malloc(32*sizeof(char*));
   *(msg+1)=(char*)malloc(64*sizeof(char));
   *(msg+1)="jamboree time";
   sigaction(1,&act,NULL);

   int time=sleep(2);
   char line[40];
   int ipid=getpid();

printf("%d\n",ipid);
   char cpid[10];
   snprintf(cpid, 10, "%d",ipid);
//cpid[7]='\0';

//printf("%lu\n",strlen(cpid));

   int fd1=open("slave_pid", O_RDWR | O_CREAT | O_TRUNC, 0640); 
   write(fd1,cpid,6); 
   printf("S slave1 done\n");

   int val=0;
   size_t len=0;
   char *inln=NULL;
  
   while(1){
   
     val=getline(&inln,&len,stdin);
     if(val<0){break;}
     sync();     
     char *templn=inln;    
    
     // non command good line 
     if(sprsln(templn)==1){ 
       printf("S line: %s",inln);
     } 
    
     // @c fatal for slave 
     if(sprsln(templn)==2){        
       fprintf(stderr,"S Error: fatal syntax(1)\n");
       status=1; 
       return status; 
     } 

     // @s set sig num to print text follwing num  
     if(sprsln(templn)==3){ 
     
       sync();
       char *temp2=inln;
       temp2=temp2+2;
       int num=0;
       int fset=0;


       // need to parse for more than one arg  
        sscanf(temp2,"%d%n",&num,&fset);
       // if num=sigkill report error
        if(num==9){
 fprintf(stderr,"Slave: Error: attempt to handle SIGKILL.\n"); 
        continue; 
        }        

        temp2=temp2+fset;
fprintf(stderr,"S got @s num: %d\n",num);
     
        while(*temp2==' '){
           temp2++;
        }        
      
        sigaction(num,&act,NULL);
        *(msg+num)=(char*)malloc(64*sizeof(char));
        *(msg+num)=temp2; 
     } 
   
   }

   free(inln);

/*
read(0,line,30);

printf("NEW: %s\n",line); 
*/


return status;

}

int sprsln(char *line){

  if(*line!='@'){ return 1;}
   line++;

  if(*line=='c'){ return 2;}

  if(*line=='s'){ return 3;}




  return 0;
}
