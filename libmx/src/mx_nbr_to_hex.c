#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr){
      if(nbr == 0){
                return "0";
        }
        unsigned long temp = nbr;
        int length = 0;
        char characters[] = "0123456789abcdef";
        while(temp > 0){
                length++;
                temp /= 16;
        }

        char *result = mx_strnew(length);
        int counter = length - 1;
        while(nbr > 0){
                result[counter] = characters[nbr % 16];
                nbr /= 16;
                counter--;
        }

        return result;
}
