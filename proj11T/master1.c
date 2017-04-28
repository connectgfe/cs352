#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <string.h>



int status;
struct sigaction act;

void my_handler(int n){
  printf("got it\n");
}

int main(){

   act.sa_handler= my_handler;
   sigemptyset(&act.sa_mask);
   sigaction(SIGPIPE,&act,NULL);
   act.sa_flags=0;
   act.sa_flags|=SA_RESTART;
  
  status=0;
  int timeout1=0;
  int timea=0;
  int timeb=-1;
  struct stat *sb=malloc(sizeof(stat));;



    sleep(2);
    stat("slave_pid",sb);
    
//fprintf(stderr,"%lu\n",sb->st_mtime);
   

fprintf(stderr,"M finshed(A): %d %d\n",timea, timeb);
      int fd1=open("slave_pid", O_RDONLY);
      char spid[20]; 
      read(fd1,spid,20); 
      int pd=atoi(spid);

   fprintf(stderr,"M slave pid: %s %d\n",spid,pd);

      

     int val=0;
     char *line=NULL;
     size_t len=0;

     while(1){

      val=getline(&line,&len,stdin); 
      if(val<1){ break;}
    

      char *templn=line;
fprintf(stderr,"Master: %s",templn);
      if(strcmp(line,"kill\n")==0){
         kill(pd,9);
      } 
  
     write(1,templn,strlen(templn));
     sync(); 
     }
   
  
  free(sb);  

//   write(1, "1234",4);


return status;

}


