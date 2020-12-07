#include "input_handling.h"
#include "command_execution.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* Reads input from stdin, returns 0 if there are no commands */
int read_input(char** input_str) 
{  
    size_t input_len = 0, n;
	int len = getline(input_str, &input_len, stdin);

    /* Find length excluding the newline at end */
    if (len > (ssize_t)0) {
		n = strcspn(*input_str, "\r\n");
	} else {
		n = 0;
	}
        
    if (n > (size_t)0) {
        /* Terminate input command before the newline */
        (*input_str)[n] = '\0';
        return 1;
    } else {
        return 0;
    }
}

/* Splits string by given token, returns number of splits */
int split_string(char* str, char** str_split, char* token) 
{ 
	int i;

	for (i = 0; i < MAXCMDS; i++) { 
		str_split[i] = strsep(&str, token); 

		if (str_split[i] == NULL) 
			break; 

		if (strlen(str_split[i]) == 0) 
			i--; 
	}
	return i;
}