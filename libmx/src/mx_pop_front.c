#include "../inc/libmx.h"

void mx_pop_front(t_list **head){

    if(!(*head)){
        return;
    }
    else if(!((*head)->next)){
        free(*head);
        head = 0;
    }
    else{
        t_list *temp = (*head)->next;
        free(*head);
        *head = temp;
    }

}

