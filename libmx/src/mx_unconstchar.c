#include "../inc/libmx.h" 
char *mx_unconstchar(const char *s)
{
    if (!s)
        return NULL;
    int i;
    char *res = NULL;
    res = (char *)malloc(mx_strlen(s) + 1);
    if (!res)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        for (i = 0; s[i] != '\0'; i++)
        {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
    }
}
