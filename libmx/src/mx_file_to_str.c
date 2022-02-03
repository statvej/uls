#include "../inc/libmx.h"

char *mx_file_to_str(const char *file){
    if(!file){
        return 0;
    }

    int open_file = 0;
    open_file = open(file,O_RDONLY);

    if(open_file < 0){
        close(open_file);
        return 0;
    }

    int file_length = 0;
    char current_char[2];

    char *new_string = 0;
    while((file_length = read(open_file,current_char,1))){
        current_char[1] = '\0';
        new_string = mx_strjoin(new_string,current_char);
    }

    return new_string;

}

