#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int sprsln(char*);
int status;

int main(){

   status=0; 
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
  
   while(val>-1){
   
     val=getline(&inln,&len,stdin);
     if(val<2){break;}
     
     char *templn=inln;    
     
     if(sprsln(templn)==1){ 
       sync();
       printf("S line: %s",inln);
     } 
     
     if(sprsln(templn)==2){ 
       sync(); 
       printf("S line: status kill(1)\n");
       return status; 
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

  if(*line=='k'){ return 2;}


  return 0;
}
