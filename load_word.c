#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_word.h"
//#include "file_process.h"
#include "bk_vector.h"

int init_new_word(word_info** p_new_word){
    word_info* new_word ;
    new_word = calloc(1, sizeof(word_info));
    if (new_word == NULL)
        return -1;
    *p_new_word = new_word;
    new_word->category_id = calloc(CATEGORY_ID_SIZE, sizeof(char));
    new_word->word_name = calloc(WORD_NAME_SIZE, sizeof(char));
    if (new_word->category_id == NULL || new_word->word_name == NULL)
        return -1;
    return 1;
}

int init_new_data_node(data_node** p_new_data){
    data_node* new_data;
    new_data = calloc(1, sizeof(data_node));
    if (new_data == NULL)
        return -1;
    new_data->data = calloc(DATA_SIZE, sizeof(char));
    if (new_data->data == NULL)
        return -1;
    *p_new_data = new_data;
    return 1;
}

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

int add_word_to_file(char* file_name, word_info* new_word){
    char file_path[128] = {0};
    data_node* data_curr_node;
    int index;
    FILE* file;

    if ( new_word == NULL)
        return -1;
    data_curr_node = new_word->p_data_head->next;
    get_file_path(file_path, file_name);
    file = fopen(file_path,"a");
    if (file == NULL)
        return -1;
    fprintf(file,"\n%s",new_word->word_name);
    fprintf(file,"\n%s", new_word->category_id);
    while(data_curr_node){
        fprintf(file, "\n%s",data_curr_node->data);
        data_curr_node = data_curr_node->next;
    }
    //index = get_new_word_index(vector, new_word);
    //insert_vector_element(vector, new_word, index);
    fclose(file);
    return 1;
    //strcat()
    //file = fopen()
}

int edit_word_in_db(Vector* vector, word_info* old_word, word_info* new_word, int old_index){
    int error;
    int is_word_exist;
    data_node* data_head;
    data_node* data_curr;
    data_node* new_data_head;
    data_node* new_data_curr;
    strcpy(new_word->category_id, old_word->category_id);
    printf("+ %s --> ",old_word->word_name);
    safe_input(new_word->word_name);
    /* Kiem tra xem tu do co ton tai hay khong, neu ton tai ma khac voi tu muon sua thi moi cho sua */
    is_word_exist = search_vector_element(vector->word_list, new_word->word_name, 0, vector->used-1);
    if ((is_word_exist != -1) && (is_word_exist != old_index)){
        printf("Khong doi ten duoc do ten nay da ton tai\n");
        return -1;
    }
    error = init_new_data_node(&new_data_head);
    if (error == -1){
        printf("Khong khoi tao duoc\n");
        return -1;
    }
    data_head = old_word->p_data_head;
    data_curr = data_head->next;
    new_data_curr = new_data_head;
    while(data_curr){
        data_node* new_data_node;
        error = init_new_data_node(&new_data_node);
        if (error == -1)
            return -1;
        printf("+ %s --> ", data_curr->data);
        safe_input(new_data_node->data);
        data_curr = data_curr->next;
        new_data_curr->next = new_data_node;
        new_data_curr = new_data_curr->next;
        new_data_curr->next = NULL;
    }
    //new_word->p_data_head = new_data_head
    //*p_old_word = new_word;
    old_word->p_data_head = new_data_head;
    old_word->word_name = new_word->word_name;
    old_word->category_id = new_word->category_id;
    return 1;
}
int edit_word_in_file(char* file_name){
}
//int type_
