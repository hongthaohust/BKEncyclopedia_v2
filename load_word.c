#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_word.h"

int load_file(char** buffer, char* file_path){
    //Vector vector[12];
    FILE* file;
    long length;
    file = fopen(file_path,"rb");
    if (file == NULL){
        printf("Khong mo duoc file");
        return -1;
    }
    fseek (file, 0, SEEK_END);
    length = ftell (file);
    fseek (file, 0, SEEK_SET);
    *buffer = calloc(length, sizeof(char));
    if (*buffer){
        fread (*buffer, 1, length, file);
    }
    fclose(file);
    return 1;
}


/* Lay cac word tu buffer roi truyen vao cau truc du lieu tuong ung */
int split_word_infor(Vector* vector, char* buffer, int size_type){
    char* p_ch;
    int count = 0;
    word_info *p_word;
    data_node *p_data_head, *p_data_curr, *p_data_last;
    p_ch = strtok(buffer, "\n");
    while(p_ch){
         /* Xoa ki tu \r trong windows */
        p_ch[strlen(p_ch) - 1] = 0;
        if (count%size_type ==  0){
            p_word = calloc(1, sizeof(word_info));
            p_data_head = calloc(1, sizeof(data_node));
            p_data_curr = p_data_head;
            p_data_last = p_data_head;
            p_word->p_data_head = p_data_head;
            //strcpy(p_word->word_name, p_ch);
            p_word->word_name = p_ch;
        }
        else if (count%size_type == 1){
            p_word->category_id = p_ch;
        }
        /* Truong hop duyet toi dong cuoi cung 1 tu */
        else if (count%size_type == (size_type-1)){
            p_data_curr = calloc(1, sizeof(data_node));
            p_data_last->next = p_data_curr;
            //strcpy(p_data_curr->data, p_ch);
            p_data_curr->data = p_ch;
            p_data_curr->next = NULL;
            int new_index = get_new_word_index(vector, p_word);
            if (new_index < vector->used)
                insert_vector_element(vector, p_word, new_index);
            else
                add_vector_element(vector, p_word);
            //add_vector_element(vector, p_word);
        }
        else {
            p_data_curr = calloc(1, sizeof(data_node));
            p_data_last->next = p_data_curr;
            p_data_last = p_data_curr;
            //strcpy(p_data_curr->data, p_ch);
            p_data_curr->data = p_ch;
            p_data_curr = p_data_curr->next;
        }
        //free(p_ch);
        p_ch = strtok(NULL, "\n");
        count++;
    }
    //free(buffer);
    return count;
}

int get_new_word_index(Vector* vector, word_info* new_word){
    int word_size = vector->used;
    word_info** word_list = vector->word_list;
    int count = 0;

    if (word_list[0] == NULL)
        return count;

    while( count < word_size && (strcmp(word_list[count]->word_name, new_word->word_name) < 0) ){
        count++;
    }

    return count;
}

void print_vector(Vector* vector){
    if (vector == NULL)
        return;
    //printf("%d", vector->used);
    for(int i = 0; i < vector->used; i++){
        print_word(vector->word_list[i]);
    }
}

void print_word(word_info* word){
    printf("%s\n",word->word_name);
    printf("%s\n",word->category_id);
    print_word_data(word->p_data_head);
}

void print_word_data(data_node* p_data_head){
    if (p_data_head == NULL)
        return;
    data_node* p_data_curr = p_data_head->next;
    while(p_data_curr){
        printf("%s\n",  p_data_curr->data);
        p_data_curr = p_data_curr->next;
    }
}

