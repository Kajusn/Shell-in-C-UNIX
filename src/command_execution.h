#define MAXCMDS 100     // Maximum number of commands supported

typedef struct CommandStruct
{
	char *args[MAXCMDS];
} Command;

void exec_command(int input, int output, int, Command);
void fork_pipes(int n_pipes, Command *);