/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed!\n");
    }
    else if (pid == 0)
    {
        // Child Process
        printf("\n--- Child Process ---\n");
        printf("Child Process ID (PID): %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
    }
    else
    {
        // Parent Process
        printf("\n--- Parent Process ---\n");
        printf("Parent Process ID (PID): %d\n", getpid());
        printf("Parent's Parent Process ID (PPID): %d\n", getppid());
        printf("Child Process ID: %d\n", pid);
    }

    return 0;
}