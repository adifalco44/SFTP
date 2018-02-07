#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/time.h>  
#include "server.h"
#include <dirent.h>
#include <stdint.h>
#include <errno.h>
#define MAXSIZE 100

void delf(char *name, int32_t size){
    char buf[MAXSIZE];
    if ((size!=recv(new_s,buf,sizeof(buf),0))<0){
	fprintf(stderr,"[recv] : %s",strerror(errno));
	return -1;
    }
    char *root_path = "../"
    char *full_path = "";
    sprintf(full_path,"%s%s",root_path,name);
    FILE *f = fopen(full_path,"r+");
    if (f != NULL){ // Success
	 fclose(f);
	 char *command;
	 char *temp_com = "rm ";
         sprintf(command,"%s%s",temp_com,full_path);
	 int rtr_val = system(command);
	 if (rtr_val == 0){ // Successful Sys Call
	    strcpy(buf,"1");	
	 }else{             // Failed Sys Call
	    strcpy(buf,"-1");
	 }
    }else{
	strcpy(buf,"-2"); // Failure
    } 
    /* Sends Message */
    if ((sendto(new_s,buf,sizeof(buf),0,(struct sockaddr *)&new_s,sizepf(struct sockaddr)))<0){
	fprintf(stderr,"[MDIR sendto #1] : %s",strerror(errno));
	continue;
    }

}

void list(){
   char *cmd = "ls -l";
   char buf[MAXSIZE];
   FILE *listing;
   listing = popen(cmd);
   int32_t size = sizeof(listing);
   if ((sendto(new_s,buf,sizeof(buf),0,(struct sockaddr *)&new_s,sizepf(struct sockaddr)))<0){
       fprintf(stderr,"[MDIR sendto #1] : %s",strerror(errno));
       continue;
   }
   if (listing){
	while (!feof(listing)){
              if (fgets(buf,MAXSIZE,listing)!=NULL){
		    if ((sendto(new_s,buf,sizeof(buf),0,(struct sockaddr *)&new_s,sizepf(struct sockaddr)))<0){
       			fprintf(stderr,"[MDIR sendto #1] : %s",strerror(errno));
       			continue;
   		    }
	      }
	}
   }else{
	return EXIT_FAILURE;
   }   
}


void mdir(char *name, int32_t size){
    char buf[MAXSIZE];
    if ((size!=recv(new_s,buf,sizeof(buf),0))<0){
	fprintf(stderr,"[recv] : %s",strerror(errno));
	return -1;
    }
    char *root_path = "../root_dir"
    char *full_path = "";
    sprintf(full_path,"%s%s",root_path,name);
    DIR *d = opendir(full_path);
    if (d == NULL){ // Success
	 char *command;
	 char *temp_com = "mkdir ";
         sprintf(command,"%s%s",temp_com,full_path);
	 int rtr_val = system(command);
	 if (rtr_val == 0){ // Successful Sys Call
	    strcpy(buf,"1");	
	 }else{             // Failed Sys Call
	    strcpy(buf,"-1");
	 }
    }else{
	closedir(full_path);
	strcpy(buf,"-2"); // Failure
    } 
    /* Sends Message */
    if ((sendto(new_s,buf,sizeof(buf),0,(struct sockaddr *)&new_s,sizepf(struct sockaddr)))<0){
	fprintf(stderr,"[MDIR sendto #1] : %s",strerror(errno));
	continue;
    }
}




void rdir(char *name, int32_t size){
    char buf[MAXSIZE];
    if ((size!=recv(new_s,buf,sizeof(buf),0))<0){
	fprintf(stderr,"[recv] : %s",strerror(errno));
	return -1;
    }
    char *root_path = "../"
    char *full_path = "";
    sprintf(full_path,"%s%s",root_path,name);
    DIR *d = opendir(full_path);
    if (d != NULL){ // Success
	 closedir(full_path);
	 char *command;
	 char *temp_com = "rm ";
         sprintf(command,"%s%s",temp_com,full_path);
	 int rtr_val = system(command);
	 if (rtr_val == 0){ // Successful Sys Call
	    strcpy(buf,"1");	
	 }else{             // Failed Sys Call
	    strcpy(buf,"-1");
	 }
    }else{
	strcpy(buf,"-2"); // Failure
    } 
    /* Sends Message */
    if ((sendto(new_s,buf,sizeof(buf),0,(struct sockaddr *)&new_s,sizepf(struct sockaddr)))<0){
	fprintf(stderr,"[MDIR sendto #1] : %s",strerror(errno));
	continue;
    }

}


void cdir(char *name, int32_t size){
    char buf[MAXSIZE];
    if ((size!=recv(new_s,buf,sizeof(buf),0))<0){
	fprintf(stderr,"[recv] : %s",strerror(errno));
	return -1;
    }
    char *root_path = "../root_dir"
    char *full_path = "";
    sprintf(full_path,"%s%s",root_path,name);
    DIR *d = opendir(full_path);
    if (d != NULL){ // Success
	 closedir(full_path);
	 char *command;
	 char *temp_com = "cd ";
         sprintf(command,"%s%s",temp_com,full_path);
	 int rtr_val = system(command);
	 if (rtr_val == 0){ // Successful Sys Call
	    buf = "1";	
	 }else{             // Failed Sys Call
	    buf = "-1";
	 }
    }else{
	buf = "-2"; // Failure
    } 
    /* Sends Message */
    if ((sendto(new_s,buf,sizeof(buf),0,(struct sockaddr *)&new_s,sizepf(struct sockaddr)))<0){
	fprintf(stderr,"[MDIR sendto #1] : %s",strerror(errno));
	continue;
    }

}

