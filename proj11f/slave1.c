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
struct sigaction dfl;
struct sigaction ign;

char **msg;
char *inln;
void cleanup();

void my_handler(int sig){

 if(strcmp(*(msg+sig),"terminate")==0){
   //clean up
//   printf("%s\n",*(msg+sig));
   cleanup();
   exit(status) ;
 } 
  
 write(1,*(msg+sig),strlen(*(msg+sig)));
// printf("%s",*(msg+sig));

}

void cleanup(){

   int j;
   for(j=0;j<32;j++){
    free(*(msg+j));
   }
   free(msg); 

   free(inln);
}

int main(){

   act.sa_handler= my_handler;
   sigemptyset(&act.sa_mask);
   sigaction(SIGINT,&act,NULL);
   act.sa_flags=0;
   act.sa_flags|=SA_RESTART;

   status=0; 
   msg=(char**)malloc(32*sizeof(char*));
 
  int i;
   for(i=0;i<32;i++){
     *(msg+i)=NULL;
   } 

 
   int time=sleep(2);
   char line[40];
   int ipid=getpid();

//printf("%d\n",ipid);
   char cpid[10]={'\0'};
   snprintf(cpid, 10, "%d",ipid);
//cpid[7]='\0';

//printf("%lu %s\n",strlen(cpid),cpid);
   int fd1=open("slave_pid", O_RDWR | O_CREAT | O_TRUNC, 0640); 
   write(fd1,cpid,strlen(cpid)); 
//printf("S slave1 done\n");

   int val=0;
   size_t len=0;
   inln=NULL;
  
   while(1){
   
     val=getline(&inln,&len,stdin);
     if(val<0){break;}
     char *templn=inln;    
    
     // non command pass line 
     if(sprsln(templn)==1){ 
/*     
        int len1=strlen(templn);
        char tempf[64];
        strcpy(tempf,templn);
        tempf[len1-1]='\0'; 
        len1=len1-2; 
        while(tempf[len1]==' '){
           tempf[len1]='\0';
           len1--;
        } 
        tempf[len1+1]='\n'; 
*/
      write(1,templn,strlen(templn));

    //   printf("%s",inln);
     } 
    
     // @c fatal for slave 
     if(sprsln(templn)==2){        
//fprintf(stderr,"Slave: Error: fatal syntax(1)\n");
       status=1; 
       cleanup();
       return status; 
     } 

     // @s set sig num to print text follwing num  
     if(sprsln(templn)==3){ 
     
       char *temp3=inln;
       temp3=temp3+2;
       int num=0;
       int fset=0;


       // need to parse for more than one arg  
        sscanf(temp3,"%d%n",&num,&fset);
       // if num=sigkill report error
        if(num==9 || num==19){
          fprintf(stderr,"Slave: Error: attempt to handle SIGKILL/SIGSTOP.\n"); 
          status=1;
        continue; 
        }        

        temp3=temp3+fset;
//fprintf(stderr,"S got @s num: %d\n",num);
     
        while(*temp3==' '){
           temp3++;
        }        
        
        int len3=strlen(temp3);
        
         
        char temp3f[64];
        strcpy(temp3f,temp3);
        temp3f[len3-1]='\0'; 
        len3=len3-2; 
        while(temp3f[len3]==' '){
           temp3f[len3]='\0';
           len3--;
        }
        temp3f[len3+1]='\n'; 
        sigaction(num,&act,NULL);
 
        if(*(msg+num)==NULL){
        *(msg+num)=(char*)malloc(64*sizeof(char));
        } 
        strcpy(*(msg+num),temp3f); 
     } 
  
     // @i ignore 
     if(sprsln(templn)==4){ 
     
       char *temp4=inln;
       temp4=temp4+2;
       int num=0;
       int fset=0;


       // need to parse for more than one arg  
        sscanf(temp4,"%d%n",&num,&fset);
       // if num=sigkill report error
        if(num==9 || num==19){
          
        fprintf(stderr,"Slave: Error: attempt to handle SIGKILL/SIGSTOP.\n"); 
        status=1; 
        continue; }  
        ign.sa_handler=SIG_IGN; 
        sigaction(num,&ign,NULL);
 
     } 

     // @t terminate 
     if(sprsln(templn)==5){ 
     
       char *temp5=inln;
       temp5=temp5+2;
       int num=0;
       int fset=0;


       // need to parse for more than one arg  
        sscanf(temp5,"%d%n",&num,&fset);
       // if num=sigkill report error
        if(num==9 || num==19){
          fprintf(stderr,"Slave: Error: attempt to handle SIGKILL/SIGSTOP.\n"); 
         status=1; 
         continue; 
        }        
        
        sigaction(num,&act,NULL);
        if(*(msg+num)==NULL){
        *(msg+num)=(char*)malloc(64*sizeof(char));
        }
        strcpy(*(msg+num),"terminate");
 
     }

     // @r restore to default
     if(sprsln(templn)==6){ 
     
       char *temp6=inln;
       temp6=temp6+2;
       int num=0;
       int fset=0;


       // need to parse for more than one arg  
        sscanf(temp6,"%d%n",&num,&fset);
       // if num=sigkill report error
        if(num==9 || num==19){
          fprintf(stderr,"Slave: Error: attempt to handle SIGKILL/SIGSTOP.\n"); 
        status=1; 
        continue; 
        }        
//printf("%d\n",num);        
        dfl.sa_handler=SIG_DFL;
        sigaction(num,&dfl,NULL);

      }
     
     if(sprsln(templn)==7){

       char *temp7=inln;
       temp7=temp7+2;
       if(*temp7==' '){
         cleanup();
         status=1;
         return status;
       }
     } 
//      sync();
    fsync(1);
   
   }
/*
   int j;
   for(j=0;j<32;j++){
    free(*(msg+i));
   }
   free(msg); 
*/
  cleanup();
//   free(inln);

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

  if(*line=='i'){ return 4;}
 
  if(*line=='t'){ return 5;}

  if(*line=='r'){ return 6;}

  if(*line=='k'){ return 7;} 

  return 0;
}
