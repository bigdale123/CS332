#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BUFFSIZE 4096
int main(int argc, char *argv[]) {
    int  readFileDescriptor, writeFileDescriptor;
    long int n;
    char buf[BUFFSIZE];
    char newline[1] = {'\n'};

    if (argc != 3){
        printf("Usage: %s <source_filename> <destination_filename>\n", argv[0]);
        exit (-1);
    }

    if (strcmp(argv[1],argv[2]) == 0){
        printf("Cannot append to the same file!\n");
        exit (-1);
    }

    readFileDescriptor = open(argv[2], O_RDONLY);
    writeFileDescriptor = open(argv[1], O_CREAT|O_WRONLY|O_APPEND, 0700);

    if(write(writeFileDescriptor,newline,sizeof(newline)) != sizeof(newline)){
        printf("Error writing to output file\n");
        exit (-1);
    }
    

    if (readFileDescriptor == -1 || writeFileDescriptor == -1){
        printf("Error with file open\n");
        exit (-1);
    }

    while ((n = read(readFileDescriptor, buf, BUFFSIZE)) > 0){
        if (write(writeFileDescriptor, buf, n) != n){
            printf("Error writing to output file\n");
            exit (-1);
        }
    }

    if (n < 0){
        printf("Error reading input file\n");
        exit (-1);
    }

    close(readFileDescriptor);
    close(writeFileDescriptor);
    return 0;
}