#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
    int a;
    int b;
    char *sa;
    char *as;

    a = open("sa.txt", O_RDONLY);
    b = open("as.txt", O_RDONLY);
    if (a == -1 || b == -1)
        return (-1);

while (1)
{
    sa = get_next_line(a);
    if (sa == NULL)
        break;
    printf("%s", sa);
    free(sa);

    as = get_next_line(b);
    if (as == NULL)
        break;
    printf("%s", as);
    free(as);
}
close(a);
close(b);

}

