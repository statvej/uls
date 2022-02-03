#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size){
    int sorted = 0;
    int swaps = 0;
    while(!sorted){
        sorted = 1;

        for(int i = 0; i < size - 1; i++){
            if(mx_strcmp(arr[i], arr[i + 1]) > 0){
                char *temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = 0;
                swaps++;
            }
        }
    }

    return swaps;
}

