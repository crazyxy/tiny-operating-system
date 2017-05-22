/**
 * File: kernel/util.c
 * Author: Yan Xue <yanxue@paypal.com>
 * Date: 22/05/2017
 */
void memory_copy(char *dst, char *src, int n){
    int i;
    for(i = 0; i < n; i ++)
        *(dst+i) = *(src+i);
}


void int_to_ascii(int n, char str[]){
    int i = 0, sign;
    if((sign=n) < 0) n = -n;
    
    do{
        str[i++] = '0'+n%10;
        n /= 10;
    }while(n);
    
    if(sign < 0) str[i++] = '-';
    str[i] = '\0';
}
