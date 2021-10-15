#include <stdio.h>
#include "../file_manager/crms_API.h"
#include "string.h"
extern char route_bin_file[256];
int main(int argc, char **argv)
{
  
  printf("Hello P1!\n");
  cr_mount(argv[1]);
  //cr_start_process(29, "test.txt_");
  //cr_finish_process(29);
  //cr_ls_processes();
  //cr_exists(0, "secret.txt");
  //cr_ls_files(0);
  //REVISAR ERROR CON PRINT DE ATRIBUTOS DE STRUCT
  //CrmsFile* file = cr_open(0, "secret.txt", 'r');
  //printf("Test cr_open: %s %i\n", file->file_name, file->id_process);

}


