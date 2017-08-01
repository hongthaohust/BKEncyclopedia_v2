#include <string.h>
#include <stdio.h>
#include "file_process.h"
char* prefix_file_path = "data/";
char* surfix_file_path = ".txt";

char* get_file_path(char* file_path, char* file_name){
    strcat(file_path, prefix_file_path);
    strcat(file_path, file_name);
    strcat(file_path, surfix_file_path);
    return file_path;
}

FILE* get_category_file_pointer(char* permission){
    FILE* category_file;
    category_file = fopen("data/theloai.txt",permission);
    if (category_file)
        return category_file;
    category_file = fopen("data/the loai.txt",permission);
    if (category_file)
        return category_file;
    category_file = fopen("data/theloai",permission);
        return category_file;
    return NULL;
}
