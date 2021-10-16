#  Proyecto 1 - smmjf
## Integrantes

+ Maria Ignacia González - 14637197
+ Juan Isamitt - 16637607
+ Felipe Willmer - 16624270
+ Sebastian Villablanca - 17641454
+ Matías Aedo - 17205689


## Decisiones de diseño
Se siguieron las instrucciones indicadas en el enunciado respecto al diseño de la API. El struct CrmsFile almacena información respectiva al archivo abierto (nombre, id de proceso, tamaño de archivo, dirección, bytes escritos y bytes leídos). Las funciones indicadas en el enunciado se encuentran en el archivo crms_API.c mientras que el resto de funciones útiles se modularizaron en el archivo functions.c

## Biblioteca
A continuación se listan las funciones implementadas:
+ cr_mount: Funciona
+ cr_ls_processes: Funciona
+ cr_exists: Funciona
+ cr_ls_files: Funciona
+ cd_start_process: Funciona
+ cr_finish_process: Funciona
+ cr_open: Funciona correctamente pero tiene un comportamiento extraño al hacer printf en main.c de algún atributo del struct. En lugar de imprimir lo que se pide, no retorna el struct y el flujo es incorrecto. Cuando no se hace el printf en main.c y se hace dentro de la función justo antes de retornar el CrmsFile, funciona como corresponde y en terminal se confirma que siguió el flujo esperado.