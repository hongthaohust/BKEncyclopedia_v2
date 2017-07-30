#ifndef LOAD_CATEGORY_H_INCLUDED
#define LOAD_CATEGORY_H_INCLUDED

#define CATEGORY_NAME_SIZE 128
#include "bk_vector.h"
#include "load_word.h"
typedef struct type_node {
    char* type_name;
    struct type_node* next;
} type_node;

/* Nut dau rong */
typedef struct category_node {
    char* category_id;
    char* category_name;
    size_t amount_of_type;  // So cac truong
    size_t amount_of_word;  // So cac  tu
    type_node* type_head;
    struct category_node* next;
} category_node;

int load_file_category(char** buffer, char* file_path);
int split_category(category_node** category_head, char* buffer);
int split_type(char* type_buffer, type_node** p_type_head);
void print_category(category_node* category_head);
void print_type(type_node* type_head);
#endif // LOAD_CATEGORY_H_INCLUDED
