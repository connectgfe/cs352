#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkargs(char*);

int main(){

  char *ln=NULL;
  int val=0;
  size_t len=0; 
  while(val>-1){
   val=getline(&ln,&len,stdin);
   printf("%d\n",checkargs(ln));
  }
  free(ln);

return 0;
}

int checkargs(char *line){
    
    char *temp=line;
    int cnt=0; 
    int offset=0;
//    printf("%s\n",temp);

    char *str=(char*)malloc(64*sizeof(char));
//    printf("%s\n",temp);

    while(sscanf(temp,"%s%n",str,&offset)==1){
       temp+=offset;
 //     printf("%s\n",temp);

   //  printf("%d %s %s\n",offset,temp,str);
      cnt++;

    free(str);
    str=(char*)malloc(64*sizeof(char));
    if(cnt>1027){break;}
    }
    
    free(str);

   // printf("word cnt: %d\n",cnt);


    return cnt;

}


