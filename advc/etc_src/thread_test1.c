#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex       = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  thread_cond = PTHREAD_COND_INITIALIZER;

void *do_write(void);
void *do_read(void);

struct com_data
{
    int a;
    int b;
};

struct com_data mydata;

void *do_write()
{
    mydata.a = 0;
    mydata.b = 0;

    while(1)
    {
        printf("write ");
        pthread_mutex_lock(&mutex);
        mydata.a = random() % 6000;
        mydata.b = random() % 6000;
        printf("%4d , %4d", mydata.a, mydata.b);
        pthread_cond_signal(&thread_cond);
 
        /* pthread_cond_wait () 함수는 인자로 넘어온 mutex를 unlock 시킨 
        * 상태에서 시그널을 기다린다. 그리고 시그널을 받게되면 mutex를 
        * lock 시키고 다음 코드로 넘어간다.
        * 그래서 이 함수의 위아래로 mutex_lock과 mutex_unlock 함수가 오는것이다.
        */
        pthread_cond_wait(&thread_cond, &mutex);
        pthread_mutex_unlock(&mutex);
 
        /* usleep으로 딜레이를 안주면 어느정도 실행되다가 멈춰버린다.
        * 이유는 너무 바쁘게 작동을 하게되면 OS가 쓰레드의 스케쥴링을 할 수가
        * 없게되어서 그렇다. 그래서 usleep으로 약간의 딜레이를 줘서 스케쥴링이
        * 되도록 해줘야 한다.
        */
 
        usleep(100);
    }
}

void *do_read()
{
   while(1)
   {
       printf("read ");
       pthread_mutex_lock(&mutex);
       pthread_cond_wait(&thread_cond, &mutex);
       printf("\t%4d + %4d = %4d\n", mydata.a, mydata.b, mydata.a + mydata.b);
       pthread_cond_signal(&thread_cond);
       pthread_mutex_unlock(&mutex);

       /* 이 예제에서 이 부분에 usleep을 쓰게되면 딱 한번만 코드가 실행되고 멈춰버린다.
        * 이 예제를 잘 살펴보면 항상 do_read 함수가 먼저 실행된 상태에서 시그널을 기다
        * 리고 있어야 제대로 작동을 하게 된다. 그런데 여기에 usleep을 쓰게되면 
        * 기다리는 쪽은 딜레이가 걸리고 보내는쪽은 계속해서  빠르게 보내는 꼴이 되어서
        * 정상작동을 하지 않는것 같다.
        */

       // usleep(100);
   }
}

int main()
{
    pthread_t p_thread[2];
    int thr_id;
    int status;
 
    thr_id = pthread_create(&p_thread[1], NULL, (void *)do_read, NULL);
 
    /* 보통 쓰레드 사이에 usleep을 둬서 OS가 쓰레드를 스케줄링 할 수 있도록 해주는것이 좋다. */
 
    usleep(100);
 
    thr_id = pthread_create(&p_thread[0], NULL, (void *)do_write, NULL);
 
    pthread_join(p_thread[0], (void **) status);
    pthread_join(p_thread[1], (void **) status);
 
    return 0;
}
