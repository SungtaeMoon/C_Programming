#include <stdio.h>

int main(int argc, char **argv)
{
    char buf[300];
    char *aa = "aaaaaaaaaa";
    char *bb = "bbbbbbbbbb";
    char *cc = "cccccccccc";
    char *dd = "dddddddddd";

    sprintf(buf, "%s%s%s%s", aa, bb, cc, dd);

    printf("buf = [%s]\n", buf);

    return 0;
}
