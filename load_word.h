#ifndef LOAD_WORD_H_INCLUDED
#define LOAD_WORD_H_INCLUDED

#include "bk_vector.h"
int load_file(char**, char*);
int split_word_infor(Vector* vector, char* buffer, int size_type);
int get_new_word_index(Vector* vector, word_info* new_word);
void print_word(word_info* word);
void print_word_data(data_node* p_data_head);
void print_vector(Vector* vector);

#endif // LOAD_WORD_H_INCLUDED
