#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "parser.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char *argv[], char *envp[]) {
    list_t *list = parse(envp);
    list_t *children = list_init();
    char **array = (char **) malloc (list->zaehler * sizeof(char *));
    array = list_to_array(list);
    if (strcmp(array[0], "exit") == 0) {
        return 0;
    }
    int pid = fork();
    // Kindprozess
    if (pid == 0) {
        char *path = getenv("PATH");
        char *command = (char*) malloc (sizeof(array[0]));
        command = strcat(command,array[0]);
        int end = 0; // hilfsvariable zum iterieren durch path
        int i = 0; // hilfsvariable zum iterieren durch help
        char *help = (char *) malloc(sizeof(path)+sizeof(array[0])+sizeof(char)); // Speichert aktuelles Verzeichnis
        while (true) {
            if (path[end] == ':' || path[end] == '\0') {
                help[i] = '/';
                help = strcat(help, command); // Anhängen des Kommandos and Pfad
                // Kommando nicht gefunden
                if (execve(help, array, envp) == -1 && end == strlen(path)) {
                    //free(help);
                    return -1;
                }
                i = 0;
            }
            else {
                help[i] = path[end];
                ++i;
            }
            ++end;
        }
    }
    // Elternprozess
    else {
        // Umwandlung von int pid in char array zur Übergabe an list_add()
        char* PID = (char*) malloc (sizeof(char*) * 2); 
        PID[0] = pid + '0';
        PID[1] = '\0';
        list_add(children, PID, 2); // Einfügen des Prozesses in liste
        wait(NULL);
    }
}
    