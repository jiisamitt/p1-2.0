// Import used global libraries
#include <stdio.h>  // FILE, fopen, fclose, etc.
#include <string.h> // strtok, strcpy, etc.
#include <stdlib.h> // malloc, calloc, free, etc.
#include <unistd.h>

// Import the header file of this module
#include "crms_API.h"

CrmsFile* crms_file_init(int id_process, char *file_name)
{
    CrmsFile *self = malloc(1*sizeof(CrmsFile));
    self -> file_name = file_name;
    self -> id_process = id_process;
    return self;
}

void file_destroy(CrmsFile* self)
{
  free(self);
}