# Mini Project 0: Operating Systems and Networks

## Overview

This mini-project consisted of two parts:

1. File Management
2. Process Creation and Management

## Code

- <span style="color:lightblue"> The submitted code can be found in the `code` folder. </span>
- The code is written in C.
- Use GCC to compile the code.
- The specifications implemented are attached in the <span style="color:lightblue"> website folder </span>. To view open the `.html` file in a browser.

## Part 1: File Management

Create a C program that does the following:

1. Accepts user input.
2. Displays file content.

### File Structure

- `fileManagement.c`: Contains the implementation for file management.

## Part 2: Process Creation and Management

Create a C program that demonstrates various process API calls.

### Tasks

1. Before creating your first child, have the parent process access a variable (e.g., `x`) and set its value to 25. What is the value of the variable in the child process? What happens to the variable when both the child and parent change the value of `x`?
2. Create a child process that uses `exec()` to create a file named `newfile.txt` and store its parent process ID in the file.
3. Create a child process that outlives its parent process. The parent process should terminate immediately after forking. The child process should then print its parent process ID.

### File Structure

- `processManagement.c`: Contains the implementation for process management.

## Error Handling

- Ensure system calls are successful. If not, display an error message and exit the program.
- Ensure the file is successfully created and opened for writing. If not, display an error message.
- Handle invalid commands by prompting the user with an appropriate message.
