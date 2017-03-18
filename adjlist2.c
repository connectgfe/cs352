#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  int ind;
  int weight; 
  struct Node *next;
}node;

typedef struct List{
  struct Node *head;
}list;

struct Graph{
  int numofV;
  struct List *arr;
};

typedef struct Vert{
  char *vname;
  int vval;
  struct Vert *next;
}vert;

int status;
int numV;
int flag;
void addlist(struct Graph*,int);
void addvert(vert*,char*,struct Graph*);
void printG(struct Graph*);
void printVlist(vert*);
void addedge(vert*,struct Graph*,char*,char*);
int getindex(vert*,char*);
void isconn(struct Graph*,int*,int,int);
void frVlist(vert*);

int main(){
  status=0;
  numV=1;
  flag=0; 
  struct Graph *graph=malloc(sizeof(struct Graph));
  vert *verhead=malloc(sizeof(vert)); 
  graph->arr=(list*)malloc(sizeof(list));

 // char **line=(char**)malloc(sizeof(char*));
  size_t len=0; 
  int j=0; 
  int val=0;
  char *names="@n";
  char *edjes="@e";
  char *path ="@q";

/* 
  while(val>=0){
   val=getline(&*(line+j),&len,stdin);

      char *op=(char*)malloc(64*sizeof(char)); 
      sscanf(*(line+j),"%s",op);
    //  printf("this is op %s",op);
      *(line+j)+=strlen(op);  
      // check if op is legal       

      char *str=(char*)malloc(64*sizeof(char)); 
      int offset=0; 
      
      while(sscanf(*(line+j),"%s%n",str,&offset)==1){
        if(strcmp(op,names)==0){ 
        printf("%s\n",str); 
        addvert(verhead,strdup(str),graph);}  
        *(line+j)+=offset;
       // printf("%s\n",str); 
        free(str);     
        str=(char*)malloc(64*sizeof(char)); 
      }
//   printf("%s",*(line+j));
 
   j++;
   line=(char**)realloc(line,(1+j)*sizeof(char*));  
   *(line+j)=(char*)malloc(1024*sizeof(char));   
   len=0; 
   }
  
  
*/


  char *v1name="John"; 
  addvert(verhead,v1name,graph);  

  char *v2name="Ed"; 
  addvert(verhead,v2name,graph);  


  char *v3name="Phil"; 
  addvert(verhead,v3name,graph);  
  char *v4name="Steve";
  addvert(verhead,v4name,graph);
  char *v5name="Dan";
  addvert(verhead,v5name,graph);
  char *v6name="Ben";
  addvert(verhead,v6name,graph);


//  printG(graph); 
//  printVlist(verhead);

  addedge(verhead,graph,v1name,v2name); 
  addedge(verhead,graph,v2name,v1name); 

  addedge(verhead,graph,v3name,v1name); 
  addedge(verhead,graph,v3name,v2name); 
  addedge(verhead,graph,v3name,v4name); 
  addedge(verhead,graph,v1name,v2name); 
  addedge(verhead,graph,v2name,v4name); 
  addedge(verhead,graph,v4name,v5name); 
  addedge(verhead,graph,v5name,v3name); 
  addedge(verhead,graph,v3name,v6name); 
  printG(graph);

 // printf("%d\n",getindex(verhead,"Ben"));

  int i;

  int *vtx=(int*)malloc(numV*sizeof(int)); 
  for(i=0;i<numV;i++){
    *(vtx+i)=i;} 
  
 printVlist(verhead);

   free(vtx);

// free Vlist
    vert *temp;
      while(verhead!=NULL){
        temp=verhead;
       verhead=verhead->next; 
        free(temp);     
      } 
// free graph   
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
//  isconn(graph,vtx,1,2);
//  printf("flagval %d\n",flag);
 
     

//  printG(graph); 
   

// printVlist(verhead);


  return status;


}

void addlist(struct Graph *graph, int val){
  
  graph->arr=(list*)realloc(graph->arr,(numV+1)*sizeof(list));
  // must realloc 
  graph->arr[numV].head=malloc(sizeof(node));
  graph->arr[numV].head->ind=val;
  graph->arr[numV].head->next=malloc(sizeof(node)); 
  numV++;
}

void addvert(vert *verhead, char *name, struct Graph *graph){
  
  vert *cur=verhead;
  while(cur->next!=NULL){
     cur=cur->next;}
  
  cur->vval=numV;
  cur->vname=name;
  cur->next=malloc(sizeof(vert));
  addlist(graph,numV); 


}

void addedge(vert *verhead, struct Graph *graph, char *n1, char *n2){

  int v, vadd;
  vert *cur=verhead;
  while(cur->next!=NULL){
    if(strcmp(cur->vname,n1)==0){
    v=cur->vval;}
    if(strcmp(cur->vname,n2)==0){
    vadd=cur->vval;}
    cur=cur->next;}

//  printf("%s %d %s %d\n",n1,v,n2,vadd);

  node *cur2=graph->arr[v].head;
  while(cur2->next!=NULL){
  cur2=cur2->next;
  }
  cur2->ind=vadd;
  cur2->next=malloc(sizeof(node));
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
  
//  printf("vtx %d\n",*(vtx+ptA)); 
  *(vtx+ptA)=0; 
  while(cur->next!=NULL){
  int nptA=cur->next->ind;
    if(*(vtx+nptA)==0 && nptA!=0){
 //      printf("here\n"); 
       cur=cur->next; 
       nptA=cur->next->ind;
     }
  // printf("%d\n",nptA);  
   if(nptA==0){
     return ;}
   if(nptA==ptB){ printf("found\n"); flag=1; return ;} 
   
   isconn(graph,vtx,nptA,ptB);
   cur=cur->next;
   }

}

void frVlist(vert *verhead){
   printf("no1\n");
   
   if(verhead->next==NULL){
     printf("no2\n");
 
     free(verhead);
     return;}

   vert *cur=verhead;
   while(cur->next!=NULL){
     printf("%s %p\n",cur->vname,cur);
     
     cur=cur->next;
    
    printf("no3\n");
 
    }
//    printf("%p\n",cur->next); 
   printf("no4\n");
 
    //printf("freed next of %s\n",cur->vname);
    

    free(cur->next); 

     printf("no5\n");
  
//   frVlist(verhead);
   printf("no6\n");

}

