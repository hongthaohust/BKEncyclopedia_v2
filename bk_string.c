#include<stdio.h>
#include<string.h>
#include<ctype.h>
int to_lower_string(char* str, char* lower_str){
    int len_str = strlen(str);
    int i;
    //char lower_str[len_str];
    for (i = 0; i < len_str; i++){
        lower_str[i] = tolower(str[i]);
    }
    lower_str[i] = 0;
    return i;
}
