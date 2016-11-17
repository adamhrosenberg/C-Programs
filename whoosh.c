/* This is the main file for the `whoosh` interpreter and the part
 that you modify. */


//Adam Rosenberg
//Objective here is to create a shell that accepts the whoosh language. Supports simotaneous process running, assigning output of programs to variables, and pipelining between n number of programs. 


#include <stdlib.h>
#include <stdio.h>
#include "csapp.h"
#include "ast.h"
#include <signal.h>
#include "fail.h"

static void run_script(script *scr);
static void run_command(script_command *command);
static void set_var(script_var *var, int new_value);
static void run_single_command(script_group* group);
static void run_or(script_group* group);
static void lay_pipe(script_group* group);

/* You probably shouldn't change main at all. */

int main(int argc, char **argv) {
	script *scr;

	if ((argc != 1) && (argc != 2)) {
		fprintf(stderr, "usage: %s [<script-file>]\n", argv[0]);
		exit(1);
	}

	scr = parse_script_file((argc > 1) ? argv[1] : NULL);

	run_script(scr);

	return 0;
}

static void run_script(script *scr) {
	//script_var* result = scr->groups->result_to;
	int i = 0;
	for (; i < scr->num_groups; i++) {
		script_group currgroup = scr->groups[i];

		switch (currgroup.mode) {
		case GROUP_SINGLE: {
			run_single_command(&currgroup);
			break;
		}
		case GROUP_AND: {
			int i = 0;
			for (; i < currgroup.repeats; i++) {
				lay_pipe(&currgroup);
			}
			break;
		}
		case GROUP_OR: {
			int i = 0;
			for(; i < currgroup.repeats; i++){
				run_or(&currgroup);
			}
			break;
		}
		default:
			break;
		}
	}
}

static void run_single_command(script_group* group) {

	if (group->result_to != NULL) {
		script_var * var = group->result_to;
		int i = 0;

		for (; i < group->num_commands; i++) {
			script_command* command = group->commands;
			pid_t pid = Fork();
			if (pid == 0) {
				Setpgid(0, 0);
				run_command(command);
			} else {
				int status;
				Waitpid(pid, &status, 0);

				int waitstatusvalue = 0;

				if (WIFEXITED(status)) {
					waitstatusvalue = WEXITSTATUS(status);
				} else if (WIFSIGNALED(status)) {
					waitstatusvalue = WTERMSIG(status) * -1;
				} else if (WIFSTOPPED(status)) {
					waitstatusvalue = WSTOPSIG(status);
				}

				set_var(var, waitstatusvalue);
			}
		}
	} else if (group->num_commands == 1) {
		int i = 0;
		for (; i < group->repeats; i++) {
			pid_t pid = Fork();
			if (pid == 0) {
				run_command(&group->commands[0]);
			} else {
				int status;
				Waitpid(pid, &status, 0);
			}
		}
	}
}

static void lay_pipe(script_group* group) {
	script_command * commands = group->commands;
	if (group->result_to != NULL) {
		script_var * var = group->result_to;
		int i = 0;

		for (; i < group->num_commands; i++) {
			script_command* command = group->commands;
			pid_t pid = Fork();
			if (pid == 0) {
				Setpgid(0, 0);
				run_command(command);
			} else {
				int status;
				Waitpid(pid, &status, 0);

				int waitstatusvalue = 0;

				if (WIFEXITED(status)) {
					waitstatusvalue = WEXITSTATUS(status);
				} else if (WIFSIGNALED(status)) {
					waitstatusvalue = WTERMSIG(status) * -1;
				} else if (WIFSTOPPED(status)) {
					waitstatusvalue = WSTOPSIG(status);
				}

				set_var(var, waitstatusvalue);
			}
		}

	} else {
		int i, input, fds[2];
		input = 0;
		pid_t parent = Fork();
		if (parent == 0) {
			for (; i < group->num_commands - 1; i++) {
				pid_t pid;
				pipe(fds);
				pid = Fork();
				if (pid == 0) {
					if (input != 0) {
						Dup2(input, 0);
						close(input);
					}
					if (fds[1] != 1) {
						Dup2(fds[1], 1);
						close(fds[1]);
					}
					run_command(&commands[i]);
				} else {
					close(fds[1]);
					input = fds[0];
					if (commands[i].pid_to != NULL) {
						set_var(commands[i].pid_to, pid);
					}
				}

			}
			if (input != 0) {
				Dup2(input, 0);
			}

			run_command(&commands[i]);

		} else {
			int status;
			Waitpid(parent, &status, 0);
			if (commands[group->num_commands - 1].pid_to != NULL) {
				set_var(commands[group->num_commands - 1].pid_to, parent);
			}
		}
	}

}

static void run_or(script_group* group) {
	if (group->result_to != NULL) {
		script_var * var = group->result_to;
		int i = 0;
		pid_t processes[group->num_commands];
		script_command* commands = group ->commands;
		for (; i < group->num_commands; i++) {
			//script_command* command = group->commands;
			pid_t pid = Fork();
			if (pid == 0) {
				//Setpgid(0, 0);
				run_command(&commands[i]);
			}else{
				processes[i] = pid;
				if (commands[i].pid_to != NULL) {
					set_var(commands[i].pid_to, pid);
				}
			}
		}

		int status;
		pid_t first = Wait(&status);
		//Waitpid(0, &status, 0);
		i = 0;
		for(; i < group->num_commands; i++){
			kill(processes[i], SIGKILL);
		}
		int waitstatusvalue = 0;

		if (WIFEXITED(status)) {
			waitstatusvalue = WEXITSTATUS(status);
		} else if (WIFSIGNALED(status)) {
			waitstatusvalue = WTERMSIG(status) * -1;
		} else if (WIFSTOPPED(status)) {
			waitstatusvalue = WSTOPSIG(status);
		}

		set_var(var, waitstatusvalue);

	}else{
		pid_t processes[group->num_commands];
		int i = 0;
		script_command* commands = group ->commands;
		for (; i < group->num_commands; i++) {

			pid_t pid = Fork();
			if (pid == 0) {
				//Setpgid(0, 0);
				run_command(&commands[i]);
			}else{
				if (commands[i].pid_to != 0) {
					set_var(commands[i].pid_to, pid);
				}
			}
		}
		int status;
		Wait(&status);
		i = 0;
		for(; i < group->num_commands; i++){
			kill(processes[i], SIGKILL);
		}
	}



}

/* This run_command function is a good start, but note that it runs
 the command as a replacement for the `whoosh` script, instead of
 creating a new process. */

static void run_command(script_command *command) {
	const char **argv;

	int i;

	argv = malloc(sizeof(char *) * (command->num_arguments + 2));
	argv[0] = command->program;

	for (i = 0; i < command->num_arguments; i++) {

		if (command->arguments[i].kind == ARGUMENT_LITERAL)
			argv[i + 1] = command->arguments[i].u.literal;
		else
			argv[i + 1] = command->arguments[i].u.var->value;
	}

	argv[command->num_arguments + 1] = NULL;

	Execve(argv[0], (char * const *) argv, environ);

	free(argv);
}

/* You'll likely want to use this set_var function for converting a
 numeric value to a string and installing it as a variable's
 value: */

static void set_var(script_var *var, int new_value) {
	char buffer[32];
	free((void *) var->value);
	snprintf(buffer, sizeof(buffer), "%d", new_value);
	var->value = strdup(buffer);
}
