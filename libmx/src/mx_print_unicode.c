#include "../inc/libmx.h"

void mx_print_unicode(wchar_t c)
{
    char template1[] = "0xxxxxxx";
    char templates2[] = "110xxxxx 10xxxxxx";
    char templates3[] = "1110xxxx 10xxxxxx 10xxxxxx";
    char templates4[] = "11110xxx 10xxxxxx 10xxxxxx 10xxxxxx";
    char *templates[] = {template1, templates2, templates3, templates4};
    int bin_count = 0;
    wchar_t copy = c;
    while (copy != 0)
    {
        copy /= 2;
        bin_count++;
    }
    int t = 0;
    if (bin_count > 7) t++;
    if (bin_count > 11) t++;
    if (bin_count > 16) t++;
    int bin[bin_count];
    for (int i = bin_count - 1; i >= 0; i--)
    {
        bin[i] = c % 2;
        c /= 2;
    }
    int t_len = mx_strlen(templates[t]);
    for (int i = t_len -1; i >= 0; i--)
    {
        if (templates[t][i] == 'x')
        {
            if (bin_count == 0) 
            {
                templates[t][i] = '0';
                continue;
            }
            templates[t][i] = bin[bin_count - 1] + '0';
            bin_count--;
        }
    }

    unsigned char buf[t + 1];
    int j = 0;

    for (int i = 0; i < t; i++) buf[i] = 0;

    for (int i = 0; i < t_len; i++)
    {
        if (templates[t][i] == ' ') j++;
        buf[j] += templates[t][i] - '0';
        if (templates[t][i + 1] != ' ' && i + 1 < t_len) buf[j] *= 2;
    }
    write(STDOUT_FILENO, buf, t + 1);
}
