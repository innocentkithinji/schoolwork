#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void child(int readfd, int writefd){
    char msg[100];
    int n;
    char eof = EOF;
    printf("%d enter msg to be sent to parent:", getpid());
    fgets(msg, 100, stdin);
    if (write(writefd, msg, strlen(msg) -1 ) == 1){
        perror("error writing");
        exit(0);
    }
    if ((n = read(readfd, msg, 100)) < 0){
        perror("error reading");
        exit(0);
    }
    msg[n] = NULL;
    printf("recieved from parent: %s", msg);
}

void parent(int readfd, int writefd){
    char msg[100];
    int n;
    
    if (write(writefd, msg, strlen(msg) -1 ) == 1){
        perror("error writing");
        exit(0);
    }
    if ((n = read(readfd, msg, 100)) < 0){
        perror("error reading");
        exit(0);
    }
    msg[n] = NULL;
    printf("%s recieved from child: %s", getpid(), msg);

    printf("%d enter msg to be sent to child :", getpid());
    fgets(msg, 100, stdin);
    write(writefd, msg, strlen(msg) -1 );
}

int main(){
    int pipe1fd[2], pipe2fd[2];

    if (pipe(pipe1fd) == -1){
        perror("pipe error: ";)
        return 0;
    }
    if (pipe(pipe2fd) == -1){
        perror("pipe error: ";)
        return 0;
    }

    pid = fork();
    if(pid == 0){
        close(pipe1fd[1]);
        close(pipe2fd[0])

        child(pipe1fd[0], pipe2fd[1]);
        exit(0);
    }
    else{
        close(pipe1fd[0]);
        close(pipe2fd[1])

        parent(pipe2fd[0], pipe1fd[1]);
        return 0;

    }
}
