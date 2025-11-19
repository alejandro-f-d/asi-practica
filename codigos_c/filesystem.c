#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define COMP_SIN_CAMBIOS 128
#define ERR_NO_SUPERUSER 1
#define ERR_DISP_BLOQUES 3
#define ERR_SYSFICH 4
#define ERR_EXIST 5 
#define ERR_CREAR_FILESYS 6
#define ERR_DELS_FILESYS 7
#define ERR_ARGS 2
#define ERR_FORK 8


/*
 * TODO: Verificar si el sistema de ficheros ya posee el sistema de ficheros a generar.
 * TODO: Verificar si existe el disco sobre el que se va a realizar el proceso. 
 * TODO: Verificar en caso de que existe que se trata de un sistema de fichero de bloques.
 * TODO: Hacer los headers. Mover los define y los include.
 * TODO: ERROR 5, 1, 128, 6, 7.
 * TODO: Realizar alguna prueba de que funciona los códigos que se van haciendo. 
*/

int procesoVerificarSysFich(char *sysFich) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(ERR_FORK);
    }

    if (pid == 0) {
        size_t tam = 32 + strlen(sysFich) + 1;
        char * cmd = calloc(32 + strlen(sysFich) + 1, sizeof(char));;
        snprintf(cmd, tam,
                 "cat /proc/filesystems | grep -w %s", sysFich);

        execl("/bin/sh", "sh", "-c", cmd, NULL);

        perror("execl");
        exit(1);
    } else{
        int status;
        waitpid(pid, &status, 0);
        printf("Código de salida: %d\n", WEXITSTATUS(status));
        return WEXITSTATUS(status);
    }
}





// Hay que utilizar blkid.

int execBlkid(){
  pid_t ejecutor_hijo; 
  ejecutor_hijo = fork();
    if(ejecutor_hijo == -1){
        fprintf(stderr, "Error al crear el proceso hijo.\n");
        perror("fork");
        // exit en el proceso padre.
    exit(ERR_FORK);
    } else if(ejecutor_hijo == 0){

    } else {
        int status_terminacion;
        waitpid(ejecutor_hijo, &status_terminacion, 0);
        // Aquí se haría el estudio del estado de terminación dependiendo de cual sea el padre termina de una manera o de otra.
    }
    return 0;
}


int filesystem(char * disk, char * state, char * fs_type, char * force, char * opts){
  /*
  0: se ha completado correctamente realizando cambios: se ha creado o eliminado un sistema de ficheros.
  128: se ha completado correctamente pero sin realizar cambios.
  1: error por la ejecución sin ser superusuario.
  2: error en los argumentos.
  3: disk no es un dispositivo de bloques.
  4: fs_type no es un tipo de sistema de ficheros soportado en el equipo
  5: ya existía un sistema de ficheros de otro tipo y force es igual a false.
  6: error en mandato que crea el sistema de ficheros.
  7: error en mandato que elimina el sistema de ficheros.
  * */
    // Verificación inicial de los parámetros de entrada.

    if(disk == NULL || (strcmp(state, "present") && fs_type == NULL)){
        fprintf(stderr, "Error con los parámetros obligatorios.\n");
        exit(ERR_ARGS);
    }
    // Verificación de que el sistema de ficheros deseado existe:
    if(procesoVerificarSysFich(fs_type) != 0){
        exit(ERR_EXIST);
    }
    return 0;
}
