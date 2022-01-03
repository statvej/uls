#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count){
    *count = 0;
        if (mx_strcmp(s, arr[0]) < 0 || mx_strcmp(s, arr[size - 1]) > 0){
            return -1;
        }

        int left = 0;
        int right = size - 1;

        while (left <= right){
            int middle = left + (right - left) / 2;

            if (mx_strcmp(arr[middle], s) < 0 && mx_strcmp(arr[middle + 1], s) > 0){
                *count = 0;
                return -1;
            }

            *count += 1;

            if (!mx_strcmp(arr[middle], s)){
                return middle;
            }

            if (mx_strcmp(arr[middle], s) < 0){
                left = middle + 1;
            }
            else{
                right = middle - 1;
            }
        }
        *count = 0;
        return -1;
}

