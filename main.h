#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "bk_vector.h"
#include "load_category.h"
#include "load_word.h"
#include "validate_input.h"
#include "file_process.h"
int load_word(category_node* category_head, Vector* vector, char** p_word_buffer);
int menu();
int search_word(Vector*);
int add_word_func(Vector* vector, category_node* category_head);
int edit_word(Vector* vector);
int print_word_category(Vector* vector, category_node* category_head);
void print_category_infor(category_node* category_head);
int add_category(category_node* category_head);
int edit_category(category_node* category_head);
int delete_category(Vector* ,category_node* category_head);
int remove_word(Vector* vector, category_node* category_head);

#endif // MAIN_H_INCLUDED
