#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>


int status;
struct sigaction act;
struct sigaction dfl;
struct sigaction ign;


void my_handler(int sig){

   printf("handled\n");
 }
 

int main(){

   act.sa_handler= my_handler;
   sigemptyset(&act.sa_mask);
   sigaction(SIGINT,&act,NULL);
   act.sa_flags=0;
   act.sa_flags|=SA_RESTART;

   status=0; 
 
   char line[40];
   int ipid=getpid();

//printf("%d\n",ipid);
   char cpid[10];
   snprintf(cpid, 10, "%d",ipid);
//cpid[7]='\0';

//printf("%lu\n",strlen(cpid));

   int fd1=open("slave_pid", O_RDWR | O_CREAT | O_TRUNC, 0640); 
   write(fd1,cpid,6); 
//printf("S slave1 done\n");

   int val=0;
   size_t len=0;
   char *inln=NULL;
  
   while(1){
   
     val=getline(&inln,&len,stdin);
     if(val<0){break;}
        
     printf("Slave: %s",inln);   
  

    sync();
    }

   free(inln);


return status;

}


