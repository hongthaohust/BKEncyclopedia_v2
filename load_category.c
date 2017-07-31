#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load_category.h"

int load_file_category(char** buffer, char* file_path){
    FILE* file;
    long length, alloced, byte_read;
    file = fopen(file_path,"r");
    if (file == NULL){
        printf("Khong mo duoc file");
        return -1;
    }
    *buffer = calloc(1024, sizeof(char));
    alloced = 1024;
    if (*buffer){
        while((byte_read = fread(*buffer, 1, 1024, file))){
            length += byte_read;
            if (length >= alloced){
                char* new_buff = realloc(buffer, alloced*2);
                *buffer = new_buff;
                alloced *= 2;
            }
        }
    }
    fclose(file);
    return 1;
}

int split_category(category_node** category_head, char* buffer){
    char* p_ch;
    int count = 0;
    category_node *tmp_new_category, *last_category;
    (*category_head) = calloc(1, sizeof(category_node));
    last_category = *category_head;
    if (*category_head == NULL){
        return -1;
    }
    p_ch = strtok(buffer,"\n");
    while(p_ch){
        //p_ch[strlen(p_ch)-1] = 0;
        //strtok(buffer,"\r");
        if (count%3 == 0){
            tmp_new_category = calloc(1, sizeof(category_node));
            tmp_new_category->category_id = p_ch;
            tmp_new_category->next = NULL;
            last_category->next = tmp_new_category;
            //*type_head = last_category->type_head;
            last_category = last_category->next;
            last_category->next = NULL;
        }
        else if (count%3 == 1) {
            tmp_new_category->category_name = p_ch;
        }
        else {
            /* tao ban copy cua p_ch */
            type_node* type_head;
            char* type_buffer = calloc(strlen(p_ch) + 1, 1);
            strcpy(type_buffer, p_ch);
            //count++;
            int amount_of_type = split_type(type_buffer, &type_head);
            last_category->amount_of_type = amount_of_type;
            last_category->type_head = type_head;
            p_ch = strtok(p_ch + strlen(p_ch)+ 1, "\n");
            count++;
            continue;
            //p_ch += amount_of_type;
        }
        p_ch = strtok(NULL, "\n");
        count++;
    }
    printf("So dong: %d", count);
    return 1;
}

int split_type(char* type_buffer, type_node** p_type_head){
    int count = 1;
    type_node *type_head, *type_curr;
    char* sub_str;
    //type_buffer[strlen(type_buffer)-1] = 0;
    sub_str = strtok(type_buffer, ";");
    type_head = *p_type_head;
    //printf("%d", sizeof(type_node));
    //fflush(stdout);
    type_head = calloc(1,sizeof(type_node));
    if (type_head == NULL)
        return -1;
    *p_type_head = type_head;
    type_curr = type_head;
    type_curr->type_name = sub_str;
    while((sub_str = strtok(NULL, ";"))){
        type_node* type_new = calloc(1, sizeof(type_node));
        type_new->type_name = sub_str;
        type_curr->next = type_new;
        type_curr = type_curr->next;
        type_curr->next = NULL;
        count++;
    }
    //p_curr->next = NULL;
    return count;
}

void print_category(category_node* category_head){
    if (category_head == NULL)
        return;
    category_node* category_curr = category_head->next;
    while(category_curr){
        printf("Ten: %s\n", category_curr->category_name);
        printf("id: %s\n", category_curr->category_id);
        printf("amount of type: %d\n", category_curr->amount_of_type);
        print_type(category_curr->type_head);
        category_curr = category_curr->next;
    }
}

void print_type(type_node* type_head){
    type_node* type_curr = type_head;
    printf("Cac truong: ");
    while(type_curr){
        printf("%s; ", type_curr->type_name);
        type_curr = type_curr->next;
    }
    printf("\n");
}

void free_category(category_node* category_head){
    category_node* category_curr;
    category_node* category_prev;
    if (category_head == NULL)
        return;
    category_curr = category_head;
    while(category_curr){
        category_prev = category_curr;
        category_curr = category_curr->next;
        free(category_prev->category_id);
        free(category_prev->category_name);
        free_type(category_prev->type_head);
    }
}

void free_type(type_node* type_head){
    type_node* type_curr;
    type_node* type_prev;
    if (type_head == NULL)
        return;
    type_curr = type_head;
    while(type_curr){
        type_prev = type_curr;
        type_curr = type_curr->next;
        free(type_prev->type_name);
        free(type_prev);
    }
    //free(type_curr)
}

category_node* has_category(category_node* category_head, char* category_name){
    category_node* category_curr;
    //int check;
    if (category_head == NULL)
        return NULL;
    category_curr = category_head->next;
    while(category_curr){
        if (strcmp(category_name, category_curr->category_name) == 0)
            return category_curr;
        category_curr = category_curr->next;
    }
    return NULL;
}
