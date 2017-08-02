#ifndef LOAD_WORD_H_INCLUDED
#define LOAD_WORD_H_INCLUDED
#include "bk_vector.h"

int init_new_word(word_info** p_new_word);
int init_new_data_node(data_node** p_new_data);
int load_file(char**, char*);
int split_word_infor(Vector* vector, char* buffer, int size_type);
long get_new_word_index(Vector* vector, word_info* new_word);
void print_word(word_info* word);
void print_word_data(data_node* p_data_head);
void print_vector(Vector* vector);
int add_word_to_file(char* file_name, word_info* new_word);
int edit_word_in_db(Vector*,word_info* old_word, word_info* new_word, long);
void print_only_word(Vector* vector);
void print_wordname_in_category(Vector* vector, char* category_id);
int remove_word_in_category(Vector* vector, char* category_id);

#endif // LOAD_WORD_H_INCLUDED
