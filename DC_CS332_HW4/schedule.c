#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
#include <features.h>


struct job {
    int jobid;
    char *command;
    char *status;
    pthread_t tid;
};

struct thread_info {
    char *command;
    int jobid;
};

void *start_thread(void *arg){
    int jobid = (int)(((struct thread_info*)arg)->jobid);
    char jobid_char[8];
    sprintf(jobid_char,"%d",jobid);
    char *Command_str = malloc(sizeof(char)*strlen((char *)arg));
    strcpy(Command_str,(char*)(((struct thread_info*)arg)->command));

    

    int k;
    int command_count = 0;
    for(k=0;k<strlen(Command_str);k++){
        if(Command_str[k]==' '){
            command_count++;
        }
    }
    command_count+=1; // Number of command will always be one greater than number of whitespace, then add additional space for NULL at end
    char *command_arr[command_count];
    command_arr[0]=strtok(Command_str," ");
    char *token;
    int h=1;
    for(h=1;h<command_count;h++){
        command_arr[h] = strtok(NULL," ");
    }
    command_arr[command_count] = NULL; //ensures array is null terminated
    int i;
    for(i=0;i<command_count;i++){
        //printf("%s\n",command_arr[i]);
    }

    pid_t pid;
    if((pid=fork())==0){
        char *newstdout_path = malloc(sizeof(jobid_char)+sizeof(strlen(".out")));
        strcpy(newstdout_path,jobid_char);
        strcat(newstdout_path,".out");
        FILE *new_stdout = fopen(newstdout_path,"w");
        dup2(fileno(new_stdout),STDOUT_FILENO);


        char *newstderr_path = malloc(sizeof(jobid_char)+sizeof(strlen(".err")));
        strcpy(newstdout_path,jobid_char);
        strcat(newstdout_path,".err");
        FILE *new_stderr = fopen(newstdout_path,"w");
        dup2(fileno(new_stderr),STDERR_FILENO);

        execvp(command_arr[0], command_arr);
    }
    else{
        wait(0);
    }
    
}

void main(int argc, char **argv){
    
    if(argc < 2){
        printf("Usage: %s [Max # of Threads]\n", argv[0]);
        exit(-1);
    }

    int items_in_queue = 0;
    struct job queue[100];
    char *input;
    int max_threads = atoi(argv[argc-1]);
    int current_running[max_threads];
    int current = 0;
    int jobid = 0;
    int j;
    int n = 0;
    while(1){
        //while((n = read(fd[0],line,8192)) > 0){}
        // read from pipe replaced with scanf for testing
        printf(" > ");
        // Used this resource to dynamically allocate the string: 
        // https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
        scanf(" %m[^\n]",&input);
        if(strstr(input," ")!=NULL){
            // basically only gets run for submit (since all else is single command)
            // submit will use a string, containing the program and arguments.
            strtok(input," ");
            input = strtok(NULL,"");
            queue[items_in_queue].jobid = jobid;
            queue[items_in_queue].command = malloc(strlen(input));
            strcpy(queue[items_in_queue].command,input);
            queue[items_in_queue].status = malloc(sizeof(12));
            strcpy(queue[items_in_queue].status,"waiting");
            items_in_queue++;
            jobid++;
            // char *new_input = malloc(sizeof(input)+1);
            // strcpy(new_input,input);
            // strcpy(line,new_input);
            // printf("%s",new_input);
        }
        int i;
        for(i=0;i<items_in_queue;i++){
            if(strcmp(queue[i].status,"waiting")==0){
                break;
            }
        }
        //printf("%d\n",i);
        if(queue[i].command != NULL){
            if(strcmp(queue[i].command,"")!=0){
                //printf("Got new job, %s\n", queue[i].command);
                if(current<max_threads&&(strcmp(queue[i].status,"waiting")==0)){
                    // submit job if room for it exists
                    //printf("Would spawn thread, tid of %d\n",current);
                    struct thread_info args;
                    args.command = malloc(strlen(queue[i].command));
                    args.jobid = queue[i].jobid;
                    strcpy(args.command,queue[i].command);
                    pthread_create(&queue[i].tid,NULL,&start_thread,&args);
                    //pthread_join(queue[i].tid,NULL);
                    queue[i].status = "running";
                    current++;
                }
            }
        }
        int k;
        for(k=0;k<items_in_queue;k++){
            if(strcmp(queue[k].status,"running")==0){
                // pthread_tryjoin checks if the thread has exited on its own
                // https://linux.die.net/man/3/pthread_tryjoin_np
                if(pthread_tryjoin_np(queue[k].tid,NULL)==0){
                    pthread_join(queue[k].tid,NULL);
                    queue[k].status = "done";
                }
            }
        }
        for(k=0;k<items_in_queue;k++){
            if(strcmp(queue[k].status,"done")==0){
                int j;
                for(j=k+1;j<items_in_queue;j++){
                    queue[j-1]=queue[j];
                }
                queue[j-1].jobid=0;
                queue[j-1].command=NULL;
                queue[j-1].status=NULL;
                queue[j-1].tid=0;
                items_in_queue--;
                current--;
            }
        }
        if(strcmp(input,"help")==0){
            printf("Usage: ./hw4 <# of threads>\n");
            printf("\n");
            printf("Available Commands:\n");
            printf("  submit <program> [arguments]: Submits a job to the scheduler.\n");
            printf("  showjobs                    : Shows all jobs currently Scheduled.\n");
            printf("\n");
        }
        else if(strcmp(input,"showjobs")==0){
            int j;
            char temp[8];
            char jobs[8192];
            strcpy(jobs,"jobs   command      status\n");
            for(j=0;j<items_in_queue;j++){
                sprintf(temp,"%d",queue[j].jobid);
                strcat(jobs,temp);
                strcat(jobs,"      ");
                strcat(jobs,queue[j].command);
                strcat(jobs,"  ");
                strcat(jobs,queue[j].status);
                strcat(jobs,"\n");
            }
            printf("%s",jobs);
        }
        else if(strcmp(input,"q")==0){
            exit(0);
        }
        else if(strstr(input," ")!=NULL){}
        else{
            printf("Please Enter a valid command.\n");
        }
    }
}