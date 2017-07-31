#include <string.h>
#include "file_process.h"


char* get_file_path(char* file_path, char* file_name){
    strcat(file_path, prefix_file_path);
    strcat(file_path, file_name);
    strcat(file_path, surfix_file_path);
    return file_path;
}
