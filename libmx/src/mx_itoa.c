#include "../inc/libmx.h"

char *mx_itoa(int number){
    char *str_num = 0;
    if(number == -2147483648){
        str_num = mx_strnew(11);
        mx_strcpy(str_num, "-2147483648");
        return str_num;
    }
    else if(number == 0){
        str_num = mx_strnew(1);
        mx_strcpy(str_num, "0");
        return str_num;
    }

    int temp = number;
    int size = 0;
    int sign = 0;
    if(temp < 0){
        size++;
        number = temp *= -1;
        sign = 1;
    }

    while(temp > 0){
        temp /= 10;
        size++;
    }

    str_num = mx_strnew(size);
    while(number > 0){
        str_num[size - 1] = (number % 10) + '0';
        size--;
        number /= 10;
    }

    if(sign) str_num[0] = '-';
    return str_num;
    
}
