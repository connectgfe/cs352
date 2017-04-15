/*
* File: myreach.c
* Author: Giulio Esposito
* Purpose: create a makefile
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
#include "cs352.h"

int goodline;
int status;
int numV;
int flag;
FILE *fp;
char *testln;

void myfree(vert*,struct Graph*);


int main(int argc, char **argv){

  fp=NULL;
  testln=NULL;
  char *targ=NULL;
  int *vtx=NULL;
  status=0;
  size_t ln=0;
  numV=1;
  flag=0;

  struct dirent **dirlist;
  struct stat sb;
  int val1=0;
  int lnval=0;
  int mkindir=0;
  int lncnt=1;
 
  if(argc==1){

    val1 = scandir(".", &dirlist,NULL,alphasort);
      while(val1--){
        if(strcmp(dirlist[val1]->d_name,"Makefile")){
         stat("Makefile",&sb);
//         printf("faccess Makefile: %s",ctime(&sb.st_atime)); 
//         printf("fstatus Makefile: %s",ctime(&sb.st_ctime));    
//         printf("fmod Makefile:    %s",ctime(&sb.st_mtime));
         mkindir=1;
         break;
        }
      }

     if(mkindir==0){
       fprintf(stderr,"Error: No Makefile in dir\n");
       status =1; return status;}

     fp=fopen("Makefile", "r");
  }

/*
//  change for >1
  if(argc>=1){

    fp=fopen(*(argv+1), "r");
      if(fp==NULL){
       fprintf(stderr,"Error with file\n");
      status=1;
      return status;    
      }

      if(argc==3){
        targ=*(argv+2);}else{
        fprintf(stderr,"Not enough args Error\n");
        fclose(fp);
       status=1;
       return status;  
       }


  }else{
   fprintf(stderr,"No File Error\n");
       status=1;
       return status;  
  } 
    
*/
 

  graph *grph=(graph*)cs352_malloc(sizeof(graph));
  if(grph==NULL){ status =1 ; fclose(fp); 
  fprintf(stderr,"Malloc failed (1)\n");
  return status;}
  grph->ver=(list*)cs352_malloc(sizeof(list));
  if(grph->ver==NULL){ status =1 ; fclose(fp); 
  fprintf(stderr,"Malloc failed (2)\n");  
  free(grph);
  return status;}
  grph->ver->head=NULL;
  grph->nextv=NULL;



  vert *verhead=(vert*)cs352_malloc(sizeof(vert));
  if(verhead==NULL){ status =1 ; free(grph->ver); free(grph);
     fclose(fp); 
  fprintf(stderr,"Malloc failed (3)\n");
  return status;}
  verhead->vname=NULL;
  verhead->vind=0;
  verhead->next=NULL;
  verhead->cmd=(cmnd*)cs352_malloc(sizeof(cmnd));
  if(verhead->cmd==NULL){ myfree(verhead,grph); status =1 ; fclose(fp); 
 fprintf(stderr,"Malloc failed (4)\n");    
 return status;}
  verhead->cmd->comnd=NULL;
  verhead->cmd->nextc=NULL;

    

    while(1){
      lnval=getline(&testln,&ln,fp);


      if(lnval==1){ continue;}
//printf("%d\n",val); 
      if(lnval==-1){  break;} 
     
     char *line1;
     char *line2;
     char first[64];
     char second[64];
     char sec2[64];
     int offset=0;
     int offset2=0;
     int fset1=0;
     int fset2=0;
     int cnt1=0;
     char str1[64];
     char str2[64];
// printf("no1\n"); 
     
      if(*testln=='\t' ){
        char *t1=testln;
        t1++;

        size_t lenc=strlen(t1);
        char temp2[lenc+1]; 
        strcpy(temp2,t1);
        temp2[lenc-1]='\0'; 
        char temp3[1024]="  ";
        strcat(temp3,temp2);
        setcmnd(verhead,first,cs352_strdup(temp3),grph);
//printf("no2\n"); 
        lncnt++; 
        continue; 
        } 

     int mkr1=0;
     int mkr2=0;

    sscanf(testln,"%64s%n",str1,&offset);
    char *nxtestln=testln;
    nxtestln+=offset;
//printf("%s %s\n",testln,nxtestln); 
    char *temp1=str1;
    size_t ln1=strlen(temp1);


    while(*temp1){
      if(*temp1==':'){
        if(cnt1==0 || cnt1==(ln1-1)){
         str1[cnt1]=' ';
         line1=str1;
//printf("%s %s\n",str1,line1);
         sscanf(line1,"%64s%n",first,&fset1);
//printf("%s\n",first);
         cnt1=0;
         mkr1=1;
         break;
      }else{
//printf("cnt: %d str: %lu",cnt,ln); 
     str1[cnt1]=' ';
     line1=str1;
//printf("%s %s\n",str1,line1);
      sscanf(line1,"%64s%n%64s%n",first,&fset1,sec2,&fset2);
         mkr1=2;
         cnt1=0;
//printf("%s %s\n",first,sec2);
     }}
     temp1++;
     cnt1++;
    }



// if mkr1==2 settarg first and add sec2 as dep send nxtestln loop
     if(mkr1==2){
     
     //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
       targ=cs352_strdup(first);}
       

       addvert(verhead,cs352_strdup(first),grph,1); 
       addvert(verhead,cs352_strdup(sec2),grph,0); 
       addedge2(verhead,grph,first,sec2);

// printf("case1 a:b first:%s sec2:%s %s\n",first,sec2,nxtestln);
     }
// if mkr1==1 settarg first and send nxtestln to loop 
    if(mkr1==1){
    //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
       targ=cs352_strdup(first);}
      

    addvert(verhead,cs352_strdup(first),grph,1); 
// printf("case2 a: b first:%s nxt:%s\n",first,nxtestln);
    }

// if mkr1==0 check for : using below

    if(mkr1==0){
      sscanf(nxtestln,"%64s%n",str2,&offset2);

      char *temp2=str2;


      if(strcmp(temp2,":")==0){
   
   //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
       targ=cs352_strdup(first);}   
       
// settarg str1 moveup by offset2 nxtestln and send to loop 
      strcpy(first,str1);

      addvert(verhead,cs352_strdup(first),grph,1); 

      nxtestln+=offset2;
      mkr2=1;
//printf("case3 a : b  str1:%s nxt:%s\n",str1,nxtestln);

     }else{

     if(*temp2==':'){
         str2[0]=' ';
         line2=str2;
         sscanf(line2,"%64s%n",second,&fset1);
         nxtestln+=offset2;
         mkr2=2;

      }
     }
    }

    if(mkr2==2){
      strcpy(first,str1); 
       //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
       targ=cs352_strdup(first);}
      
      addvert(verhead,cs352_strdup(first),grph,1); 
       addvert(verhead,cs352_strdup(second),grph,0); 
       addedge2(verhead,grph,first,second);

// settarg str1 moveup nxtestln by fset1 and send to loop
//printf("case4 a :b str1%s secnd:%s nxt:%s\n",str1,second,nxtestln);

     }

    if(mkr2==0 && mkr1==0){
      fprintf(stderr,"Error improper format\n");
      status=1;
      myfree(verhead,grph);  

      if(vtx!=NULL){  
      free(vtx);}


      if(fp!=NULL){
      fclose(fp);}

      free(testln);

 
      return status;} 

    mkr1=0;
    mkr2=0;



      char temp[64];
      int offset3=0;

      while(sscanf(nxtestln,"%64s%n",temp,&offset3)==1){

       addvert(verhead,cs352_strdup(temp),grph,0);
       addedge2(verhead,grph,first,temp);

       nxtestln+=offset3;

       }

    lncnt++;
   }

   int i;
   vtx=(int*)cs352_malloc(numV*sizeof(int)); 
   if(vtx==NULL){ myfree(verhead,grph); status =1 ; 
   fprintf(stderr,"Malloc failed (15)\n");
    fclose(fp); 
    free(testln); 
    return status;}

// printf("numV: %d\n",numV); 
   for(i=0;i<numV;i++){
       *(vtx+i)=(i+1);
//  printf("%d\n",*(vtx+i));    
   }

// exit(0); 
/*
    printf("\ngraph \n");
   printG2(grph);
   printf("\nvlist \n");
   printVlist(verhead);  
*/



  int val2=istarg(verhead,targ);
  if(val2!=0){

   buildm(verhead,grph,vtx,val2,val2);
   }else{
   fprintf(stderr,"Not proper target\n");
   status=1;
  
   myfree(verhead,grph);  

    if(vtx!=NULL){  
     free(vtx);}


    if(fp!=NULL){
     fclose(fp);}

    free(testln);


    return status;
    }

   myfree(verhead,grph);  

    if(vtx!=NULL){  
     free(vtx);}


    if(fp!=NULL){
     fclose(fp);}

    free(testln);

return status;
}




void myfree(vert *verhead,graph *grph){
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


// free lists    
   graph *cur=grph; 
   while(cur->nextv!=NULL){
    node *temp;
     while(cur->ver->head!=NULL){
        temp=cur->ver->head;
        cur->ver->head=cur->ver->head->next;
       free(temp->name);  
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


  }
