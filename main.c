#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bk_vector.h"
#include "load_category.h"
#include "load_word.h"
#include "validate_input.h"

char* prefix_file_path = "data/";
char* surfix_file_path = ".txt";

int load_word(category_node* category_head, Vector* vector, char** p_word_buffer);
int menu();
int search_word(Vector*);

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
        else if (choice == 9)
            break;
    }
    //load_file(&word_buffer, "data/Country.txt");
    //split_word_infor(vector, word_buffer, 6);
    //print_vector(vector);
    free(category_buffer);
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
}

int menu(){
    int user_choice = 1;
    char new_line_char;
    int byte_input;
    while(1){
        printf("\n---------------------------------\n");
        printf("[1]Tim tu\n");
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
    int error;
    char file_path[100] = {0};
    int amout_of_word;
    category_node* category_curr = category_head->next;
    while(category_curr){
        strcat(file_path, prefix_file_path);
        strcat(file_path, category_curr->category_name);
        strcat(file_path, surfix_file_path);
        amout_of_word = load_file(p_word_buffer, file_path);
        if (error == -1){
            category_curr = category_curr->next;
            memset(file_path,0, strlen(file_path));
            continue;
        }

        //printf("%s %d",", category_curr->amount_of_type);
        split_word_infor(vector, *p_word_buffer, category_curr->amount_of_type + 2);
        category_curr->amount_of_word = amout_of_word/(category_curr->amount_of_type + 2) + 1;
        category_curr = category_curr->next;
        memset(file_path,0, strlen(file_path));
        puts("OK ");
        fflush(stdout);
    }
    return 1;
}
