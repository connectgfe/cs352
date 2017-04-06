/*
* File: minPerLine.c
* Author: Giulio Esposito
* Purpose: find the min value in a given string of possible intgers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funct.h"

int goodline;
int status;
int numV;
int flag;

int main(int argc, char **argv){


  char *targ=NULL;
  FILE *fp;
  int *vtx=NULL;


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
    status=0;
    int strcnt=0;
    int offset=0;
    size_t ln=0;

    char *inln=NULL;

    numV=1;
    flag=0;


  graph *grph=(graph*)malloc(sizeof(graph));
  grph->ver=(list*)malloc(sizeof(list));
  grph->ver->head=NULL;
  grph->nextv=NULL;



  vert *verhead=(vert*)malloc(sizeof(vert));
  verhead->vname=NULL;
  verhead->vind=0;
  verhead->next=NULL;
  verhead->cmd=(cmnd*)malloc(sizeof(cmnd));
  verhead->cmd->comnd=NULL;
  verhead->cmd->nextc=NULL;

    

    while(1){
      val=getline(&inln,&ln,fp);


      char first[64];
      char second[64];
      if(val==1){ continue;}
//printf("%d\n",val); 
      if(val==-1){  break;} 
     
      
// printf("no1\n"); 
     
      if(*inln=='\t' ){
        setcmnd(verhead,first,strdup(inln));
//printf("no2\n"); 
       continue; 
        } 
      char *inln2=inln;

      int fset=0;
      sscanf(inln2,"%64s%n",first,&fset);
      inln2+=fset;       
      int fset2=0;
      sscanf(inln2,"%64s%n",second,&fset2);
      inln2+=fset2; 
       
      char *line=inln2; 
      char temp[64];
     // line+=fset;      

//printf("%s %s %s\n",first,second,line);

       if(strcmp(second,":")==0){
       addvert(verhead,strdup(first),grph,1); 
//printf("no3\n"); 
       }else{
       fprintf(stderr,"Error improper format\n");
       status=1;
       return status;} 
      while(sscanf(line,"%64s%n",temp,&offset)==1){
//printf("no4\n"); 
 
   //   if(strcmp(temp,":")==0){ line+=offset; continue;} 
//printf("no5\n"); 

       addvert(verhead,strdup(temp),grph,0);
       addedge2(verhead,grph,first,temp);

       line+=offset;
       printf("%s %s\n",first,temp);  

       }
//printf("no6\n"); 

    }
//printf("no7\n"); 

  // do things with graph

  printf("targ: %s\n",targ);

   int i;
   vtx=(int*)malloc(numV*sizeof(int)); 
   for(i=1;i<numV;i++){
       *(vtx+i)=(i);
printf("%d\n",*(vtx+i)); 
  }

  

    printf("\ngraph \n");
   printG2(grph);
   printf("\nvlist \n");
   printVlist(verhead);  
  printf("\nisconn \n");

   buildm(verhead,grph,vtx,8);


//   printf("%s\n",getcmnd(verhead,"first"));

// free vertlist

    vert *tempv;
     while(verhead!=NULL){
       tempv=verhead;
       verhead=verhead->next;

       free(tempv->vname);

//           if(tempv->cmd!=NULL){
            cmnd *tempc;

              while(tempv->cmd!=NULL){
                 tempc=tempv->cmd;
                 tempv->cmd=tempv->cmd->nextc;
                 free(tempc->comnd);
                 free(tempc);
              }

 
//         }


//       free(tempv->cmd);
       free(tempv);
      }
  if(vtx!=NULL){  
   free(vtx);}


// free lists    
   graph *cur=grph; 
   while(cur->nextv!=NULL){
    node *temp;
     while(cur->ver->head!=NULL){
        temp=cur->ver->head;
        cur->ver->head=cur->ver->head->next;
        free(temp);
     }
    cur=cur->nextv;
   }

// free graph
    graph *tempg;
    list *templ;
    while(grph->nextv!=NULL){
        tempg=grph;
        templ=grph->ver;
        grph=grph->nextv;

        free(templ);
        free(tempg);
     }


   free(verhead);

   free(grph->ver);
    free(grph);




    if(fp!=NULL){
     fclose(fp);}

     free(inln);

return 0;
}



