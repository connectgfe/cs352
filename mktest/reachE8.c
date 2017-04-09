/*
* File: reachE8.c
* Author: Giulio Esposito
* Purpose: use a graph to find if nodes are connected
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funct.h"
#include "cs352.h"

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




   

void addlist(struct Graph *grph, char *str, vert *verhead){

  graph *cur=grph;
  while(cur->nextv!=NULL){
   cur=cur->nextv;}

   cur->ver->head=malloc(sizeof(node));
   if(cur->ver->head==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}
  cur->ver->head->name=str;
  cur->ver->head->ind=numV;
  cur->ver->head->next=malloc(sizeof(node));
  if(cur->ver->head->next==NULL){ myfree(verhead,grph); status=1; 
  fclose(fp); exit(1);}
 
  cur->ver->head->next->ind=0;
   cur->ver->head->next->name=NULL;
  cur->ver->head->next->next=NULL;

  cur->nextv=malloc(sizeof(graph));
 if(cur->nextv==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}
 
  cur->nextv->nextv=NULL; 
   cur->nextv->ver=(list*)malloc(sizeof(list));
  if(cur->nextv->ver==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}


  numV++;
}

void addvert(vert *verhead, char *name, graph *grph, int targ){


 
  vert *cur=verhead;
  while(cur->next!=NULL){
   if(strcmp(cur->vname,name)==0 && cur->targ==1 && targ==1){
      free(name);
   fprintf(stderr,"Error: Target assigned\n"); 
    exit(1);} 
    if(strcmp(cur->vname,name)==0 && targ==0){
      free(name);
    return;} 
    if(strcmp(cur->vname,name)==0 && targ==1){
     cur->targ=targ; 
     free(name);
    return;} 
        
   cur=cur->next;

   }
  
     cur->vind=numV;
     cur->vname=name;
     cur->targ=targ;
 
  cur->next=malloc(sizeof(vert));
  if(cur->next==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}

  cur->next->vname=NULL;
  cur->next->vind=0;
  cur->next->targ=0;
//  cur->next->cmd=NULL; 
   cur->next->cmd=(cmnd*)malloc(sizeof(cmnd));
   if(cur->next->cmd==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}

   cur->next->cmd->comnd=NULL;
   cur->next->cmd->nextc=NULL;

  cur->next->next=NULL;
   
 addlist(grph,name,verhead); 


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
   printf("%s %d %d\n",cur->vname, cur->vind, cur->targ);
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


void setcmnd(vert *verhead, char *name, char *command, graph *grph){

   vert *cur=verhead;
   while(cur->next!=NULL){
      if(strcmp(cur->vname,name)==0){
        cmnd *ccur=cur->cmd; 
          while(ccur->nextc!=NULL){ 
              ccur=ccur->nextc;} 
        ccur->comnd=command;
        ccur->nextc=(cmnd*)malloc(sizeof(cmnd));
        if(ccur->nextc==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}

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
     if(ndcur->next==NULL){ myfree(verhead,grph); status=1; fclose(fp);
    exit(1);}

     ndcur->next->name=NULL;
     ndcur->next->ind=0; 
     ndcur->next->next=NULL;
      
     break;
    }
    cur=cur->nextv;
  }

}

void settarg(vert *verhead, char *name){
   
     vert *cur=verhead;
     while(cur->next!=NULL){
      if(strcmp(cur->vname,name)==0){
        cur->targ=1;
        return;}
       cur=cur->next;
       }

}

void buildm(vert *verhead, struct Graph *grph,int *vtx,int target,int otrg){


//printf("no1\n");
   graph *gcur=grph;
   list *lcur=NULL; 
   node *cur=NULL;
   while(gcur->nextv!=NULL){
    if(gcur->ver->head->ind==target){
     
    lcur=gcur->ver;
    cur=lcur->head; 
//printf("no2 %d\n", cur->ind);

    break;}
    gcur=gcur->nextv;
   }
   if(gcur==NULL || cur==NULL) { return;}


//printf("(1) target: %d curind:%d vtx:%d\n",target,cur->ind,*(vtx+target));

  if(*(vtx+target)==0){
  return;}



 vert *vcur=verhead;
  while(vcur->next!=NULL){
  if(vcur->vind==cur->ind){ // && vcur->targ==0){

  *(vtx+target)=0; 
   break;
   }
   vcur=vcur->next;
   }

//printf("(2) target: %d curind:%d vtx:%d\n",target,cur->ind,*(vtx+target));

     while(cur->next!=NULL){
       target=cur->next->ind;
     // for cycles  
      if(target==otrg){
       vert *ncur=verhead;
        while(ncur->next!=NULL){
         if(strcmp(ncur->vname,lcur->head->name)==0){
            printf("%s\n",ncur->vname);
            cmnd *ccur=ncur->cmd;
             while(ccur->nextc!=NULL){
               printf("%s\n",ccur->comnd);
               ccur=ccur->nextc;
             }
          }
         ncur=ncur->next;
       }

       return;} 
       
       buildm(verhead,grph,vtx,target,otrg);
       cur=cur->next;
       }

 vert *ncur=verhead;
    
     while(ncur->next!=NULL){
         if(strcmp(ncur->vname,lcur->head->name)==0){
            printf("%s\n",ncur->vname);
            cmnd *ccur=ncur->cmd;
             while(ccur->nextc!=NULL){
               printf("%s\n",ccur->comnd);
               ccur=ccur->nextc;
             }
          }
         ncur=ncur->next;
       }

//printf("(3) target: %d curind:%d vtx:%d\n",target,cur->ind,*(vtx+target));

}

int istarg(vert *verhead,char *tar){

   vert *cur=verhead;
   while(cur->next!=NULL){
     if(strcmp(cur->vname,tar)==0 && cur->targ==1){
        return cur->vind;
         }
      cur=cur->next;
    }
    return 0;
} 
