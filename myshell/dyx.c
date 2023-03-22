#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 128
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3
#define NONE_REDIR 0

int redir_status=NONE_REDIR;
int PIPES=0;

void parse_args(char* line, char** args) {
    char* token = strtok(line, " \t\r\n\a");
    args[0] = token;
    int i = 1;
    if(strcmp(args[0],"ls")==0)
        {
            args[i++]=(char*)"--color=auto";
        }
        if(strcmp(args[0],"ll")==0)
        {
            args[0]=(char*)"ls";
            args[i++]=(char*)"-l";
            args[i++]=(char*)"--color=auto";
        }
    while (token != NULL) {
        token = strtok(NULL, " \t\r\n\a");
        args[i++] = token;
    }
}

int has_pipe(char** args, int* pipe_position) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            *pipe_position = i;
            return 1;
        }
    }
    return 0;
}

char *CheckRedir(char *start)
{
    char *end=start+strlen(start)-1;
 
    while(end>=start)
    {
        if(*end=='>')
        {
            if(*(end-1)=='>')
            {
                redir_status=APPEND_REDIR;
                *(end-1)='\0';
                end++;
                while(*end==' ')
                    ++end;
                break;
            }
            redir_status=OUTPUT_REDIR;
            *end='\0';
            end++;
            while(*end==' ')
                ++end;
            break;
        }
        else if(*end=='<')
        {
            redir_status=INPUT_REDIR;
            *end='\0';
            end++;
            while(*end==' ')
                ++end;
            break;
        }
        else
        {
            end--;
        }
    }
    if(end>=start)
    {
        return end;
    }
    else
    {
        return NULL;
    }
}

void run_command_with_pipe(char** args1, char** args2) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(args1[0], args1);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execvp(args2[0], args2);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void run_command(char** args) {
    int pipe_position;
    if (has_pipe(args, &pipe_position)) {
        char* args1[MAX_ARGS];
        char* args2[MAX_ARGS];
        memcpy(args1, args, pipe_position * sizeof(char*));
        args1[pipe_position] = NULL;
        memcpy(args2, &args[pipe_position + 1], (MAX_ARGS - pipe_position - 1) * sizeof(char*));
        run_command_with_pipe(args1, args2);
    } else {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }
}

void run_command_with_pipe1(char** args, int num_args) {
    int pipefd[num_args-1][2];
    pid_t pids[num_args-1];

    // Create all pipes
    for (int i = 0; i < num_args-1; i++) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Create all child processes
    for (int i = 0; i < num_args; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (i == 0) {
                // First command
                dup2(pipefd[i][1], STDOUT_FILENO);
            } else if (i == num_args-1) {
                // Last command
                dup2(pipefd[i-2][0], STDIN_FILENO);
            } else {
                // Intermediate command
                dup2(pipefd[i-1][0], STDIN_FILENO);
                dup2(pipefd[i][1], STDOUT_FILENO);
            }
            // Close all pipes
            for (int j = 0; j < num_args-1; j++) {
                if (j != i-1) {
                    close(pipefd[j][0]);
                    close(pipefd[j][1]);
                }
            }
            execvp(args[i], &args[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            pids[i-1] = pid;
        }
    }

    // Close all pipes in parent process
    for (int i = 0; i < num_args-1; i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < num_args-1; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }
}

int main() {
    char line[MAX_LINE];
    char* args[MAX_ARGS];
    char prior[100]={'\0'};
    args[0]="\0";
    //signal(SIGINT,SIG_IGN); //屏蔽ctrl+c
    while (1) {
        int x=dup(0),y=dup(1);
        printf("[dyx-super-shell]# ");
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        if(strcmp(line,"\n")==0)
            continue;
        line[strlen(line)-1]='\0';
        char *sep=CheckRedir(line);
        parse_args(line, args);
        if (args[0] == NULL) {
            continue;
        }
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] && strcmp(args[1], "-") == 0)
            {
                if (prior)
                {
 
                    char buf[100];
                    getcwd(buf, 100);
                    printf("%s\n", prior);
 
                    chdir(prior);
 
                    strcpy(prior, buf);
                }
                else
                { 
                    printf("bash: cd: OLDPWD 未设定\n");
                }
            }
            else
            {
                getcwd(prior, 100);
                chdir(args[1]);
            }
 
            continue;
        }
        if(sep!=NULL)
            {
                int fd=-1;
                switch(redir_status) {
                    case INPUT_REDIR:
                        fd=open(sep,O_RDONLY);
                        dup2(fd,0);
                        close(fd);
                        break;
                    case OUTPUT_REDIR:
                        fd=open(sep,O_WRONLY|O_TRUNC|O_CREAT,0666);
                        dup2(fd,1);
                        close(fd);
                        break;
                    case APPEND_REDIR:
                        fd=open(sep,O_WRONLY|O_APPEND|O_CREAT,0666);
                        dup2(fd,1);
                        close(fd);
                        break;
                    default:
                        printf("bug?\n");
                        break;
                }
            }
        run_command(args);
        dup2(x,0);
        dup2(y,1);
    }

    return 0;
}
