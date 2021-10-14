// Tells the compiler to compile this file once
#pragma once

//Global variables
char route_bin_file[256];

// Define the struct
typedef struct CrmsFile {
  int len;
  char*** lines;  // This is an array of arrays of strings
} CrmsFile;


void cr_mount(char* memory_path);

void cr_ls_processes();

int cr_exists(int process_id, char* file_name);

void cr_ls_files(int process_id);

void cr_start_process(int process_id, char* process_name);

void cr_finish_process(int process_id);

CrmsFile* cr_open(int process_id, char* file_name, char mode);

int cr_write_file(CrmsFile* file_desc, void* buffer, int n_bytes);

int cr_read(CrmsFile* file_desc, void* buffer, int n_bytes);

void cr_delete_file(CrmsFile* file_desc);

void cr_close(CrmsFile* file_desc);