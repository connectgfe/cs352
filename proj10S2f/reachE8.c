/*
* File: reachE8.c
* Author: Giulio Esposito
* Purpose: use a graph to find if nodes are connected
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

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
  int targ;
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
void setcmnd(vert*,char*,char*);
int graph(char *str1,char*str2,int c){
*/

int status;
int numV;
int flag;
int mrkr;
char *testln;   
int retval;
struct stat sb1;
struct stat sb2;
int mkcmnd;
int retval2;
char *prcmnd;


void addlist(struct Graph *grph, char *str, vert *verhead){

  graph *cur=grph;
  while(cur->nextv!=NULL){
   cur=cur->nextv;}

   cur->ver->head=malloc(sizeof(node));

  cur->ver->head->name=strdup(str);
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

void addvert(vert *verhead, char *name, graph *grph, int targ){


  vert *cur=verhead;
  while(cur->next!=NULL){
   if(strcmp(cur->vname,name)==0 && cur->targ==1 && targ==1){
  
    free(name);
   fprintf(stderr,"Error: Target assigned\n"); 
   myfree(verhead,grph); 
   fclose(fp); 
   free(testln);
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
     cur->edgeof=(int*)calloc(25,sizeof(int)); 
  cur->next=malloc(sizeof(vert));

  cur->next->vname=NULL;
  cur->next->vind=0;
  cur->next->targ=0;
  cur->next->edgeof=NULL;

//  cur->next->cmd=NULL; 
   cur->next->cmd=(cmnd*)malloc(sizeof(cmnd));

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

          printf("edge of: %d %d %d\n",*(cur->edgeof),*(cur->edgeof+1),*(cur->edgeof+2));

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
 

        ccur->nextc->comnd=NULL;  
        ccur->nextc->nextc=NULL; 
        break; 
         }
  cur=cur->next;}

}


/*
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
*/

void addedge2(vert *verhead, graph *grph, char *str1, char *str2){

 int v=getindex(verhead,str1);
 int edg=getindex(verhead,str2);

 vert *vcur=verhead;
 while(vcur->next!=NULL){

   if(strcmp(vcur->vname,str2)==0){

//   vcur->edgeof=v;
//   break;

    
     int i;
     for(i=0;i<25;i++){
        if(*(vcur->edgeof+i)==0){
        *(vcur->edgeof+i)=v;
//       printf("the vert of %d: %d\n",edg,*(vcur->edgeof+i));
        break;}
      }



   }
   vcur=vcur->next;
 }


// add edge info to vert

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

/*
void settarg(vert *verhead, char *name){
   
     vert *cur=verhead;
     while(cur->next!=NULL){
      if(strcmp(cur->vname,name)==0){
        cur->targ=1;
        return;}
       cur=cur->next;
       }

}
*/

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
   if(*(vtx+target)==0 && target!=0){
     cur=cur->next;
     target=cur->next->ind;}     

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
   //        printf("edgeof:%d\n",*ncur->edgeof);
          

 
           int j=0;
           if(*(ncur->edgeof+j)==0){
           vert *tempncur=verhead;
printf("no1\n");
           stat(ncur->vname,&sb1);
            stat(tempncur->vname,&sb2); 
            double diff=difftime(sb2.st_atime,sb1.st_atime);    

printf("cur:%s curtar:%d edgof:%d temp:%s diff:%f\n",ncur->vname,ncur->targ,*ncur->edgeof,tempncur->vname,diff);
             if(mkcmnd!=0){ 
     
              if(strcmp(prcmnd,tempncur->cmd->comnd)!=0){

      //    if(diff==0){ 
printf("no1b\n");           
              strcpy(prcmnd,tempncur->cmd->comnd);
            retval=system(prcmnd);
             printf("%s\n",prcmnd);

            mkcmnd++;  
            }            
            } 

/*
               strcpy(prcmnd,tempncur->cmd->comnd);
            retval=system(prcmnd);
             printf("%s\n",prcmnd);

            mkcmnd++;  


*/
            } 
           
          if(*(ncur->edgeof+j)!=0){
printf("no2\n");
           for(j=3;j>-1;j--){
            if(*(ncur->edgeof+j)==0){
             continue;
            }          
          // int ed= *(ncur->edgeof+j);         
              
           vert *tempncur=verhead;
     //   printf("edge :  %d\n",*(ncur->edgeof+j));
           int i;
           for(i=0;i<(*(ncur->edgeof+j)-1);i++){
                tempncur=tempncur->next;
           } 
//          printf("%s\n",ncur->vname);
//            printf("cur:%s curtar:%d edgof:%d temp:%s\n",ncur->vname,ncur->targ,*ncur->edgeof,tempncur->vname);
            stat(ncur->vname,&sb1);
            stat(tempncur->vname,&sb2); 
            double diff=difftime(sb2.st_atime,sb1.st_atime);    
          printf("diff: %f %s %s\n",diff,tempncur->vname,ncur->vname);

printf("no2b\n");
            if(diff<0){ 
 printf("no2c\n");          
       //     if(strcmp(prcmnd,"0")==0){
              strcpy(prcmnd,tempncur->cmd->comnd);
            retval=system(prcmnd);
             printf("%s\n",prcmnd);

            mkcmnd++;  
      //     continue;
            }   


/*            
            if(strcmp(prcmnd,tempncur->cmd->comnd)==0){
      //        continue;
            }else{ 
           strcpy(prcmnd,tempncur->cmd->comnd);
             retval=system(prcmnd);
             printf("%s\n",prcmnd);

            mkcmnd++;  
             }
*/
      //        mkcmnd++;  
/*
             cmnd *ccur=ncur->cmd;
             while(ccur->nextc!=NULL){

             retval=system(ccur->comnd);
               
             printf("%s\n",ccur->comnd);
              ccur=ccur->nextc;
             }
*/            
                      
         }
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
