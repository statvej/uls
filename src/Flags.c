#include "../inc/uls.h"

t_flags init_flags(void)
{
    t_flags ret;
    ret.l = false;
    ret.a = false;
    ret.h = false;
    ret.A = false;
    ret.S = false;
    return ret;
}
t_flags mx_get_flags(int ac, char **av)
{

    t_flags ret = init_flags();

    for (int count = 1; count < ac; count++)
    {
        if (av[count][0] == '-')
        {
            for (int i = 1; av[count][i] != 0; i++)
            {
                if (av[count][i] == 'S')
                    ret.S = true;
                if (av[count][i] == 'l')
                    ret.l = true;
                if (av[count][i] == 'a')
                    ret.a = true;
                if (av[count][i] == 'h')
                    ret.h = true;
                if (av[count][i] == 'A')
                    ret.A = true;
            }
        }
    }

    return ret;
}