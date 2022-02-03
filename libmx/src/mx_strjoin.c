#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2){

    if(!s1 && !s2){
		return 0;
	}
	char* new_string;
	if(s1 && (!s2 || mx_strlen(s2) == 0)){
		new_string = mx_strdup(s1);
		new_string[mx_strlen(new_string)] = '\0';
		return new_string;
	}
	else if(s2 && (!s1 || mx_strlen(s1) == 0)){
		new_string = mx_strdup(s2);
		new_string[mx_strlen(new_string)] = '\0';
		return new_string;
	}

	int length1 = mx_strlen(s1);
	int length2 = mx_strlen(s2);
	new_string = mx_strnew(length1 + length2 + 1);
	new_string = mx_strcpy(new_string, s1);
	new_string = mx_strcat(new_string, s2);
	new_string[mx_strlen(new_string)] = '\0';
	return new_string;

}

