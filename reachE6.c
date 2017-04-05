/*
* File: reach.c
* Author: Giulio Esposito
* Purpose: use a graph to find if nodes are connected
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funct.h"

/*
typedef struct Node{
  int ind;
  char *name; 
  struct Node *next;
}node;

typedef struct List{
  struct Node *head;
}list;

typedef struct Graph{
  
  struct List *ver;
  struct Graph *nextv;
}graph;

typedef struct Vert{
  char *vname;
  int vind;  
  struct Cmnd *cmd;
  struct Vert *next;
}vert;

typedef struct Cmnd{
  char *comnd;
  struct Cmnd *nextc;
}cmnd;

int status;
int numV;
int flag;
int mrkr;


void addlist(struct Graph*,char*);
void addvert(vert*,char*,struct Graph*);
void printG2(struct Graph*);
void printVlist(vert*);
void addedge2(vert*,struct Graph*,char*,char*);
int getindex(vert*,char*);
void isconn(struct Graph*,int*,int,int);
void setcmnd(vert*,char*,char*);
int graph(char *str1,char*str2,int c){
*/

int status;
int numV;
int flag;
int mrkr;



void buildgraph(char *str1, char *str2, int mrkr ){
  status=0;
  numV=1;
  flag=0; 

/*
    addvert(verhead,strdup(str1),grph);

    addvert(verhead,strdup(str2),grph);
*/



/*
  graph *grph=malloc(sizeof(struct Graph));
  grph->ver=(list*)malloc(sizeof(list));
  grph->ver->head=NULL;
  grph->nextv=NULL;  


  
  vert *verhead=malloc(sizeof(vert)); 
  verhead->vname=NULL; 
  verhead->vind=0;
  verhead->next=NULL; 
  verhead->cmd=(cmnd*)malloc(sizeof(cmnd));
  verhead->cmd->comnd=NULL;
  verhead->cmd->nextc=NULL;
  

//  int *vtx=NULL;

  

   //  add vertex

   int c=1;
   char *str1="a";
   char *str2="b";
   char *str3="c";
   char *str4="d";
   char *str5="e";

     
    addvert(verhead,strdup(str1),grph,NULL);


    addvert(verhead,strdup(str2),grph,NULL);
    addvert(verhead,strdup(str3),grph,NULL);
    addvert(verhead,strdup(str4),grph,NULL);
    addvert(verhead,strdup(str5),grph,NULL);


printVlist(verhead);



     addedge2(verhead,grph,str1,str2);

     addedge2(verhead,grph,str1,str3);

     addedge2(verhead,grph,str1,str4);

     addedge2(verhead,grph,str3,str2);



printG2(grph);

*/


/*
         if(getindex(verhead,str)!=0){
          fprintf(stderr,"(2) Bad name selection\n");
          free(str);
          status=1;
          continue;}      
*/
   


     // add edge

 
/*              
        if(getindex(verhead,str)==0 || getindex(verhead,str2)==0){
           fprintf(stderr,"Error: bad edge assign\n");
           status=1;
           free(str);
           free(str2);
           free(op);
           continue;}
*/ 
         

      // check isconnected

/*  
       int i;
        vtx=(int*)malloc(numV*sizeof(int)); 
        for(i=0;i<numV;i++){
          *(vtx+i)=(i);
         } 
     
      str=(char*)malloc(64*sizeof(char)); 
      str2=(char*)malloc(64*sizeof(char)); 
 
      
       if(getindex(verhead,str)==0 || getindex(verhead,str2)==0){
           fprintf(stderr,"Error: bad path attempt\n");
           status=1;
           free(str);
           free(str2);           
           free(op); 
           free(vtx);
            vtx=NULL;
           
            continue;}
        
         if(strcmp(str,str2)==0){

          flag=1;
            printf("%d\n",flag); 
           flag=0;
           }

 
         isconn(graph,vtx,getindex(verhead,str),getindex(verhead,str2));
           printf("%d\n",flag); 
           flag=0;
      
         free(str);
         free(str2); 
         free(vtx);
*/   


/*
// free vertlist
   
    vert *tempv;
     while(verhead!=NULL){
       tempv=verhead;
       verhead=verhead->next;
          
       free(tempv->vname);  

           if(tempv->cmd!=NULL){
            cmnd *tempc;
              while(tempv->cmd!=NULL){
                 tempc=tempv->cmd;
                 tempv->cmd=tempv->cmd->nextc;
                 free(tempc->comnd);
                 free(tempc);
              } 
          } 


       free(tempv->cmd); 
       free(tempv);
      }



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
*/
    
}

void addlist(struct Graph *grph, char *str){

  graph *cur=grph;
  while(cur->nextv!=NULL){
   cur=cur->nextv;}

   cur->ver->head=malloc(sizeof(node));
  cur->ver->head->name=str;
  cur->ver->head->ind=numV;
  cur->ver->head->next=malloc(sizeof(node));
   cur->ver->head->next->ind=0;
   cur->ver->head->next->name=NULL;
  cur->ver->head->next->next=NULL;

  cur->nextv=malloc(sizeof(graph));
   cur->nextv->nextv=NULL; 
   cur->nextv->ver=(list*)malloc(sizeof(list));
   

  numV++;
}

void addvert(vert *verhead, char *name, graph *grph){


 
  vert *cur=verhead;
  while(cur->next!=NULL){
   if(strcmp(cur->vname,name)==0){
      free(name);
       return;}
       cur=cur->next;}
  
     cur->vind=numV;
     cur->vname=name;
/*
    if(cur->cmd==NULL){    
    cur->cmd=(cmnd*)malloc(sizeof(cmnd));
    cur->cmd->comnd=NULL;
    cur->cmd->nextc=NULL;}
*/
 
  cur->next=malloc(sizeof(vert));
  cur->next->vname=NULL;
  cur->next->vind=0;
//  cur->next->cmd=NULL; 
   cur->next->cmd=(cmnd*)malloc(sizeof(cmnd));
   cur->next->cmd->comnd=NULL;
   cur->next->cmd->nextc=NULL;

  cur->next->next=NULL;
   
 addlist(grph,name); 


}


void printG2(graph *grph){

   graph *cur=grph;

   while(cur->nextv!=NULL){
    node *ndcur=cur->ver->head;
      while(ndcur->next!=NULL){
        printf("%d ", ndcur->ind);
        ndcur=ndcur->next;
     }
 //    printf("%s ",cur->vert->head->str); 

  cur=cur->nextv;

   printf("\n");
     }


}


void printVlist(vert *verhead){

  vert *cur=verhead;
  while(cur->next!=NULL){
   printf("%s %d\n",cur->vname, cur->vind);
    cmnd *ccur=cur->cmd;
      while(ccur->nextc!=NULL){
          printf("%s\n",ccur->comnd);
          ccur=ccur->nextc;} 
   // need to print cmnds too 
  cur=cur->next;
  }

}

int getindex(vert *verthead, char *name){

  vert *cur=verthead;
  while(cur->next!=NULL){
  if(strcmp(cur->vname,name)==0){
   return cur->vind;}
  cur=cur->next;}
  return 0;

}

void setcmnd(vert *verhead, char *name, char *command){

   vert *cur=verhead;
   while(cur->next!=NULL){
      if(strcmp(cur->vname,name)==0){
        cmnd *ccur=cur->cmd; 
          while(ccur->nextc!=NULL){ 
              ccur=ccur->nextc;} 
        ccur->comnd=command;
        ccur->nextc=(cmnd*)malloc(sizeof(cmnd));
        ccur->nextc->comnd=NULL;  
        ccur->nextc->nextc=NULL; 
        break; 
         }
  cur=cur->next;}

}

char *getcmnd(vert *verhead, char *name){

   vert *cur=verhead;
   while(cur->next!=NULL){
      if(strcmp(cur->vname,name)==0){
        if(cur->cmd->comnd!=NULL){ 
        return cur->cmd->comnd;}
         }
  cur=cur->next;
     }
    return "no command";
}
/*
void isconn(struct Graph *graph,int *vtx,int ptA,int ptB){

  node *cur=graph->arr[ptA].head;
//printf("ptA:%d ptB:%d curind:%d vtx:%d\n",ptA,ptB,cur->ind,*(vtx+ptA));
  if(*(vtx+ptA)==0){return;}
  *(vtx+ptA)=0; 

  while(cur->next!=NULL){
 int nptA=cur->next->ind;
//printf("nptA:%d nvtx:%d\n",nptA,*(vtx+nptA));
    if(*(vtx+nptA)==0 && nptA!=0){
       cur=cur->next; 
       nptA=cur->next->ind;
     }
   if(nptA==0){
     return ;}
   if(nptA==ptB){ 
   flag=1; 
   return ;} 
   isconn(graph,vtx,nptA,ptB);
   cur=cur->next;
   }
}


*/

void addedge2(vert *verhead, graph *grph, char *str1, char *str2){

 int v=getindex(verhead,str1);
 int edg=getindex(verhead,str2);
//printf("no1");
  graph *cur=grph;
  while(cur->nextv!=NULL){
    if(cur->ver->head->ind == v){

//printf("no2");
     node *ndcur=cur->ver->head;
     while(ndcur->next!=NULL){
        ndcur=ndcur->next;}
     ndcur->ind=edg;
     ndcur->next=malloc(sizeof(node));
     ndcur->next->name=NULL;
     ndcur->next->ind=0; 
     ndcur->next->next=NULL;
      
     break;
    }
    cur=cur->nextv;
  }

}

