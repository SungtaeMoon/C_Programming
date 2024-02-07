#include <stdio.h>

int
main(void)
{
#if 0
    int a = 5;
    char *pc;

    pc = (char *)&a;

    printf("addr of a  = [%p]\n", &a);
    printf("addr of pc = [%p]\n", pc);
#endif

    int a[5] = {2, 4, 6, 8, 22};
    int *p;

    p = &a[1];

    printf("%d %d", a[0], p[-1]);
    printf("\n");
    printf("%d %d", a[1], p[0]);

    return 0;
}
