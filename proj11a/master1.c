#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <string.h>


int mparln(char*);
int mparln2(char*);

int status;
struct sigaction act;

void my_handler(int n){
  printf("got it\n");
}

int main(){

   act.sa_handler= my_handler;
   sigemptyset(&act.sa_mask);
   sigaction(SIGINT,&act,NULL);
   act.sa_flags=0;
   act.sa_flags|=SA_RESTART;
  
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
 
      while(1){
               
        val=getline(&line,&len,stdin);        
        if(val<0){ break;} 
        // check exe to deal with blank lines
     //   if(val<2){continue;}   
//fprintf(stderr,"%s",line);
          char *templn=line; 

        // @ bad comm         
         if( mparln(templn)==0 ){

             fprintf(stderr,"Master: Error: bad cmnd error %s",line);
             status=1;  
         }
         
         // not comm then send to slave1
         if( mparln(templn)==1 ){
           int len1=strlen(templn);             
           sync();   
           write(1,templn,len1);
            //printf("%s",line);
         } 
        
         // send @c syntax error for slave 
         if( mparln(templn)==2 ){
            sync();          
            write(1,"@c",3);
 
//fprintf(stderr,"M : kill for slave(@c)\n");
         }  
        
         // @s send to slave to update sig txt
         if( mparln(templn)==3 ){
             char *temp3=line;
             temp3=temp3+2; 
             int num=0; 
             int k=0; 
             int fset=0;


          // need to parse for more than one arg  
             sscanf(temp3,"%d%n",&num,&fset);
             char other[1024]={'\0'};
             temp3=temp3+fset;
             sscanf(temp3,"%s",other);
             
            if(num>31 || num<1 || other[0]=='\0'){ 
               fprintf(stderr,"M Error: bad argument for @s\n");
             }
             int len3=strlen(templn);             
             sync();   
             write(1,templn,len3);
          

         }  
 
        // @k kill slave input
         if( mparln(templn)==7 ){

          int num=mparln2(templn);
          int k=0; 
          if(num==-1){
              fprintf(stderr,"Master: Error: bad argument for @k\n"); 
            }else{
               sync(); 
fprintf(stderr,"M : %d num for kill (@k)\n",num);
               sleep(1); 
               k=kill(pd, num);
           } 


/*            
             char *temp2=line;
             temp2=temp2+2; 
             int num=0; 
             int k=0; 
             int fset=0;


          // need to parse for more than one arg  
             sscanf(temp2,"%d%n",&num,&fset);
             char other[1024]={'\0'};
             temp2=temp2+fset;
             sscanf(temp2,"%s",other);
             
            if(num>31 || num<1 || other[0]!='\0'){ 
               fprintf(stderr,"M Error: bad argument for @k\n");
             }else{

*/
             sync(); 
//fprintf(stderr,"M : %d num for kill (@k)\n",num);
             sleep(1); 
             k=kill(pd, num);
              
             if(k==-1){ 
               fprintf(stderr,"M Error: kill for slave fail\n");
             } 
          } 

         // @i send sig to ingnore
         if( mparln(templn)==4 ){
          int num=mparln2(templn);
          if(num==-1){
             fprintf(stderr,"Master: Error: bad argument for @i\n"); 
           }else{ 
             int len4=strlen(templn);             
             sync();   
             write(1,templn,len4);
           }
         } 

         // @t send sig to dfl
         if( mparln(templn)==5 ){
          int num=mparln2(templn);
          if(num==-1){
             fprintf(stderr,"Master: Error: bad argument for @t\n"); 
           }else{ 
             int len5=strlen(templn);             
             sync();   
             write(1,templn,len5);
           }
         }

          // @r send sig to ingnore
         if( mparln(templn)==6 ){
          int num=mparln2(templn);
          if(num==-1){
             fprintf(stderr,"Master: Error: bad argument for @r\n"); 
           }else{ 
             int len6=strlen(templn);             
             sync();   
             write(1,templn,len6);
           }
         }

         // @T send to test signal
         if( mparln(templn)==8 ){
             int num=mparln2(templn);
             sync();   
             union sigval jam;
             
             sleep(1);
             sigqueue(pd, num, jam);
            
         } 
      

      sleep(.1);
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


  while(*line==' '){
    line++;
  }

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

  if(*line=='k'){ 
    line++;
    if(*line==' '){   
     return 7;}  
  } 

  if(*line=='T'){ 
    line++;
    if(*line==' '){   
     return 8;}  
  }

  return 0;

}
int mparln2(char *temp2){

       temp2=temp2+2; 
       int num=0; 
       int k=0; 
       int fset=0;


     // need to parse for more than one arg  
       sscanf(temp2,"%d%n",&num,&fset);
       char other[1024]={'\0'};
       temp2=temp2+fset;
       sscanf(temp2,"%s",other);
             
      if(num>31 || num<1 || other[0]!='\0'){ 
 //       fprintf(stderr,"M Error: bad argument for @k\n"); 
       return -1;
      }
              
     return num;

}
