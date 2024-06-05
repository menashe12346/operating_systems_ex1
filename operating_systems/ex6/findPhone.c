#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For functions like fork, pipe, dup2

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s Name\n", argv[0]);
        return 1;
    }

    /* 
    Declare two pipes. Each pipe is an array of two integers. for each pipe the first integer represent the Read end and second integer represent the write end
    Write End: The endpoint of the pipe where a process writes data.
    Read End: The endpoint of the pipe where a process reads data.
    Pipes are used for inter-process communication,(תקשורת בין תהליכים) allowing data to flow between processes.  we will use them with fork and exec functions to set up communication between processes.
    pipes are useful for passing data from one process to another without using complex communication methods.
    */
    int pipe1[2], pipe2[2]; //This declaration alone does not create the pipe; it only allocates space to store the file descriptors.
    /*
    pid is a unique identifier assigned by the operating system to each process.
    The pid helps the system to keep track of all running processes and manage them accordingly.
    When fork() is called, it creates a new process It returns a value of 0 to the child process and the child process's pid to the parent process. if an error occurs no child process will be created.
    */
    pid_t pid1, pid2;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) { //now we are creating the actual pipe. the array is passed as an argument to the pipe function, which fills the array with two file descriptors
        printf( "Error creating pipes");
        return 1;
    }

    // First fork for grep
    //When you call the fork() function it creates a new process by duplicating the calling (parent) process.
    if ((pid1 = fork()) == -1) { //Create a child process. fork returns the child's PID to the parent and 0 to the child.
        printf( "Error: first fork failed");
        return 1;
    }

    if (pid1 == 0) { //means that this code is executed by the child process.
        // Child process for grep
        close(pipe1[0]); // we dont need to read from the child.
        dup2(pipe1[1], STDOUT_FILENO); // Redirects the standard output to the write end of the pipe. it Ensures that the output of the child process (grep in this case) is written to the pipe, which can then be read by another process (the parent process).
        close(pipe1[1]); // we dont need to write anymore.

        // used to replace the process image with grep
        execlp("grep", "grep", argv[1], "phonebook.txt", (char *)NULL);  // A NULL pointer to indicate the end of the arguments.
        printf( "Error: execlp failed"); //execute this only if the the execlp faild to redirect to the other process.
        return 1;
    }

    // Second fork for sed and awk
    if ((pid2 = fork()) == -1) {
        printf( "Error: second fork failed");
        return 1;
    }

    if (pid2 == 0) {
        // Child process for sed and awk
        close(pipe1[1]);
        /*
        This line duplicates the read end of pipe (file descriptor pipe1[0]) to the standard input (file descriptor STDIN_FILENO).
        After this call, any standard input read operations (like scanf, gets) will read from the pipe instead of the keyboard.
        */
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);

        close(pipe2[0]);
        /*
        This line duplicates the write end of pipe2 (file descriptor pipe2[1]) to the standard output (file descriptor STDOUT_FILENO).
        After this call, any standard output write operations (like printf, puts) will write to the pipe instead of the screen.
        */
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);

        /*
        The first command will return only the line that contains the "Name."
        The second command will replace all spaces with hash symbols.
        The third command will replace the comma with a space (thus creating a second column).
        The fourth command will print the second column (the phone number).
        */
        execlp("sh", "sh", "-c", "sed 's/ /#/g' | sed 's/,/ /' | awk '{print $2}'", (char *)NULL);
        printf( "Error: execlp failed"); //execute this only if the the execlp faild to redirect to the other process.
        return 1;
    }

    // Parent process
    //close the pipes because we dont need them anymore.
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);

    char buffer[128];
    int count;
    while ((count = read(pipe2[0], buffer, sizeof(buffer) - 1)) > 0) { //Reads data from the read end of the second pipe into the buffer.
        buffer[count] = '\0';
        printf("%s", buffer);
    }

    close(pipe2[0]);
    return 0;
}

/*
How the function works:
First Child (grep) Redirects stdout to write end of pipe1.
then the Second Child (sed and awk) Redirects stdin to read end of pipe1 and Redirects stdout to write end of pipe2.
and finally the parent Reads from read end of pipe2 and prints the output.
*/