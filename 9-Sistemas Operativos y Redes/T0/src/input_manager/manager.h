#ifndef MANAGER_H
#define MANAGER_H

#include <sys/wait.h>
#include <time.h>

struct ProcessInfo
{
    pid_t pid;
    char name[20];
    time_t start_time;
    time_t end_time;
    int exit_code;
};
#define MAX_PROCESSES 100
extern pid_t current_child_pid;
extern struct ProcessInfo shell_processes[MAX_PROCESSES];
extern int process_count;
extern int kill(pid_t pid, int sig);
// Prototypes for the functions
void sigchld_handler();
void sigint_handler();
void sigtstp_handler();

void execute_command(char *cmd);
void execute_hello();
void execute_sum(char *num1_str, char *num2_str);
void execute_is_prime(char *numero_str);
void lrexec(const char *executable, char *const argv[]);
void execute_lrlist();

#endif
