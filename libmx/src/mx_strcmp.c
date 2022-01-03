
   
#include "libmx.h"
int mx_strcmp(const char *s1, const char *s2)
{
    int cam = 0;
    int cam2 = 0;
    while (s1[cam] != '\0')
    {

        if (s1[cam] != s2[cam])
        {
            return s1[cam] - s2[cam];
        }
        ++cam;
    }
    while (s2[cam2] != '\0')
    {

        if (s1[cam2] != s2[cam2])
        {
            return s1[cam] - s2[cam];
        }
        ++cam2;
    }
    return 0;
}
