#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include "funct11.h"



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
