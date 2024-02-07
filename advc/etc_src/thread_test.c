#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *threadfunc(void *arg);

int main(int argc, char **argv)
{
    int       n, i, j;
    pthread_t threadid;

    if ((n = pthread_create(&threadid, NULL, threadfunc, NULL)) != 0)
    {
        perror("Thread create error ");
        exit(0);
    }

    usleep(100);  /* 다른 UNIX OS에서도 잘 동작할 수 있도록 하기 위하여 usleep 추가 */

    printf("Main Thread START\n");

    for (i = 0; i < 100000000; i++)
    {
        j = i*5;
    }

    printf("Main Thread END\n");
    pthread_join(threadid, NULL);

    return 0;
}

void *threadfunc(void *arg)
{
    int i, j;

    printf("Thread Start\n");

    for (i = 0; i < 100000000; i++)
    {
        j = i*5;
    }

    printf("Thread:end\n");

    return;
}
