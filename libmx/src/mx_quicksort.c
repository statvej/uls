#include "../inc/libmx.h"
int mx_quicksort(char **arr, int left, int right){
    if(!arr){
        return -1;
    }

    int counter = 0;

    if(left < right){
        int first = left;
        int last = right;
        char *middle = arr[(first + last) / 2];

        while(first < last){
            while(mx_strlen(arr[first]) < mx_strlen(middle))
                first++;
            while(mx_strlen(arr[last]) > mx_strlen(middle))
                last--;

            if(first <= last){
                if(mx_strlen(arr[first]) != mx_strlen(arr[last])){
                    char *temp = arr[first];
                    arr[first] = arr[last];
                    arr[last] = temp;
                    counter++;
                }
                first++;
                last--;
            }
        }

        counter += mx_quicksort(arr, left, last);
        counter += mx_quicksort(arr, first, right);
    }

    return counter;
}

