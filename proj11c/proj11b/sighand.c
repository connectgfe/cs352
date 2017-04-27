#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>


struct sigaction act;
struct sigaction act2;
char **msg;
void my_handler(int);

int main(){

   act.sa_handler= my_handler;
   sigemptyset(&act.sa_mask);

   act2.sa_handler= my_handler;
   sigemptyset(&act2.sa_mask);

/*
   sigaction(SIGINT,&act,NULL);
   act.sa_flags=0;
   act.sa_flags|=SA_RESTART;
*/

  msg=(char**)malloc(32*sizeof(char*));
  *(msg)=(char*)malloc(64*sizeof(char));  
  *(msg+1)=(char*)malloc(64*sizeof(char));  
  
  *(msg)="first msg";
  *(msg+1)="second msg";

  my_handler(1);
  my_handler(2);

  sigaction(SIGINT,&act,NULL);
  sigaction(SIGKILL,&act2,NULL); 
/*
  while(1){
  sleep(1);
  }
*/
 return 0;
}

void my_handler(int sig){


     printf("%s\n",*(msg+sig-1));     

     
}


