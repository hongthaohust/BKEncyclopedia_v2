#ifndef BK_VECTOR_H_INCLUDED
#define BK_VECTOR_H_INCLUDED

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
    int used;
    int capacity;
    word_info** word_list;
} Vector;


int add_vector_element(Vector* vector, word_info*);
int search_vector_element(word_info** word_list, char* word_name, int left, int right);
int insert_vector_element(Vector* vector, word_info* new_word, int index);
int resize_vector(Vector* vector);
int free_vector(Vector* vector);
int free_word_list(word_info* word);
int init_vector(Vector** vector, int size);

#endif // BK_VECTOR_H_INCLUDED
