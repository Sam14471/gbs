#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "parser.h"

int main (int argc, char *argv[], char *envp[]) {
    //list_t list = parse(envp);
    char **array = list_to_array(list);
    int pid = fork();
    if (pid = 0) {
        // pfadnamen suchen (use getenv)
        // parsen von $PATH
        // durchgehen durch verzeichnissen
        // für jedes verzeichnis slash und Kommandonamen (argv[0]) anfügen
        // test durch übergabe an execve()
}
    }
    else {
        list_t children = list_init();
        //list_add(children, ) // pid als int in char array umwandeln und übergeben
        wait(pid);
    }
    