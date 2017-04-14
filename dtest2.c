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
 



  printf("no of args:%d\n", argc);

//  for(i=0;i<argc;i++){
//  printf("%d %s\n",i,*(argv+i));
//  }

  //case 1: no args, search for Makefile
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
       fprintf(stderr,"Error: Not proper args(1)\n"); 
       status =1; return status;}

     fp=fopen("Makefile", "r");
  } 
  
  if(argc==2){
     if(**(argv+1)=='-'){fprintf(stderr,"Error: Not proper args(2)\n"); 
     status =1; return status;}




  }



// need to make first target in file if no target specified
  while(val2>-1){
      val2=getline(&testln,&ln,fp);
    
      if(val2==1){ continue;}
    
      printf("%s",testln);
   }




 exit(0);
   



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

  


  int retval = system("echo hello");

return 0;
}
