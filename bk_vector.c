#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bk_vector.h"
#include "bk_string.h"
int init_vector(Vector** vector, int size){
    *vector = calloc(1, sizeof(vector));
    if (vector == NULL)
        return -1;
    (*vector)->capacity = size;
    (*vector)->used = 0;
    (*vector)->word_list = calloc(size, sizeof(word_info*));
    if ((*vector)->word_list == NULL)
        return -1;
    return 1;
}

int resize_vector(Vector* vector){
    size_t new_size = (vector->capacity) * 2 ;
    word_info** new_word_list = realloc(vector->word_list, new_size* sizeof(word_info*));
    if (new_word_list == NULL){
       printf("Khong cap phat duoc\n");
       return -1;
    }

    vector->word_list = new_word_list;
    vector->capacity *= 2;
    return 1;
}

int add_vector_element(Vector* vector, word_info* new_word){
    if (vector->used == vector->capacity){
        resize_vector(vector);
    }
    vector->word_list[(vector->used)++] = new_word;
    return 1;
}


/* insert 1 tu vao mang word_list */
int insert_vector_element(Vector* vector, word_info* new_word, int index){
    if (index < 0 || index > vector->used)
        return -1;
    if (vector->used == vector->capacity)
        resize_vector(vector);
    word_info** word_list = vector->word_list;
    int word_size = vector->used;
    /* Dich trai cac phan tu ke tu index */
    for (int i = word_size-1; i >= index; i--){
        vector->word_list[i+1] = vector->word_list[i];
    }
    word_list[index] = new_word;
    (vector->used)++;
    return 1;
}

/* Tim nhi phan */
int search_vector_element(word_info** word_list, char* word_name, int left, int right){
    //int word_size = vector->used;
    int middle = (left + right)/2;
    char lower_word_name[128];
    char lower_middle_word_name[128];

    if (left > right)
        return -1;
    /* Cho ve chuoi chu thuong */
    to_lower_string(word_name, lower_word_name);
    to_lower_string(word_list[middle]->word_name, lower_middle_word_name);
    if (strcmp(lower_middle_word_name, lower_word_name) == 0)
        return middle;
    else if (strcmp(lower_middle_word_name, lower_word_name) < 0)
        return search_vector_element(word_list, word_name, middle+1, right);
    else
        return search_vector_element(word_list, word_name, left, middle-1);
}
