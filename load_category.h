#ifndef LOAD_CATEGORY_H_INCLUDED
#define LOAD_CATEGORY_H_INCLUDED

#include <stddef.h>
#include "bk_vector.h"
#include "load_category.h"
#include "load_word.h"
#include "bk_header.h"

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

int init_category(category_node** p_new_category);
int init_type(type_node** p_new_type);
int load_file_category(char** buffer);
int split_category(category_node** category_head, char* buffer);
int split_type(char* type_buffer, type_node** p_type_head);
void print_all_category(category_node* category_head);
void print_one_category(category_node* category);
void print_type(type_node* type_head);
void free_category(category_node* category_head);
void free_type(type_node* type_head);
void free_one_category(category_node* category);
void free_one_type(type_node* type);
category_node* has_category(category_node* category_head, char* category_name);
int add_category_to_db(category_node* category_head, category_node* new_category_node);
int add_category_to_file(category_node* new_category_node);
int delete_category_in_db(category_node* category_head, char* category_name);
int write_category_to_file(category_node* category_head);
#endif // LOAD_CATEGORY_H_INCLUDED
