#include <stdio.h>
#include <stdlib.h>


int main( int argc, char **argv){
  
  int status=0;
  printf("no of args: %d\n",argc);
  int i;
  for(i=0;i<argc;i++){
   printf("%s\n",*(argv+i));}

  int mrkr=0; 
  FILE *fp=fopen(*(argv+1), "r");
  
  if(argc>1){
   if(fp==NULL){
    printf("Error with file\n"); return 1;}
   if(argc>2){status=1;} 
  mrkr=1;  
  } 
  
  int val=0;
  char *line; 
  size_t len=0; 
  while(val>=0){
    if(mrkr==1){
     val=getline(&line,&len,fp);}else{
     val=getline(&line,&len,stdin);}
  printf("%s",line);
  line=NULL;
  len=0; 
  } 
  free(line);     




return status;
}
