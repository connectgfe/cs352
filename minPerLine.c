/*
* File: minPerLine.c
* Author: Giulio Esposito
* Purpose: find the min value in a given string of possible intgers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int *makeIarr(char**);
void order(int*);
int strcnt,intcnt;
int goodline;
int status;

int main(){


    int i=0;
    status=0;
    strcnt=0;
    int offset=0;
    size_t ln=0;

    char **line=(char**)malloc(sizeof(char*));
    char **input;


    while(getline(&*line,&ln,stdin)!=EOF){
     if(**line=='\n'){ fprintf(stderr,"Empty string\n");
     status=1;
     continue;}
//    printf("L1 %s\n",*line);

     input=(char**)malloc(sizeof(char*));
     *(input)=(char*)malloc(64*sizeof(char));

       while(sscanf(*line,"%s%n",*(input+i),&offset)==1){
 //      printf("%s ",*(input+i));


       *line+=offset;
       i++;
       strcnt++;
       input=(char**)realloc(input,(i+1)*sizeof(char*));
       *(input+i)=(char*)malloc(64*sizeof(char));
       }
  //  printf("   i:%d\n",i);

    int *arr= makeIarr(input);

    int m;
    for(m=0;m<(i+1);m++){
    free(*(input+m));}
    free(input);

    i=0;
     if(goodline==0){
     order(arr);
     int num=*arr; 
     printf("%d\n",num);
    }


    free(arr);
    intcnt=0;
    ln=0;
    offset=0;
    strcnt=0;
}

return 0;
}


int *makeIarr(char **test1){
  int *ar=(int*)malloc(sizeof(int));
  int i,j;
  intcnt=0;
  goodline=0;
  for(i=0;i<strcnt;i++){

     size_t len=strlen(*(test1+i));
        for(j=0;j<len;j++){
          if(isdigit(*(*(test1+i)+j))==0){
            *(test1+i)=NULL;
            status=1;
           goodline=1;
           break;}
        }

        if(*(test1+i)!=NULL){

          *(ar+intcnt)=atoi(*(test1+i));
          ar=(int*)realloc(ar,(2+intcnt)*sizeof(int));
          intcnt++;
        }
  }

   *(ar+intcnt)=-1;
   if(goodline==1){
     fprintf(stderr,"Line contains something other than digits and white space\n");
  }

   return ar;
}

void order(int *arr){
  int cnt=0;
  int i=0;
  while(*(arr+i+1)!=-1){
   int temp;
   if(*(arr+i+1)<*(arr+i)){
     temp=*(arr+i);
     *(arr+i)=*(arr+i+1);
     *(arr+i+1)=temp;
    cnt++;}
    i++;}

  if(cnt==0){
 // printf("end\n");
  return;}
  order(arr);
}
