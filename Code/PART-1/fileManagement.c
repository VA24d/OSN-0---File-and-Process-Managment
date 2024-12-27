#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define true 1

int main() {
    printf("Welcome to file system\n");
    char command[4096];
    char ToFile[4096];
    char output[4096];

    // Open or create newfile.txt for writing with permissions 0644
    int fd = open("newfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Write open");
        return 1;
    }

    // Duplicate the standard file descriptors
    int fd_stdout = dup(STDOUT_FILENO);
    int fd_stdin = dup(STDIN_FILENO);

    while (true) {
        printf(">>");
        scanf("%s", command);

        if (!strcmp(command, "INPUT")) {
            printf(" -> ");
            // Read the full line of input after the command
            scanf("\n"); // Consume the newline character from previous input
            scanf("%[^\n]s", ToFile);

            // Redirect stdout to the file
            dup2(fd, STDOUT_FILENO);
            printf("%s\n", ToFile); // Write to the file

            // Restore stdout to console
            dup2(fd_stdout, STDOUT_FILENO);
        }
        else if (!strcmp(command, "PRINT")) {
            // Close the write file descriptor first
            close(fd);

            // Open the file for reading using freopen
            FILE *file = freopen("newfile.txt", "r", stdin);
            if (file == NULL) {
                perror("Read freopen");
                continue;
            }

            int lines=0;

            // Read and print each line from the file using scanf and printf
            while (scanf("%[^\n]\n", output) == 1) {
                printf("%s\n", output);
                lines++;
            }

            if (!lines)
                printf("No lines in file. Create some with the \"INPUT\" command.\n");

            // Restore stdin to console
            freopen("/dev/tty", "r", stdin); // For Unix-like systems
            // Use "CON" instead of "/dev/tty" for Windows systems

            // Reopen the file in append mode for further INPUT commands
            fd = open("newfile.txt", O_WRONLY | O_APPEND, 0644);
            if (fd == -1) {
                perror("Write reopen");
                return 1;
            }
        }
        else if (!strcmp(command, "STOP")) {
            break;
        }
        else {
            printf("Unknown command: %s, Did you mean STOP?\n", command);
        }
    }

    // Close the file descriptor
    printf("Closing and Exiting... ");
    close(fd);
    close(fd_stdout);
    close(fd_stdin);
    printf("Done\n");

    return 0;
}
