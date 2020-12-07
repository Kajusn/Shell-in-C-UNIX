#include "command_execution.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
int pipe(int pipefd[2]);
#define _GNU_SOURCE
#include <unistd.h>
#include <fcntl.h> 
int pipe2(int pipefd[2], int flags);


/* Executes command using given input and output file descriptors */
void exec_command(int in, int out, int to_close_fd, Command cmd) 
{
	int status = 0;
	pid_t pid;

	pid = fork();

	if (pid < 0) {
		printf("Failed creating new process. %s\n", strerror(errno));
		return;
	}

	if (pid == 0) {
		close(to_close_fd);
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != STDOUT_FILENO) {
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		if (execvp(cmd.args[0], cmd.args) < 0) {
			printf("\nCould not execute command\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	} else {
		return;
	}
}

/* Creates and connects pipes and their inputs/outputs */
void fork_pipes(int n, Command *cmd) 
{
	int i, in, out, fd[2];
	pid_t pid;

	/* The first process should get its input from the original stdin file descriptor 0.  */
	in = 0;

	/* Loops all except the last command */
	for (i = 0; i < n - 1; ++i) {
		//pipe2(fd, O_CLOEXEC);
		pipe(fd);
		out = fd[1];
		/* f[1] is the write end of the pipe, we carry 'in' from the prev iteration.  */
		exec_command(in, out, fd[0], cmd[i]);
		if (in != STDIN_FILENO)
        	close (in);
      	if (out != STDOUT_FILENO)
        	close (out);
      	in = fd[0];
	}
	
	exec_command(in, STDOUT_FILENO,-1, cmd[i]);

	if (in != STDIN_FILENO)
		close (in);
	if (out != STDOUT_FILENO)
		close (out);

	int status = 0;

    while((pid = waitpid(WAIT_ANY, &status, 0)) > 0);
}