#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define true 1
#define pn printf("\n");

int main()
{
    printf("Initialized main\n");
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        printf("PART 1\n");
        int x = 25;
        pid_t child1 = fork();
        if (child1 == 0)
        {
            printf("\tValue of x in child: %d\n", x);
            x = 100;
            printf("\tChanged value of x to 100 in child process\n");
            printf("\tValue of x in child: %d\n", x);
        }
        else
        {
            wait(NULL);
            printf("\tValue of x in parent: %d\n", x);
            x = 0;
            printf("\tChanged value of x to 0 in parent process\n");
            printf("\tValue of x in parent: %d\n", x);
        }

        if (child1 == 0)
        {
            printf("\tValue of x in child: %d\n", x);
        }
        else
        {
            wait(NULL);
            printf("Done with part one\n");
        }
    }
    else
    {
        wait(NULL);

        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            printf("PART 2\n");
            // Create newfile.txt
            pid_t t_exc = fork();
            if (t_exc == 0)
            {
                char *c_args[] = {"touch", "newfile.txt", NULL};
                execvp(c_args[0], c_args);
                perror("execvp failed");
                exit(1);
            }
            else
            {
                wait(NULL);
            }

            int w_exc = fork();
            if (w_exc < 0)
            {
                perror("fork failed");
                exit(1);
            }
            else if (w_exc == 0)
            {
                execlp("sh", "sh", "-c", "echo Parent PID: $PPID > newfile.txt", NULL);

                // If execlp fails
                perror("execlp failed");
                exit(1);
            }
            else
            {
                // Parent process
                wait(NULL);
                printf("Done with part two\n");
            }
        }
        else
        {
            wait(NULL);

            pid_t pid3 = fork();
            if (pid3 == 0)
            {
                printf("PART 3\n");
                pid_t pid = fork();
                if (pid < 0)
                {
                    perror("fork failed");
                    return 1;
                }
                else if (pid == 0)
                {
                    // Child process
                    // The child process will sleep to ensure the parent exits
                    sleep(2); // Sleep to simulate a long-running process
                    printf("\tChild Process:\n");
                    printf("\t\tParent Process ID after termination: %d\n", getppid()); // Print parent PID
                    printf("\t\tChild Process ID: %d\n", getpid());                     // Print child PID
                }
                else
                {
                    // Parent process
                    printf("\tParent Process:\n");
                    printf("\t\tParent Process ID before termination: %d\n", getpid()); // Print parent PID
                    // exit(0);
                    
                    return 0; // Parent exits immediately
                }

                printf("Done with part three\n");
            }
        }
    }

    return 0;
}
