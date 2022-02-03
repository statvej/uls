#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex){
    if(!hex){
                return 0;
        }
        unsigned long result = 0;
        int length = 0;
        for(;hex[length];length++){
                unsigned int temp = 0;
                if(mx_isalpha(hex[length])){
                        if((hex[length] >= 'a' && hex[length] <= 'f') || (hex[length] >= 'A' && hex[length] <= 'F')){
                                temp = (unsigned long)hex[length] + 10;
                                temp -= (mx_isupper(hex[length]) ? 'A' : 'a');
                        }
                        else{
                                return 0;
                        }
                }
                else if(mx_isdigit(hex[length])){
                        temp = (unsigned long)hex[length] - '0';
                }
                else{
                        return 0;
                }

                result = result * 16 + temp;
        }

        return result;
}

