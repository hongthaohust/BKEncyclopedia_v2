#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "bk_header.h"

#include "bk_vector.h"
#include "load_category.h"
#include "load_word.h"
#include "validate_input.h"
//#include "file_process.h"

int load_word(category_node* category_head, Vector* vector, char** p_word_buffer);
int menu();
int search_word(Vector*);
int add_word_func(Vector* vector, category_node* category_head);
int edit_word(Vector* vector);
int print_amount_of_category(category_node* category_head);

int main()
{
    Vector* vector = NULL;
    category_node* category_head;
    //type_node* type_head;
    char *word_buffer, *category_buffer;
    init_vector(&vector,1024);

//    printf("loading....\n");
//    fflush(stdout);
//    load_file(&word_buffer, "10000");
//    split_word_infor(vector, word_buffer, 3);
//    printf("load done\n");
//    fflush(stdout);
//    print_vector(vector);
//    printf("\n Find: %d", search_vector_element(vector->word_list, "test999", 0, vector->used));
    load_file_category(&category_buffer, "data/theloai.txt");
    split_category(&category_head, category_buffer);
    print_category(category_head);
    load_word(category_head, vector, &word_buffer);
    //print_vector(vector);
    //load_file(&word_buffer, "data/Dai hoc.txt");
    //split_word_infor(vector, word_buffer, 8);
    //print_vector(vector);
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
        else if (choice == 9)
            break;
    }
    //load_file(&word_buffer, "data/Country.txt");
    //split_word_infor(vector, word_buffer, 6);
    //print_vector(vector);
    free_category(category_head);
    //free(category_buffer);
    //free(word_buffer);
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
        printf("[9]Thoat chuong trinh\n");
        printf("Moi chon: ");
        fflush(stdout);
        byte_input = scanf("%d%c", &user_choice, &new_line_char);
        if (byte_input !=2 || new_line_char != '\n'){
            printf("Nhap khong hop le\n");
            clear_stdin();
            continue;
        }
        /* Xoa ki tu \n */
        if (user_choice > 0 && user_choice < 10)
            break;
    }
    return user_choice;
}
int load_word(category_node* category_head, Vector* vector, char** p_word_buffer){
    //int error;
    char file_path[128] = {0};
    int amout_of_word;
    int error;
    category_node* category_curr = category_head->next;
    while(category_curr){
        get_file_path(file_path, category_curr->category_name);
//        strcat(file_path, prefix_file_path);
//        strcat(file_path, category_curr->category_name);
//        strcat(file_path, surfix_file_path);
        error = load_file(p_word_buffer, file_path);
        if (error == -1){
            category_curr = category_curr->next;
            memset(file_path,0, strlen(file_path));
            continue;
        }

        //printf("%s %d",", category_curr->amount_of_type);
        amout_of_word = split_word_infor(vector, *p_word_buffer, category_curr->amount_of_type + 2);
        category_curr->amount_of_word = amout_of_word/(category_curr->amount_of_type + 2) + 1;
        category_curr = category_curr->next;
        memset(file_path,0, strlen(file_path));
        puts("OK ");
        fflush(stdout);
    }
    return 1;
}

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
//    printf("%s: ", type_curr->type_name);
//    gets(new_data_head->data);
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
