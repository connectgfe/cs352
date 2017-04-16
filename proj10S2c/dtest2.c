#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


int main(int argc, char **argv){

  FILE *fp=NULL;


  int status=0;
  int i;


  struct dirent **dirlist;
  struct stat sb;
  int val1=0;
  int val2=0; 
  int mkindir=0;
  char *testln=NULL; 
  size_t ln=0;  
  char *targ=NULL; 



  printf("no of args:%d\n", argc);

/*
  for(i=0;i<argc;i++){
  printf("%d %s\n",i,*(argv+i));
  }

exit(0);
*/

//no args, search for Makefile and target
  if(argc==1){ 
  

    val1 = scandir(".", &dirlist,NULL,alphasort);
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
       fprintf(stderr,"Error: Not proper args(1)\n"); 
       status =1; return status;}

     fp=fopen("Makefile", "r");
  } 


// only target given  
  if(argc==2){
    
     val1 = scandir(".", &dirlist,NULL,alphasort);
      while(val1--){
        if(strcmp(dirlist[val1]->d_name,"Makefile2")==0){
         stat("Makefile2",&sb);
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
     
     fp=fopen("Makefile2", "r");
   
    targ=strdup(*(argv+1));
    } 

  if(argc==3){

   if(strcmp(*(argv+1),"-f")==0){
   val1 = scandir(".", &dirlist,NULL,alphasort);
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
       fprintf(stderr,"Error: Makefile given not in dir\n"); 
       status =1; return status;}
 
     fp=fopen(*(argv+2), "r");
   }else{
   fprintf(stderr,"Error: Not proper file assign\n"); 
       status =1; return status;}
//note: targ in makefile so use mkindir to set targ     
  }


  if(argc==4){

   if(strcmp(*(argv+1),"-f")==0){
    val1 = scandir(".", &dirlist,NULL,alphasort);
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
       fprintf(stderr,"Error: Makefile given not in dir\n"); 
       status =1; return status;}
 
     fp=fopen(*(argv+2), "r");
     targ=strdup(*(argv+3));

   }else if(strcmp(*(argv+2),"-f")==0){
    val1 = scandir(".", &dirlist,NULL,alphasort);
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
       fprintf(stderr,"Error: Makefile given not in dir\n"); 
       status =1; return status;}
 
     fp=fopen(*(argv+3), "r");
     targ=strdup(*(argv+1));

   }else{
  fprintf(stderr,"Error: Makefile and file improper format\n"); 
       status =1; return status;}
 
  }

 printf("targ: %s\n",targ);



// need to make first target in file if no target specified
  while(val2>-1){
      val2=getline(&testln,&ln,fp);
    
      if(val2==1){ continue;}
    
      printf("%s",testln);
   }



   



/*
 val = scandir(".", &dirlist,NULL,alphasort);
  while(val--){
   if(strcmp(dirlist[val]->d_name,"Makefile")){
     stat("Makefile",&sb);
     printf("faccess Makefile: %s",ctime(&sb.st_atime)); 
     printf("fstatus Makefile: %s",ctime(&sb.st_ctime));    
     printf("fmod Makefile:    %s",ctime(&sb.st_mtime));
     break; 
   } 
   
*/


/*
//neet to free the below
   free(dirlist[val]);
 
  free(dirlist);
*/

 char *cmnd="ls -l"; 


  int retval = system(cmnd);

return 0;
}
