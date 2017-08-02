#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bk_vector.h"


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
int insert_vector_element(Vector* vector, word_info* new_word, long index){
    long amount_of_word;
    if (index < 0 || index > vector->used)
        return -1;
    if (vector->used == vector->capacity)
        resize_vector(vector);
    word_info** word_list = vector->word_list;
    amount_of_word = vector->used;
    /* Dich trai cac phan tu ke tu index */
    for (int i = amount_of_word-1; i >= index; i--){
        vector->word_list[i+1] = vector->word_list[i];
    }
    word_list[index] = new_word;
    (vector->used)++;
    return 1;
}

/* Tim nhi phan */
long search_vector_element(word_info** word_list, char* word_name, long left, long right){
    //int word_size = vector->used;
    long middle = left + (right - left)/2;
    char lower_word_name[WORD_NAME_SIZE];
    char lower_middle_word_name[WORD_NAME_SIZE];

    if (left > right)
        return -1;
    /* convert ve chu HOA -> thuong */
    to_lower_string(word_name, lower_word_name);
    to_lower_string(word_list[middle]->word_name, lower_middle_word_name);
    if (strcmp(lower_middle_word_name, lower_word_name) == 0)
        return middle;
    else if (strcmp(lower_middle_word_name, lower_word_name) < 0)
        return search_vector_element(word_list, word_name, middle+1, right);
    else
        return search_vector_element(word_list, word_name, left, middle-1);
}

int sort_vector_element(Vector* vector){
    long low;
    long high;
    if (vector == NULL)
        return -1;
    word_info** word_list = vector->word_list;
    low = 0;
    high = vector->used - 1;
    my_quick_sort(word_list, low, high);
    return 1;
}

int my_quick_sort(word_info** word_list, long low, long high){
    long pivot_pos;
    if (low < high){
        pivot_pos = my_parttition(word_list, low, high);
        my_quick_sort(word_list, low, pivot_pos-1);
        my_quick_sort(word_list, pivot_pos+1, high);
    }
    return 1;
}

long my_parttition(word_info** word_list, long low, long high){
    char pivot_word_name[WORD_NAME_SIZE];
    char compared_word_name[WORD_NAME_SIZE];
    word_info* pivot;
    word_info* tmp_word;
    pivot = word_list[high];
    long i, j;
    i = low - 1;
    to_lower_string(pivot->word_name, pivot_word_name);
    for (j = low; j <= high - 1; j++ ){
        to_lower_string(word_list[j]->word_name, compared_word_name);
        if (strcmp(compared_word_name, pivot_word_name) <= 0){
            i++;
            tmp_word = word_list[i];
            word_list[i] = word_list[j];
            word_list[j] = tmp_word;
        }
    }
    tmp_word = word_list[i+1];
    word_list[i+1] = word_list[high];
    word_list[high] = tmp_word;
    return i+1;
}

int sort_vector_element_by_id(Vector* vector){
    long low;
    long high;
    if (vector == NULL)
        return -1;
    word_info** word_list = vector->word_list;
    low = 0;
    high = vector->used - 1;
    my_quick_sort_by_id(word_list, low, high);
    return 1;
}

int my_quick_sort_by_id(word_info** word_list, long low, long high){
    long pivot_pos;
    if (low < high){
        pivot_pos = my_parttition_by_id(word_list, low, high);
        my_quick_sort_by_id(word_list, low, pivot_pos-1);
        my_quick_sort_by_id(word_list, pivot_pos+1, high);
    }
    return 1;
}

long my_parttition_by_id(word_info** word_list, long low, long high){
    //char pivot_category_id[CATEGORY_ID_SIZE];
    //char compared_category_id[CATEGORY_ID_SIZE];
    word_info* pivot;
    word_info* tmp_word;
    pivot = word_list[high];
    long i, j;
    i = low - 1;
    //to_lower_string(pivot->word_name, pivot_category_id);
    for (j = low; j <= high - 1; j++ ){
        //to_lower_string(word_list[j]->word_name, compared_category_id);
        if (strcmp(word_list[j]->category_id, pivot->category_id) <= 0){
            i++;
            tmp_word = word_list[i];
            word_list[i] = word_list[j];
            word_list[j] = tmp_word;
        }
    }
    tmp_word = word_list[i+1];
    word_list[i+1] = word_list[high];
    word_list[high] = tmp_word;
    return i+1;
}

/* Xoa phan tu trong vector va giam kich thuoc mang dong di 1*/
void remove_vector_element(Vector* vector, long index){
    long amount_of_word = vector->used;
    word_info** word_list;
    word_list = vector->word_list;
    for (long i = index; i < amount_of_word - 1;i++){
        word_list[i] = word_list[i+1];
    }
    vector->used--;
}

void remove_many_element(Vector* vector, long first_index, long last_index){
    word_info** word_list;
    long amount_of_word;
    long distance;
    word_list = vector->word_list;
    amount_of_word = vector->used;
    distance = last_index - first_index;
    for(long i = last_index + 1; i < amount_of_word; i++){
        word_list[i-distance] = word_list[i];
    }
    vector->used -= (distance + 1);
}
void free_vector(Vector* vector){
    if (vector == NULL)
        return;
    free(vector->word_list);
    free_word_list(vector->word_list, vector->used);
    free(vector);
}

void free_word_list(word_info** word_list, long word_size){
    for (long i = 0; i < word_size; i++){
        free(word_list[i]);
    }
}
