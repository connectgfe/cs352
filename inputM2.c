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
  

    int i=0;
    status=0;
    int strcnt=0;
    int offset=0;
    size_t ln=0;

    char *inln=NULL;
    
    char **input;
    char *temp=(char*)malloc(64*sizeof(char)); 

    while(getline(&inln,&ln,fp)!=EOF){
      char *line=inln; 
     input=(char**)malloc(sizeof(char*));
     *(input)=(char*)malloc(64*sizeof(char));

       while(sscanf(line,"%64s%n",temp,&offset)==1){

       strcpy(*(input+i),temp);

       line+=offset;
       i++;
       strcnt++;
       input=(char**)realloc(input,(i+1)*sizeof(char*));
       *(input+i)=(char*)malloc(64*sizeof(char));
       free(temp);
       temp=(char*)malloc(64*sizeof(char)); 

       }
    }

    int n=0;
       for(n=0;n<i;n++){
        printf("%s\n",*(input+n));
       } 
    int m;
    for(m=0;m<(i+1);m++){
    free(*(input+m));}
    free(input);




     free(temp);
     free(inln);

return 0;
}



