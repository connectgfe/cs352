#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int parln(char*);
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
      fprintf(stderr,"M slave pid: %s\n",spid);
 
      int val=0;
      size_t len=0;
      char *line=NULL;      
 
      while(val>-1){
               
        val=getline(&line,&len,stdin);        
        if(val<2){break;}   
   //   fprintf(stderr,"%s",line);
          char *templn=line; 
         
         if( parln(templn)==0 ){
             printf("**need to terminate process(1)**\n");
             fprintf(stderr,"M Error: input error\n");
             status=1;  
         }

         if( parln(templn)==1 ){
             printf("%s",line);
         } 
         if( parln(templn)==2 ){
             printf("**need to terminate process(2)**\n");
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

int parln(char *line){

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

