#ifndef FILE_PROCESS_H_INCLUDED
#define FILE_PROCESS_H_INCLUDED

char* get_file_path(char* file_path, char* file_name);
FILE* get_category_file_pointer(char* permission);
int is_file_exist(char* fname);
#endif // FILE_PROCESS_H_INCLUDED
