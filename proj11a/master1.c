#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>



int main(){

  int timeout1=0;
  int timea=0;
  int timeb=-1;

  struct stat *sb=malloc(sizeof(stat));;


/*
  int val=0;
  size_t len=0;
  char *line=NULL;      
 
  while(val>-1){
        
    val=getline(&line,&len,stdin);        
    fprintf(stderr,"%s",line);

  }
      
*/

  while(timeout1<6){
    sleep(1);
    stat("slave_pid",sb);
    
//fprintf(stderr,"%lu\n",sb->st_mtime);
    timea=sb->st_mtime;
   

    if(timeb!=-1 && timea>timeb){ 
      fprintf(stderr,"M finshed(A): %d %d\n",timea, timeb);
      int fd1=open("slave_pid", O_RDONLY);
      char spid[20]; 
      read(fd1,spid,20); 
      fprintf(stderr,"M slave pid: %s\n",spid);
 
      int val=0;
      size_t len=0;
      char *line=NULL;      
 
      while(val>-1){
               
        val=getline(&line,&len,stdin);        
        if(val<2){break;}   
   //   fprintf(stderr,"%s",line);
        printf("%s",line);
      
      }

       free(line);
       break;
    } 
   
    timeb=timea; 

    if(timeout1==5){
      fprintf(stderr,"Error: file slave_pid not altered or exist\n");
    }
    timeout1++;
  }
 
  
  free(sb);  

//   write(1, "1234",4);


return 0;

}
