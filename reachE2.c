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
  char *str; 
  char *cmnd; 
  struct Node *next;
}node;

typedef struct List{
  struct Node *head;
}list;

typedef struct Graph{
    
   struct List *vert;
   struct Graph *nextv;
}graph;

typedef struct Vert{
  char *vname;
  int vval;
  struct Vert *next;
}vert;

int status;
int numV;
int flag;

int sAlpha(char*);
void addv(graph*,char*);
void addvert(vert*,char*,struct Graph*);
void printG(graph*);
void printG2(graph*);
void printVlist(vert*);
void addedge(graph*,char*,char*);
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


  graph *grph=(graph*)malloc(sizeof(graph));
  grph->vert=(list*)malloc(sizeof(list));
  grph->vert->head=NULL;

/*  
  vert *verhead=malloc(sizeof(vert)); 
  verhead->vname=NULL; 
  verhead->vval=0;
  verhead->next=NULL; 
*/

  int *vtx=NULL;

  

   //  add vertex

   int c=1;
   char *str1="a";




     if(c==1){  

/*
         if(getindex(verhead,str)!=0){
          fprintf(stderr,"(2) Bad name selection\n");
          free(str);
          status=1;
          continue;}      
*/
   
          addv(grph,strdup(str1));

     } 


    char *str2="b";
    addv(grph,strdup(str2));

    char *str3="c";
    addv(grph,strdup(str3));



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


         
     char *str4="1";
     addedge(grph,str1,strdup(str4));
     
     char *str5="2";
     addedge(grph,str1,strdup(str5));



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

void addv(graph *grph, char *str){
  
  list *temp=(list*)malloc(sizeof(list)); 
  temp->head=malloc(sizeof(node));
  temp->head->str=str;
  temp->head->next=malloc(sizeof(node));
  graph *cur=grph;
  while(cur->nextv!=NULL){  
   cur=cur->nextv;}
    
   cur->vert=temp;
   cur->nextv=malloc(sizeof(graph));
   cur->nextv->vert=NULL;
}

/*
void addvert(char *name, struct Graph *graph){
  
  graph *cur=verhead;
  while(cur->next!=NULL){
     cur=cur->next;}
  
  cur->vval=numV;
  cur->vname=name;
  cur->next=malloc(sizeof(vert));
  cur->next->vname=NULL;
  cur->next->vval=0;
  cur->next->next=NULL;
 
 addlist(graph,numV); 


}
*/

void addedge(graph *grph, char *str1, char *str2){


//printf("no1");
  graph *cur=grph;
  while(cur->nextv!=NULL){
    if(strcmp(cur->vert->head->str,str1)==0){
     
//printf("no2");
     node *ndcur=cur->vert->head;
     while(ndcur->next!=NULL){
        ndcur=ndcur->next;}
     ndcur->str=str2;
     ndcur->next=malloc(sizeof(node));
     ndcur->next->str=NULL;
     ndcur->next->cmnd=NULL;
     ndcur->next->next=NULL;
    break;
    }
    cur=cur->nextv; 
  }  

}




void printG(graph *grph){

   graph *cur=grph; 
    
   while(cur->nextv!=NULL){ 
    node *ndcur=cur->vert->head; 
      while(ndcur->next!=NULL){ 
        printf("%s ", ndcur->str);
        ndcur=ndcur->next;  
     } 
 //    printf("%s ",cur->vert->head->str); 

  cur=cur->nextv;  
   
   printf("\n"); 
     } 


}


void printG2(graph *grph){

   if(grph->nextv==NULL){
     return;}
   graph *cur=grph; 
//printf("%s ",cur->vert->head->str); 

   node *ndcur=cur->vert->head; 
      while(ndcur->next!=NULL){ 
        printf("%s ", ndcur->str);
        ndcur=ndcur->next;  
      } 

    printf("\n"); 
 
   printG(grph->nextv);   



}


/*
void printVlist(vert *verhead){

  vert *cur=verhead;
  while(cur->next!=NULL){
  printf("%s %d\n",cur->vname, cur->vval);
  cur=cur->next;
  }

}

int getindex(vert *verthead, char *name){

  vert *cur=verthead;
  while(cur->next!=NULL){
  if(strcmp(cur->vname,name)==0){
   return cur->vval;}
  cur=cur->next;}
  return 0;

}

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
