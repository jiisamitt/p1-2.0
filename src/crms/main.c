#include <stdio.h>
#include "../file_manager/crms_API.h"
#include "string.h"
extern char route_bin_file[256];
int main(int argc, char **argv)
{
  
  printf("Hello P1!\n");
  cr_mount(argv[1]);
  cr_ls_processes();
  cr_exists(0, "secret.txt");
  cr_ls_files(0);
}


