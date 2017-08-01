#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validate_input.h"

/* Kiem tra xem nguoi dung nhap so */
char check_main_program_input(char* buffer){
    for(unsigned int i = 0; i < strlen(buffer); i++){
        if(isdigit(buffer[i])){
            clear_stdin();
            return buffer[i];
        }
    }
    clear_stdin();
    return 0;
}

/* Xoa bo dem */
void clear_stdin(){
    char tmp_ch;
    tmp_ch = getchar();
    while(tmp_ch != '\n' && tmp_ch != EOF){
        tmp_ch = getchar();
    }
}

void safe_input(char* buffer){
    gets(buffer);
    strtok(buffer, "\n");
}
