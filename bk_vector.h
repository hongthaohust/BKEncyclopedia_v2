#ifndef BK_VECTOR_H_INCLUDED
#define BK_VECTOR_H_INCLUDED
#include "bk_string.h"
#include "bk_header.h"
/* nut dau rong */
typedef struct data_node {
    char* data;
    struct data_node* next;
} data_node;

typedef struct {
    //char data[1024];
    data_node* p_data_head;
    char* category_id;
    char* word_name;
} word_info;

typedef struct Vector {
    long used;
    long capacity;
    word_info** word_list;
} Vector;


int add_vector_element(Vector* vector, word_info*);
long search_vector_element(word_info** word_list, char* word_name, long left, long right);
int insert_vector_element(Vector* vector, word_info* new_word, long index);
int resize_vector(Vector* vector);
void free_vector(Vector* vector);
void free_word_list(word_info** word_list, long);
int init_vector(Vector** vector, int size);
int sort_vector_element(Vector* vector);
int my_quick_sort(word_info** word_list, long low, long high);
long my_parttition(word_info** word_list, long low, long high);
void remove_vector_element(Vector* vector, long index);
void remove_many_element(Vector* vector, long first_index, long last_index);
int sort_vector_element_by_id(Vector* vector);
int my_quick_sort_by_id(word_info** word_list, long low, long high);
long my_parttition_by_id(word_info** word_list, long low, long high);
#endif // BK_VECTOR_H_INCLUDED
