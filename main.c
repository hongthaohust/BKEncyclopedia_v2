#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int print_amount_of_category(category_node* category_head);
void print_category_infor(category_node* category_head);
int add_category(category_node* category_head);
int delete_category(category_node* category_head);
int main()
{
    Vector* vector = NULL;
    category_node* category_head;
    //type_node* type_head;
    char *word_buffer, *category_buffer;
    int error;

    init_vector(&vector,1024);
    printf("Loading....\n");
    error = load_file_category(&category_buffer);
    if (error == -1){
        printf("Khong load duoc file the loai\n");
        return 1;
    }
    split_category(&category_head, category_buffer);
//    print_all_category(category_head);
    load_word(category_head, vector, &word_buffer);
    printf("Load done\n");
    while(1){
        int choice = menu();
        if (choice == 1)
            search_word(vector);
        else if (choice == 2)
            add_word_func(vector, category_head);
        else if (choice == 3)
            edit_word(vector);
        else if (choice == 5)
            print_amount_of_category(category_head);
        else if (choice == 6){
            add_category(category_head);
        }

        else if (choice == 8){
            /* Xoa the loai sau do load lai */
            if (delete_category(category_head) == -1)
                continue;
            free(word_buffer);
            free(vector);
            init_vector(&vector, 1024);
            load_word(category_head, vector, &word_buffer);
        }
        else if (choice == 9)
            print_category_infor(category_head);
        else if (choice == 10)
            break;
        else if (choice == 11)
            print_all_category(category_head);
    }
    //load_file(&word_buffer, "data/Country.txt");
    //split_word_infor(vector, word_buffer, 6);
    //print_vector(vector);
    free_category(category_head);
    //free(category_buffer);
    free(word_buffer);
    //getchar();
    //printf("%s",vector[2].data);
}

int search_word(Vector* vector){
    int index;
    char word_name[128];
    printf("-- Nhap vao tu de tim: ");
    gets(word_name);
    strtok(word_name, "\n");
    index = search_vector_element(vector->word_list, word_name, 0, vector->used-1);
    if (index == -1){
        printf("Khong tim thay\n");
        return -1;
    }
    print_word(vector->word_list[index]);
    return 1;
}

int menu(){
    int user_choice = 1;
    char new_line_char;
    int byte_input;
    while(1){
        printf("\n---------------------------------\n");
        printf("[1]Tim tu\n");
        printf("[2]Them tu\n");
        printf("[3]Sua tu\n");
        printf("[4]Xoa tu\n");
        printf("[5]Thong ke cac tu thuoc the loai\n");
        printf("[6]Them the loai\n");
        printf("[7]Sua the loai\n");
        printf("[8]Xoa the loai\n");
        printf("[9]In thong thong tin 1 the loai\n");
        printf("[10]Thoat chuong trinh\n");
        printf("[11]Hien thi tat ca the loai\n");
        printf("Moi chon: ");
        fflush(stdout);
        byte_input = scanf("%d%c", &user_choice, &new_line_char);
        if (byte_input !=2 || new_line_char != '\n'){
            printf("Nhap khong hop le\n");
            clear_stdin();
            continue;
        }
        /* Xoa ki tu \n */
        if (user_choice > 0 && user_choice < 12)
            break;
    }
    return user_choice;
}

int load_word(category_node* category_head, Vector* vector, char** p_word_buffer){
    char file_path[128] = {0};
    int amout_of_word;
    int error;
    category_node* category_curr = category_head->next;
    while(category_curr){
        get_file_path(file_path, category_curr->category_name);
        error = load_file(p_word_buffer, file_path);
        if (error == -1){
            category_curr = category_curr->next;
            memset(file_path,0, strlen(file_path));
            continue;
        }
        amout_of_word = split_word_infor(vector, *p_word_buffer, category_curr->amount_of_type + 2);
        category_curr->amount_of_word = amout_of_word/(category_curr->amount_of_type + 2) + 1;
        category_curr = category_curr->next;
        memset(file_path,0, strlen(file_path));
    }
    return 1;
}

/* Chuc nang them 1 tu */
int add_word_func(Vector* vector, category_node* category_head){
    char category_name[64] = {0};
    word_info* new_word;
    type_node* type_curr;
    data_node* new_data_head;
    data_node* new_data_curr;
    category_node* finded_category = NULL;
    int amout_of_type;
    int error;
    int index;

    printf("Nhap ten the loai: ");
    safe_input(category_name);
    //getchar();
    finded_category = has_category(category_head, category_name);
    if ( finded_category == NULL)
        return -1;

    type_curr = finded_category->type_head;
    amout_of_type = finded_category->amount_of_type;
    /* Cap phat bo nho cho word moi */
    error = init_new_word(&new_word);
    if (error == -1)
        return -1;
    error = init_new_data_node(&new_data_head);
    if (error == -1)
        return -1;
    /* Nhap ten */
    strcpy(new_word->category_id, finded_category->category_id);
    printf("Nhap ten tu: ");
    safe_input(new_word->word_name);
    /* Nhap cac truong */
    new_data_curr = new_data_head;
//    type_curr = type_curr->next;
    for (int i = 0; i < amout_of_type; i++){
        data_node* new_data_node;
        error = init_new_data_node(&new_data_node);
        if (error == -1)
            return -1;
        printf("%s: ", type_curr->type_name);
        safe_input(new_data_node->data);
//        gets(new_data_node->data);
//        strtok(new_data_node->data, "\n");
        new_data_node->next = NULL;
        new_data_curr->next = new_data_node;
        new_data_curr = new_data_curr->next;
        type_curr = type_curr->next;
    }
    /* Them tu vao danh sach */
    new_word->p_data_head = new_data_head;
    index = get_new_word_index(vector, new_word);
    insert_vector_element(vector, new_word, index);
    add_word_to_file(category_name, new_word);
    return 1;
    //add_word(vector, category_name, )
}

/* Chuc nang sua 1 tu tra ve 1 neu thanh cong va -1 neu loi*/
int edit_word(Vector* vector){
    word_info* new_word;
    word_info* old_word;
    word_info** word_list;
    char word_name[WORD_NAME_SIZE];
    int index;
    int error;

    printf("--Nhap ten tu muon sua: ");
    safe_input(word_name);
    index = search_vector_element(vector->word_list,word_name,0,vector->used-1);
    if (index == -1){
        printf("Khong tim thay tu nay\n");
        return -1;
    }
    word_list = vector->word_list;
    old_word = word_list[index];
    init_new_word(&new_word);
    error = edit_word_in_db(vector, old_word,new_word, index);
    if (error == -1){
        printf("Khong sua thanh cong\n");
        return -1;
    }
    return 1;
}

int print_amount_of_category(category_node* category_head){
    category_node* category = NULL;
    char category_name[CATEGORY_NAME_SIZE];
    printf("--Nhap ten the loai: ");
    safe_input(category_name);
    category = has_category(category_head, category_name);
    if (category == NULL){
        printf("Khong thay the loai nay\n");
        return -1;
    }
    printf("--So tu cua the loai %s la %d", category->category_name, category->amount_of_word);
    return 1;
}

int add_category(category_node* category_head){
    int error;
    int amount_of_type;
    char category_name[CATEGORY_NAME_SIZE];
    category_node* new_category;
    type_node* type_head;
    type_node* type_curr;
    printf("--Nhap ten the loai: ");
    safe_input(category_name);
    if (has_category(category_head, category_name) != NULL){
        printf("Ten the loai da ton tai\n");
        return -1;
    }
    error = init_category(&new_category);
    if (error == -1){
        return -1;
    }
    strcpy(new_category->category_name, category_name);
    printf("--Nhap ma the loai: ");
    safe_input(new_category->category_id);
    printf("--Nhap so truong: ");
    scanf("%d",&amount_of_type);
    clear_stdin();
    if (amount_of_type <1){
        printf("So truong phai >= 1");
        free_category(new_category);
        return -1;
    }
    new_category->amount_of_type = amount_of_type;
    error = init_type(&type_head);
    if (error == -1){
        free_one_type(type_head);
        free_category(new_category);
    }
    printf("Nhap vao truong 1: ");
    safe_input(type_head->type_name);
    type_curr = type_head;
    type_curr->next = NULL;
    for (int i = 0; i < amount_of_type-1; i++){
        type_node* new_type;
        error = init_type(&new_type);
        if (error == -1)
            return -1;
        printf("--Nhap ten truong %d: ",i+2);
        safe_input(new_type->type_name);
        new_type->next = NULL;
        type_curr->next = new_type;
        type_curr = type_curr->next;
    }
    new_category->type_head = type_head;
    add_category_to_db(category_head, new_category);
    add_category_to_file( new_category);
    return 1;
}

void print_category_infor(category_node* category_head){
    category_node* finded_category = NULL;
    char category_name[CATEGORY_NAME_SIZE];
    //int error;
    printf("Nhap vao ten the loai: ");
    safe_input(category_name);
    finded_category = has_category(category_head, category_name);
    if (finded_category == NULL){
        printf("Khong tim thay the loai nay\n");
        return;
    }
    print_one_category(finded_category);
}

int delete_category(category_node* category_head){
    //category_node* finded_category = NULL;
    char category_name[CATEGORY_NAME_SIZE];
    int error;
    if (category_head->next == NULL){
        printf("Khong con the loai nao de xoa\n");
        return -1;
    }
    printf("--Nhap ten the loai can xoa: ");
    safe_input(category_name);
    error = delete_category_in_db(category_head, category_name);
    if (error == -1){
        printf("Khong tim thay ten the loai\n");
        return -1;
    }
    error = write_category_to_file(category_head);
    if (error == -1){
        printf("Khong xoa duoc trong file\n");
        return -1;
    }
    printf("Xoa the loai thanh cong\n");
    return 1;
}
