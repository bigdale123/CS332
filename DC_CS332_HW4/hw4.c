#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct args {
    char *program;
    char *args;
}

void create_thread(){

}

void main(int argc, char **argv){

    if(argc > 2 || argc < 2){
        printf("Usage: ./hw4 [thread_count]\n");
        exit(0);
    }
    int thread_count = atoi(argv[argc-1]);
    
    char *input;
    while(1){
        printf(" > ");
        // Used this resource to dynamically allocate the string: 
        // https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
        scanf(" %m[^\n]",&input);
        if(strstr(input," ")!=NULL){
            // basically only gets run for submit (since showjobs is single command)
            // submit will use a struct, containing the program and arguments.

        }
        else{
            if(strcmp(input,"help")==0){
                printf("Usage: ./hw4 <# of threads>\n");
                printf("\n");
                printf("Available Commands:\n");
                printf("  submit <program> [arguments]: Submits a job to the scheduler.\n");
                printf("  showjobs                    : Shows all jobs currently Scheduled.\n");
                printf("\n");
            }
            else if(strcmp(input,"q")==0){
                exit(0);
            }
            else{
                printf("Please Enter a valid command.\n");
            }
                    
        }
    }
    
}