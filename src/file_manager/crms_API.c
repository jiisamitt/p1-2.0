// Import used global libraries
#include <stdio.h>  // FILE, fopen, fclose, etc.
#include <string.h> // strtok, strcpy, etc.
#include <stdlib.h> // malloc, calloc, free, etc.
#include <unistd.h>

// Import the header file of this module
#include "crms_API.h"
extern char route_bin_file[256];

//FUNCIONES GENERALES

void cr_mount(char* memory_path)
{
    /* Funcion para montar la memoria. Establece como variable global
     la ruta local donde se encuentra el archivo .bin correspondiente a la memoria. */

    
    if (getcwd(route_bin_file, sizeof(route_bin_file)))
    {
        strcat(route_bin_file, "/");
        strcat(route_bin_file, memory_path);
        printf("Se monta la memoria\nWorking dir: %s\n",route_bin_file);
    }
    else
    {
        printf("Error montando la memoria\n");
    }

}

void cr_ls_processes()
{
    /* Funcion que muestra en pantalla los procesos en ejecución. */
    unsigned int buffer_estado = 0;
    unsigned int buffer_id = 0;
    unsigned char* buffer_nombre[12];
    FILE* file = fopen(route_bin_file, "rb");
    for (int i = 0; i < 16; i++)
    {
        fseek(file, 256*i, SEEK_SET);
        fread(&buffer_estado, 1, 1, file);
        if (buffer_estado == 1)
        {
            fseek(file, 256*i + 1, SEEK_SET);
            fread(&buffer_id, 1, 1, file);
            fseek(file, 256*i + 2, SEEK_SET);
            fread(&buffer_nombre, sizeof(unsigned char), 12, file);
            printf("ID: %d\n", buffer_id);
            char* foo = (char*) buffer_nombre;
            printf("Nombre proceso: %s\n", foo);
        } 
    }
    fclose(file);
}

int cr_exists(int process_id, char* file_name)
{
    /* Funcion para ver si un archivo con nombre file
    name existe en la memoria del proceso con id process id. 
    Retorna 1 si existe y 0 en caso contrario. */

    //Buscamos el proceso
    unsigned int buffer_estado = 0;
    unsigned int buffer_id = 0;
    unsigned char* buffer_nombre_archivo[12];
    FILE* file = fopen(route_bin_file, "rb");
    for (int i = 0; i < 16; i++)
    {
        fseek(file, 256*i, SEEK_SET);
        fread(&buffer_estado, 1, 1, file);
        if (buffer_estado == 1)
        {
            fseek(file, 256*i + 1, SEEK_SET);
            fread(&buffer_id, 1, 1, file);
            if (buffer_id == process_id)
            {
                for (int j = 0; j < 10; j++)
                //Buscamos el archivo
                {
                    unsigned int buffer_validez = 0;
                    fseek(file, 256*i + 14 + 21*j, SEEK_SET);
                    fread(&buffer_validez, 1, 1, file);
                    if (buffer_validez == 1)
                    {
                        fseek(file, 256*i + 14 + 21*j + 1, SEEK_SET);
                        fread(&buffer_nombre_archivo, sizeof(unsigned char), 12, file);

                        if (memcmp(buffer_nombre_archivo, file_name, 12) == 0)
                        {
                            printf("Existe este archivo en este proceso\n");
                            fclose(file);
                            return 1;
                        }
                    }
                    
                }
                fclose(file);
                return 0;
                
            }
        }  
    }
return 0;   
}

void cr_ls_files(int process_id)
{
    /*Funcion para listar los archivos dentro de la memoria del proceso. 
    Imprime en pantalla los nombres de todos los archivos presentes en la memoria 
    del proceso con id process id. */
    //Buscamos el proceso
    unsigned int buffer_estado = 0;
    unsigned int buffer_id = 0;
    unsigned char* buffer_nombre_archivo[12];
    FILE* file = fopen(route_bin_file, "rb");
    for (int i = 0; i < 16; i++)
    {
        fseek(file, 256*i, SEEK_SET);
        fread(&buffer_estado, 1, 1, file);
        if (buffer_estado == 1)
        {
            fseek(file, 256*i + 1, SEEK_SET);
            fread(&buffer_id, 1, 1, file);
            if (buffer_id == process_id)
            {
                for (int j = 0; j < 10; j++)
                //Buscamos el archivo
                {
                    unsigned int buffer_validez = 0;
                    fseek(file, 256*i + 14 + 21*j, SEEK_SET);
                    fread(&buffer_validez, 1, 1, file);
                    if (buffer_validez == 1)
                    {
                        fseek(file, 256*i + 14 + 21*j + 1, SEEK_SET);
                        fread(&buffer_nombre_archivo, sizeof(unsigned char), 12, file);
                        char* S1 = (char*) (buffer_nombre_archivo);
                        printf("Nombre archivo: %s\n", S1);
                    }
                    
                }
                 
            }
        }  
    }
    fclose(file);

}


//FUNCIONES PROCESOS
void cr_start_process(int process_id, char* process_name)
{
    /*Funcion que inicia un proceso con id process id y nombre process name. 
    Guarda toda la informacion correspondiente en una entrada en la tabla de PCBs.*/
}

void cr_finish_process(int process_id)
{
    /*Funcion para terminar un proceso con id process id. Es importante que antes de que el proceso
     termine se debe liberar toda la memoria asignada a este y no debe tener entrada valida en 
     la tabla de PCBs. */

}


//FUNCIONES ARCHIVOS
CrmsFile* cr_open(int process_id, char* file_name, char mode)
{
    /*Funcion para abrir un archivo perteneciente a process id. Si mode es ‘r’, 
    busca el archivo con nombre file name y retorna un CrmsFile* que lo representa. 
    Si mode es ‘w’, se verifica que el archivo no exista y se retorna un nuevo CrmsFile* que lo representa. */
    CrmsFile* file;
    return file;
}

int cr_write_file(CrmsFile* file_desc, void* buffer, int n_bytes)
{
    /*Funcion para escribir archivos. Escribe en el archivo descrito por file desc los n bytes que se encuentren en la
    direccion indicada por ´ buffer y retorna la cantidad de Bytes escritos en el archivo3
    Cabe recalcar que los archivos parten con tamano 0 y luego su tama no crece a medida que se escribe. 
    La escritura comienza desde el primer espacio libre dentro de la memoria virtual, por lo tanto, 
    no necesariamente comenzaran a escribirse desde el inicio de una pagina. Esto significa que los archivos 
    pueden compartir el mismo frame y pagina. Finalmente, la escritura se debe detener cuando:
    • No quedan frames disponibles para continuar, o´
    • Se termina el espacio contiguo en la memoria virtual, o´
    • Se escribieron los n bytes.
    */
   return 0;
}

int cr_read(CrmsFile* file_desc, void* buffer, int n_bytes)
{
    /*Funcion para leer archivos. Lee los siguientes n bytes desde el archivo descrito por file desc y los guarda en la direccion´
    apuntada por buffer. Debe retornar la cantidad de Bytes efectivamente le´ıdos desde el archivo4
    . La lectura
    de cr read se efectua recorriendo los ´ frames donde se encuentra escrito su contenido, comenzando desde la
    ultima posici ´ on le ´ ´ıda por un llamado a cr read.
    El contenido de un archivo puede estar escrito en mas de un ´ frame, por lo que, cuando se ha le´ıdo todo el
    contendido de un archivo de dicho frame, se debe continuar la lectura desde el principio del frame asociado a la
    siguiente pagina, y continuar repitiendo esto hasta completar los ´ n bytes o llegar al final del archivo. */
    return 0;
}

void cr_delete_file(CrmsFile* file_desc)
{
    /*Funcion para liberar memoria de un archivo perte- ´
    neciente al proceso con id process id. Para esto el archivo debe dejar de aparecer en la memoria virtual del
    proceso, ademas, si los ´ frames quedan totalmente libres se debe indicar en el frame bitmap que ese frame ya
    no esta siendo utilizado e invalidar la entrada correspondiente en la tabla de p ´ aginas. ´ */
}

void cr_close(CrmsFile* file_desc)
{
    /*Funcion para cerrar archivo. Cierra el archivo indicado por ´
    file desc. */
}