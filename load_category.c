#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load_category.h"
#include "file_process.h"
char* category_file_path = "data/theloai.txt";
int init_category(category_node** p_new_category){
    category_node* new_category;
    new_category = calloc(1, sizeof(category_node));
    if (new_category == NULL)
        return -1;
    new_category->category_id = calloc(CATEGORY_ID_SIZE, sizeof(char));
    new_category->category_name = calloc(CATEGORY_NAME_SIZE, sizeof(char));
    //new_category->type_head = calloc(1, sizeof(type_node));
    *p_new_category = new_category;
    return 1;
}

int init_type(type_node** p_new_type){
    type_node* new_type = calloc(1, sizeof(type_node));
    if (new_type == NULL)
        return -1;
    new_type->type_name = calloc(TYPE_NAME_SIZE, sizeof(char));
    if (new_type->type_name == NULL)
        return 1;
    *p_new_type = new_type;
    return 1;
}

int load_file_category(char** p_buffer){
    FILE* file;
    char* buffer;
    long length, alloced, byte_read;
    file = get_category_file_pointer("r");
    if (file == NULL){
        return -1;
    }
    buffer = calloc(1024, sizeof(char));
    alloced = 1024;
    if (buffer){
        while((byte_read = fread(buffer, 1, 1024, file))){
            length += byte_read;
            if (length >= alloced){
                char* new_buff = realloc(buffer, alloced*2);
                buffer = new_buff;
                alloced *= 2;
            }
        }
    }
    *p_buffer = buffer;
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
    //printf("So dong: %d", count);
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

void print_all_category(category_node* category_head){
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

void print_one_category(category_node* category){
    if (category == NULL)
        return;
    printf("Ten: %s\n", category->category_name);
    printf("id: %s\n", category->category_id);
    //printf("amount of type: %d\n", category->amount_of_type);
    print_type(category->type_head);
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

void free_one_category(category_node* category){
    if (category == NULL)
        return;
    free(category->category_id);
    free(category->category_name);
    free(category);
    //free(category->)
}

void free_one_type(type_node* type){
    if (type == NULL)
        return;
    free(type->type_name);
    free(type);
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

category_node* get_last_category_node(category_node* category_head){
    category_node* category_curr;
    if (category_head == NULL)
        return NULL;
    category_curr = category_head;
    while(category_curr->next){
        category_curr = category_curr->next;
    }
    return category_curr;
}

int add_category_to_db(category_node* category_head, category_node* new_category_node){
    category_node* last_category_node;
    last_category_node = get_last_category_node(category_head);
    if (last_category_node == NULL)
        return -1;
    last_category_node->next = new_category_node;
    return 1;
}

int add_category_to_file(category_node* new_category_node){
    FILE* file;
    type_node* type_head;
    type_node* type_curr;
    file = fopen(category_file_path,"a+");
    if (file == NULL){
        printf("Khong mo duoc file the loai");
        return -1;
    }
    type_head = new_category_node->type_head;
    type_curr = type_head;
    fprintf(file,"\n%s",new_category_node->category_id);
    fprintf(file,"\n%s", new_category_node->category_name);
    fprintf(file, "\n%s", type_curr->type_name);
    while(type_curr = type_curr->next){
        fprintf(file,";%s",type_curr->type_name);
    }
    fclose(file);
    return 1;
}

int delete_category_in_db(category_node* category_head, char* category_name){
    category_node* category_curr;
    category_node* category_prev;
    if (category_head == NULL)
        return -1;
    category_curr = category_head->next;
    category_prev = category_head;
    while(category_curr && strcmp(category_curr->category_name, category_name) ){
        category_prev = category_curr;
        category_curr = category_curr->next;
    }
    /* Truong hop khong tim thay */
    if (category_curr == NULL){
        return -1;
    }
    category_prev->next = category_curr->next;
    return 1;
}

int write_category_to_file(category_node* category_head){
    category_node* category_curr;
    type_node* type_curr;
    FILE* category_file;
    int error;
    if (category_head == NULL)
        return -1;
    category_file = fopen("data/tmp_category", "a+");
    if (category_file == NULL)
        return -1;
    category_curr = category_head->next;
    while(category_curr){
        type_curr = category_curr->type_head;
        fprintf(category_file,"%s\n",category_curr->category_id);
        fprintf(category_file,"%s\n",category_curr->category_name);
        fprintf(category_file, "%s",type_curr->type_name);
        type_curr = type_curr->next;
        while(type_curr){
            fprintf(category_file,";%s",type_curr->type_name);
            type_curr = type_curr->next;
        }
        category_curr = category_curr->next;
        fprintf(category_file,"\n");
    }
    fclose(category_file);
    error = remove(category_file_path);
    if (error){
        printf("Khong xoa file thanh cong");
        return -1;
    }
    /* Neu khong con the loai nao thi ta xoa luon file the loai */
    if (category_head->next == NULL){
        remove("data/tmp_category");
        return 1;
    }
    error = rename("data/tmp_category", category_file_path);
    return 1;

}
