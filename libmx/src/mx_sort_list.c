#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)){

    t_list *current_node = 0;
    t_list *sorted_pointer = 0;
    int swaps = 1;


    while(swaps){
        swaps = 0;
        current_node = list;
        while(current_node->next != sorted_pointer){
            if(cmp(current_node->data, current_node->next->data)){
                void *temp = current_node->data;
                current_node->data = current_node->next->data;
                current_node->next->data = temp;
                swaps++;
            }
            current_node = current_node->next;
        }
        sorted_pointer = current_node;

    }

    return list;
}

