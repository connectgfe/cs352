/*
* File: reach.c
* Author: Giulio Esposito
* Purpose: use a graph to find if nodes are connected
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int sAlpha(char*);
void addlist(struct Graph*,char*);

void addvert(vert*,char*,struct Graph*,char*);

void printG(struct Graph*);
void printG2(struct Graph*);
void printVlist(vert*);

void addedge(vert*,struct Graph*,char*,char*);
void addedge2(vert*,struct Graph*,char*,char*);

int getindex(vert*,char*);
void isconn(struct Graph*,int*,int,int);
int checkargs(char*);
int selfLoop(int,struct Graph*);
int isempty(char*);


//int graph(char *str1,char*str2,int c){
int main(){
  status=0;
  numV=1;
  flag=0; 


  graph *grph=malloc(sizeof(struct Graph));
  grph->ver=(list*)malloc(sizeof(list));
  grph->ver->head=NULL;
  
  vert *verhead=malloc(sizeof(vert)); 
  verhead->vname=NULL; 
  verhead->vind=0;
  verhead->next=NULL; 
  verhead->cmd=(cmnd*)malloc(sizeof(cmnd));
  verhead->cmd->comnd=NULL;
  verhead->cmd->nextc=NULL;
  

  int *vtx=NULL;

  

   //  add vertex

   int c=1;
   char *str1="a";
   char *str2="b";
   char *str3="c";
   char *str4="d";
   char *str5="e";

     
    addvert(verhead,str1,grph,NULL);
    addvert(verhead,str2,grph,NULL);
    addvert(verhead,str3,grph,NULL);
    addvert(verhead,str4,grph,NULL);
    addvert(verhead,str5,grph,NULL);


printVlist(verhead);



     addedge2(verhead,grph,str1,str2);

     addedge2(verhead,grph,str1,str3);

     addedge2(verhead,grph,str1,str4);

     addedge2(verhead,grph,str3,str2);



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
         

printG2(grph);
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
// free graph
   
    vert *temp;
     while(verhead!=NULL){
        temp=verhead;
       verhead=verhead->next;
       free(temp->vname);  
       free(temp);
      }


    int i;
    for(i=0;i<numV;i++){
    node *temp;
     while(graph->arr[i].head!=NULL){
        temp=graph->arr[i].head;
        graph->arr[i].head=graph->arr[i].head->next;
        free(temp);
     }
    }


    free(verhead);
    free(graph->arr);

    free(graph); 
*/
    
     return status;


}

void addlist(struct Graph *grph, char *str){


  list *temp=(list*)malloc(sizeof(list));
  temp->head=malloc(sizeof(node));
  temp->head->name=str;
  temp->head->ind=numV;
  temp->head->next=malloc(sizeof(node));
   temp->head->next->ind=0;
 temp->head->next->name=NULL;
  temp->head->next->next=NULL;
 graph *cur=grph;
  while(cur->nextv!=NULL){
   cur=cur->nextv;}

   cur->ver=temp;
   
   cur->nextv=malloc(sizeof(graph));
   cur->nextv->ver=NULL;
   

/*  
  graph->arr=(list*)realloc(graph->arr,(numV+1)*sizeof(list));
  graph->arr[numV].head=malloc(sizeof(node));
  graph->arr[numV].head->ind=val;
  graph->arr[numV].head->cmnd=NULL;
  
  graph->arr[numV].head->next=malloc(sizeof(node)); 
  graph->arr[numV].head->next->ind=0;
  graph->arr[numV].head->next->cmnd=NULL;
  graph->arr[numV].head->next->next=NULL;
*/
  numV++;
}

void addvert(vert *verhead, char *name, graph *grph, char *com){

  
  vert *cur=verhead;
  while(cur->next!=NULL){
     cur=cur->next;}
  
  cur->vind=numV;
  cur->vname=name;
 
  if(com!=NULL){
    cmnd *ccur=cur->cmd; 
    while(ccur->nextc!=NULL){
        ccur=ccur->nextc;}
    ccur->comnd=com;
    ccur->nextc=(cmnd*)malloc(sizeof(cmnd));
    ccur->nextc->nextc=NULL;}  

  cur->next=malloc(sizeof(vert));
  cur->next->vname=NULL;
  cur->next->vind=0;
  cur->next->cmd=NULL; 
  cur->next->next=NULL;
   
 addlist(grph,name); 


}

/*
void addedge(vert *verhead, graph *grph, char *n1, char *n2){

  int v, vadd;
  vert *cur=verhead;
  while(cur->next!=NULL){
    if(strcmp(cur->vname,n1)==0){
    v=cur->vval;}
    if(strcmp(cur->vname,n2)==0){
    vadd=cur->vval;}
    cur=cur->next;}


  node *cur2=graph->arr[v].head;
  while(cur2->next!=NULL){
  cur2=cur2->next;
  }
  cur2->ind=vadd;
  cur2->next=malloc(sizeof(node));
  cur2->next->ind=0;
  cur2->next->cmnd=NULL;
  cur2->next->next=NULL;
}




void printG(struct Graph *graph){

  int i;
  for(i=1;i<numV;i++){
    
    node *cur=graph->arr[i].head;
    while(cur->next!=NULL){ 
    printf("%d ", cur->ind);
    cur=cur->next;  
    }
    printf("\n"); 
    }
}

*/

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


int checkargs(char *line){

    char *temp=line;
    int cnt=0; 
    int offset=0;
    char *str=(char*)malloc(64*sizeof(char));

    while( sscanf(temp,"%s%n",str,&offset)==1){
       temp+=offset;
      cnt++;
   free(str);
    str=(char*)malloc(64*sizeof(char));
    if(cnt>1027){break;}
    }
    free(str);
    
    return cnt;

}

int sAlpha(char *str){

  int size=strlen(str);
   int cnt=0;

   while(*str){
    if(isalpha(*str)!=0){
    cnt++;
    }
   if(isdigit(*str)!=0){
    cnt++;
    }
   str++;
  }


  if(cnt!=size){
    return 1;
  }


return 0;
}


int selfLoop(int pos, struct Graph *graph){
    node *cur=graph->arr[pos].head;
    int cnt=0;
    while(cur->next!=NULL){
     if(cur->ind==pos){cnt++;}
     cur=cur->next;}
     if(cnt>=2){return 1;}

     return 0;

}

int isempty(char *str){
   size_t len1=strlen(str);
   int cnt=0;
   while(*str){

   if(*str==' '){
   cnt++;}
   str++;
   }
  if(cnt==(len1-1)){return 1;}
  return 0;
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

