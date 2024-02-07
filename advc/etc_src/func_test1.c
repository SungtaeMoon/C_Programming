#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_LEN 20

long apmmem_long2strn(char *, long, long);

int main(int argc, char **argv)
{
    long rc = 0;
    long p_key;
    char print_str[PRINT_LEN+1];

    memset(print_str, 0x00, sizeof(print_str));

    p_key = getpid() * 1000 + 1;
    printf("pid[%d], p_key[%ld]\n", getpid(), p_key);

    rc = apmmem_long2strn(print_str, p_key, PRINT_LEN);
    if (rc != 0)
    {
        return (-1);
    }

    printf("Output string = [%s]\n", print_str);

    return (0);
}

long apmmem_long2strn(char *str, long num, long buf_size)
{
    char result_str[256];
    long size   = 0;    
    long i      = 0;
    long offset = 0;
    long len    = 0;
    
    memset(result_str, 0x00, sizeof(result_str));
    sprintf(result_str, "%ld", num);
    
    len = strlen(result_str);
    
    if (len > buf_size)
    {
        printf("apmmem_long2strn 인자중, 버퍼크기보다 입력된 문자열의 길이가 더 큽니다.\n");
        return (-1);
    }
    
    offset = buf_size - len;
    for ( i = 0; i < offset; i++)
    {
        strcat(str, " ");
    }

    strncpy(str+offset, result_str, len);

    return (0);
}
