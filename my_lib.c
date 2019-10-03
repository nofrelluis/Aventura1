#include "my_lib.h"

size_t my_strlen(const char *str){
    char *str2 = str;
    while(*str2 != 0){
        str2++;
    }
    return str2-str;
}

int my_strcmp(const char *str1, const char *str2){

}

char *my_strcpy(char *dest, const char *src){

}

char *my_strncpy(char *dest, const char *src, size_t n){

}

char *my_strcat(char *dest, const char *src){

}
