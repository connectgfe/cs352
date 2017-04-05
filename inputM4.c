/*
* File: minPerLine.c
* Author: Giulio Esposito
* Purpose: find the min value in a given string of possible intgers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int goodline;
int status;

int main(int argc, char **argv){

char *targ=NULL;
  FILE *fp;



  if(argc>=1){

    fp=fopen(*(argv+1), "r");
      if(fp==NULL){
       fprintf(stderr,"Error with file\n");
       fclose(fp);
       return 1;}

      if(argc==3){
        targ=*(argv+2);}else{
        fprintf(stderr,"Not enough args Error\n");
        fclose(fp);
        return 1;}


  }else{
   fprintf(stderr,"No File Error\n");
     return 1;}
  
    int val=0;
    int i=0;
    status=0;
    int strcnt=0;
    int offset=0;
    size_t ln=0;

    char *inln=NULL;
    

    while(1){
      val=getline(&inln,&ln,fp);

      if(val==1){ continue;}
//printf("%d\n",val); 
      if(val==-1){  break;} 

      char *line=inln; 
      char temp[64];

       while(sscanf(line,"%64s%n",temp,&offset)==1){


       line+=offset;
       i++;
       strcnt++;
       printf("%s\n",temp);  

       }

    }




    if(fp!=NULL){
     fclose(fp);}

     free(inln);

return 0;
}



