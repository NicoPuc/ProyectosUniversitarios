#include "manager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h> //waitpid
#include <stdlib.h>   //atof
#include <errno.h>

struct ProcessInfo shell_processes[MAX_PROCESSES];
int process_count = 0;

void sigchld_handler()
{
    // Espera por todos los procesos hijos que hayan terminado
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void sigint_handler()
{
    if (shell_processes[process_count].pid > 0)
    {
        kill(shell_processes[process_count].pid, SIGINT); // Envía SIGINT al proceso hijo actual
    }

    sleep(10); // Esperar 10 segundos para que los procesos hijos terminen

    if (shell_processes[process_count].pid > 0)
    {
        kill(shell_processes[process_count].pid, SIGKILL); // Envía SIGKILL si el proceso hijo aún no ha terminado
    }
}

void sigtstp_handler()
{
    if (shell_processes[process_count].pid > 0)
    {
        kill(shell_processes[process_count].pid, SIGTSTP);
    }
    printf("\nProceso suspendido.\n");
}

void execute_command(char *cmd)
{
    char *args[16];
    int i = 0;
    args[i] = strtok(cmd, " ");
    while (args[i] != NULL && i < 15)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
    args[i] = NULL; // Terminar el array de argumentos

    if (strcmp(args[0], "hello") == 0)
    {
        execute_hello();
    }
    else if (i == 3 && strcmp(args[0], "sum") == 0)
    {
        execute_sum(args[1], args[2]);
    }
    else if (i == 2 && strcmp(args[0], "is_prime") == 0)
    {
        execute_is_prime(args[1]);
    }
    else if (strcmp(args[0], "lrexec") == 0)
    {
        if (i > 1)
        {
            lrexec(args[1], &args[1]); // Llama a lrexec pasando el ejecutable y los argumentos
        }
        else
        {
            printf("Usage: lrexec <executable> <arg1> <arg2> ...\n");
        }
    }
    else if (strcmp(args[0], "lrlist") == 0)
    {
        execute_lrlist();
    }
}

void execute_hello()
{
    printf("Hello World!\n");
}

void execute_sum(char *num1_str, char *num2_str)
{
    double num1 = atof(num1_str);
    double num2 = atof(num2_str);
    double result = num1 + num2;
    printf("Suma: %.2f\n", result);
}

void execute_is_prime(char *numero_str)
{
    int numero = atoi(numero_str);
    int primo = 1;
    if (numero < 2)
    {
        primo = 0;
    }
    else
    {
        for (int i = 2; i < numero; i++)
        {
            if (numero % i == 0)
            {
                primo = 0;
                break;
            }
        }
    }
    if (primo)
    {
        printf("%d es primo.\n", numero);
    }
    else
    {
        printf("%d no es primo.\n", numero);
    }
}

void lrexec(const char *executable, char *const argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Proceso hijo
        execvp(executable, argv); // EJECUCION
        // Si execvp falla
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Proceso padre
        int status;
        if (waitpid(pid, &status, 0) < 0)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

void execute_lrlist()
{
    for (int i = 0; i < process_count; i++)
    {
        time_t start_time = shell_processes[i].start_time;
        time_t end_time = shell_processes[i].end_time;
        time_t execution_time = end_time - start_time;
        printf("Process %d: PID %d, Name: %s, Execution Time: %ld seconds, Exit Code: %d\n",
               i + 1, shell_processes[i].pid, shell_processes[i].name,
               execution_time, shell_processes[i].exit_code);
    }
}