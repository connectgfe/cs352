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

int goodline;
int status;
int numV;
int flag;
FILE *fp;
char *testln;
char *targ;
char *prcmnd;


void myfree(vert*,struct Graph*);


int main(int argc, char **argv){

  fp=NULL;
  testln=NULL;
  targ=NULL;
  int *vtx=NULL;
  status=0;
  size_t ln=0;
  numV=1;
  flag=0;
  mkcmnd=0;
  prcmnd=(char*)malloc(1024*sizeof(char));
  strcpy(prcmnd,"0");

  struct dirent **dirlist;
  struct stat sb;
  int val1=0;
  int freeval1=0; 
  int lnval=0;
  int mkindir=0;
  int lncnt=1;
 
  if(argc==1){
//printf("no1");
    val1 = scandir(".", &dirlist,NULL,alphasort);
    freeval1=val1;  
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
       fprintf(stderr,"Error: No Makefile in dir(1)\n");
     while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
       status =1; return status;}

     fp=fopen("Makefile", "r");
  }


// only target given  
  if(argc==2){

     val1 = scandir(".", &dirlist,NULL,alphasort);
   freeval1=val1; 
     while(val1--){
        if(strcmp(dirlist[val1]->d_name,"Makefile")==0){
         stat("Makefile",&sb);
//         printf("faccess Makefile: %s",ctime(&sb.st_atime)); 
//         printf("fstatus Makefile: %s",ctime(&sb.st_ctime));    
//         printf("fmod Makefile:    %s",ctime(&sb.st_mtime));
         mkindir=1;
         break;
        }
      }

     if(mkindir==0){
       fprintf(stderr,"Error: No Makefile in dir(2)\n");
     while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
       status =1; return status;}

     fp=fopen("Makefile", "r");
    mkindir=0;

    targ=strdup(*(argv+1));
    }

  if(argc==3){

   if(strcmp(*(argv+1),"-f")==0){
   val1 = scandir(".", &dirlist,NULL,alphasort);
   freeval1=val1;  
    while(val1--){
        if(strcmp(dirlist[val1]->d_name,*(argv+2))==0){
         stat(*(argv+2),&sb);
//         printf("faccess Makefile: %s",ctime(&sb.st_atime)); 
//         printf("fstatus Makefile: %s",ctime(&sb.st_ctime));    
//         printf("fmod Makefile:    %s",ctime(&sb.st_mtime));
         mkindir=1;

         break;
        }
      }

     if(mkindir==0){
       fprintf(stderr,"Error: Makefile given not in dir(1)\n");
      while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
     status =1; return status;}

     fp=fopen(*(argv+2), "r");

   }else{
   fprintf(stderr,"Error: Not proper file assign\n");
     while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
       status =1; return status;}
//note: targ in makefile so use mkindir to set targ     
  }

  if(argc==4){

   if(strcmp(*(argv+1),"-f")==0){
    val1 = scandir(".", &dirlist,NULL,alphasort);
    freeval1=val1;  
    while(val1--){
        if(strcmp(dirlist[val1]->d_name,*(argv+2))==0){
         stat(*(argv+2),&sb);
//         printf("faccess Makefile: %s",ctime(&sb.st_atime)); 
//         printf("fstatus Makefile: %s",ctime(&sb.st_ctime));    
//         printf("fmod Makefile:    %s",ctime(&sb.st_mtime));
         mkindir=1;
         break;
        }
      }

     if(mkindir==0){
       fprintf(stderr,"Error: Makefile given not in dir(2)\n");
      while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
      status =1; return status;}

     fp=fopen(*(argv+2), "r");
     mkindir=0;
     targ=strdup(*(argv+3));

   }else if(strcmp(*(argv+2),"-f")==0){
    val1 = scandir(".", &dirlist,NULL,alphasort);
    freeval1=val1;  
    while(val1--){
        if(strcmp(dirlist[val1]->d_name,*(argv+3))==0){
         stat(*(argv+3),&sb);
//         printf("faccess Makefile: %s",ctime(&sb.st_atime)); 
//         printf("fstatus Makefile: %s",ctime(&sb.st_ctime));    
//         printf("fmod Makefile:    %s",ctime(&sb.st_mtime));
         mkindir=1;
         break;
        }
      }

     if(mkindir==0){
       fprintf(stderr,"Error: Makefile given not in dir(3)\n");
     while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
       status =1; return status;}

     fp=fopen(*(argv+3), "r");
   mkindir=0;  
   targ=strdup(*(argv+1));

   }else{
  fprintf(stderr,"Error: Makefile and file improper format\n");
     while(freeval1--){
       free(dirlist[freeval1]);
       } 
     free(dirlist);
     free(targ);
       status =1; return status;}

  }

 while(freeval1--){
   free(dirlist[freeval1]);
 } 
  free(dirlist);

 

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
        setcmnd(verhead,first,strdup(temp3),grph);
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

//scan whole first string for :
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


// found : in first string
// if mkr1==2 settarg first and add sec2 as dep send nxtestln loop
     if(mkr1==2){
     
     //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
//printf("no2b");


       targ=strdup(first);}
       

       addvert(verhead,strdup(first),grph,1); 
       addvert(verhead,strdup(sec2),grph,0); 
       addedge2(verhead,grph,first,sec2);

// printf("case1 a:b first:%s sec2:%s %s\n",first,sec2,nxtestln);
     }
// if mkr1==1 settarg first and send nxtestln to loop 
    if(mkr1==1){
    //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
//printf("no2c");


       targ=strdup(first);}
      

    addvert(verhead,strdup(first),grph,1); 
// printf("case2 a: b first:%s nxt:%s\n",first,nxtestln);
    }

// if mkr1==0 check for : using below

    if(mkr1==0){
      int strtest=sscanf(nxtestln,"%64s%n",str2,&offset2);

      if(strtest<1){
      fprintf(stderr,"Last: Error improper format(1)\n");
      status=1;
      myfree(verhead,grph);  
      free(targ);
      if(vtx!=NULL){  
      free(vtx);}

      if(fp!=NULL){
      fclose(fp);}

      free(testln); 
      return status;} 

      char *temp2=str2;

      if(strcmp(temp2,":")==0){
   
      strcpy(first,str1);
   //set targ  if mkindir
       if(mkindir==1 && lncnt==1){ 
//printf("no2d");


       targ=strdup(first);}   
       
// settarg str1 moveup by offset2 nxtestln and send to loop 

      addvert(verhead,strdup(first),grph,1); 

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
//printf("no2e");

       targ=strdup(first);}
      
      addvert(verhead,strdup(first),grph,1); 
       addvert(verhead,strdup(second),grph,0); 
       addedge2(verhead,grph,first,second);

// settarg str1 moveup nxtestln by fset1 and send to loop
//printf("case4 a :b str1%s secnd:%s nxt:%s\n",str1,second,nxtestln);

     }

    if(mkr2==0 && mkr1==0){
      fprintf(stderr,"Last: Error improper format(2)\n");
      status=1;
      myfree(verhead,grph);  
      free(targ);
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

       addvert(verhead,strdup(temp),grph,0);
       addedge2(verhead,grph,first,temp);

       nxtestln+=offset3;

       }

    lncnt++;
   }

   int i;
   vtx=(int*)malloc(numV*sizeof(int)); 
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
 /*  
    if(mkcmnd==0){ 
      printf("%s already made\n",targ);
    }
*/
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
   free(targ);
   free(grph->ver);
    free(grph);


  }
