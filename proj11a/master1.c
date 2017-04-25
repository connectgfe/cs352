#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>

int mparln(char*);
int status;

int main(){
  
  status=0;
  int timeout1=0;
  int timea=0;
  int timeb=-1;

  struct stat *sb=malloc(sizeof(stat));;



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
      int pd=atoi(spid);

      fprintf(stderr,"M slave pid: %s %d\n",spid,pd);
 
      int val=0;
      size_t len=0;
      char *line=NULL;      
 
      while(val>-1){
               
        val=getline(&line,&len,stdin);        
        if(val<2){break;}   
//fprintf(stderr,"%s",line);
          char *templn=line; 
         
         if( mparln(templn)==0 ){
             printf("@k 1 **need to terminate process(1)**\n");
             sync(); 
             sleep(1); 
//             kill(pd, 1);

             fprintf(stderr,"M Error: input error(1)\n");
             status=1;  
         }

         if( mparln(templn)==1 ){
             sync();
             printf("%s",line);
         } 
         
         if( mparln(templn)==2 ){
             printf("@k 2 **need to terminate process(2)**\n");
             sync(); 
             sleep(1); 
//             kill(pd, 2);
             
             fprintf(stderr,"M Error: input error(2)\n");
             status=1;  
         }  

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


return status;

}

int mparln(char *line){

  if(*line!='@'){ return 1;}
   line++;
  
  if(*line=='c'){ 
    line++;
    if(*line==' '){   
     return 2;}  
  }
  
  if(*line=='s'){ 
    line++;
    if(*line==' '){   
     return 3;}  
  }
  
  if(*line=='i'){ 
    line++;
    if(*line==' '){   
     return 4;}  
  }
  
  if(*line=='t'){ 
    line++;
    if(*line==' '){   
     return 5;}  
  }
  
  if(*line=='r'){ 
    line++;
    if(*line==' '){   
     return 6;}  
  }

  return 0;

}

