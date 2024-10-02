#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "../input_manager/manager.h"

#define MAX_CMD_LEN 1024

int main()
{
    char cmd[MAX_CMD_LEN];

    // Configura el manejador de señales para evitar procesos zombies
    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    while (1)
    {
        printf("Nico&Vicho's : "); // Prompt de la shell
        fflush(stdout);
        // Leer comando desde la entrada estándar
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            break; // Salir si se alcanza EOF
        }
        // Remover el salto de línea al final del comando
        cmd[strcspn(cmd, "\n")] = 0;

        // Si el comando es "lrexit", salir de la shell
        if (strcmp(cmd, "lrexit") == 0)
        {
            sigint_handler();
            break;
        }

        // Crear proceso hijo para ejecutar el comando
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {                         // Proceso hijo
            execute_command(cmd); // Ejecuta el comando hijo
            exit(EXIT_SUCCESS);   // Terminar proceso hijo
        }
        else
        { // Proceso padre
            process_count++;
            // Esperar a que el proceso hijo termine
            shell_processes[process_count].pid = pid;
            strcpy(shell_processes[process_count].name, cmd);
            shell_processes[process_count].start_time = time(NULL);
            shell_processes[process_count].exit_code = -1;
            waitpid(pid, NULL, 0);
            shell_processes[process_count].end_time = time(NULL);
            shell_processes[process_count].exit_code = 0;
        }
    }

    return 0;
}
