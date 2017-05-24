#include "string.h"

void int_to_ascii(int n, char *str){
    int sign;
    if((sign=n) < 0) n = -n;
    
    char *p = str;
    do{
        *p = '0'+n%10;
        n /= 10;
        ++p;
    }while(n);
    if(sign < 0){
        *p = '-';
        ++p;
    }
    *p = '\0';
    reverse(str);
}

void hex_to_ascii(int n, char *str){
    append(str, '0');
    append(str, 'x');

}

void reverse(char *str){
    int i = 0, j = strlen(str) - 1;
    while(i < j){
        char tmp = *(str+i);
        *(str+i) = *(str+j);
        *(str+j) = tmp;
        i ++;
        j --;
    }
}

int strlen(char *str){
    char *p = str;
    while(*p != '\0') p ++;
    return p - str;
}

void backspace(char *str){
    int n = strlen(str);
    if(n==0) return;
    *(str+n-1) = '\0';
}

void append(char *str, char ch){
    int n = strlen(str);
    char *p = str;
    *(p+n) = ch;
    *(p+n+1) = '\0';
}

int strcmp(char *s1, char *s2){
    int i;
    for(i = 0; s1[i] == s2[i]; i ++)
        if(s1[i] == '\0') return 0;

    return s1[i] - s2[i];
}
