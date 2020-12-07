#include "input_handling.h"
#include "command_execution.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    char *input_str, *args_piped[MAXCMDS];
    
    /* No command line parameters */
    if (argc < 2) {
        printf("Welcome to my implementation of shell!\n>");
	    while (1) {
            /* Read from stdin, continue loop if input is empty */
	        if (!read_input(&input_str))
		        continue;
            /* Piped commands */
            int n_commands = split_string(input_str, args_piped, "|");
            Command commands[n_commands];

            for (int i=0; i<n_commands; i++) {
                if (split_string(args_piped[i], commands[i].args, " ") == 0) {
                    n_commands--; i--;
                }
            }
            if (n_commands > 0) {
                int ret = strcmp(commands[0].args[0], "exit");
                if (ret == 0) {
                    exit(0);
                }
                fork_pipes(n_commands, commands);
            } else {
                continue;
            }
            printf("\n>");
	    }
    } else {
        /* Use command line parameters */
        argv[argc] = NULL;
        Command command;
        for (int i = 0; i < MAXCMDS; i++) {
            if ((argv+1)[i] != NULL) {
                command.args[i] = (argv+1)[i];
            } else {
                command.args[i] = (argv+1)[i];
                break;
            }
        }
        int ret = strcmp(command.args[0], "exit");
        if (ret == 0) {
            exit(0);
        }
	    exec_command(STDIN_FILENO, STDOUT_FILENO,-1, command);
    }
    return 0;
}