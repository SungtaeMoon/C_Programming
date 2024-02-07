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
 
        /* pthread_cond_wait () �Լ��� ���ڷ� �Ѿ�� mutex�� unlock ��Ų 
        * ���¿��� �ñ׳��� ��ٸ���. �׸��� �ñ׳��� �ްԵǸ� mutex�� 
        * lock ��Ű�� ���� �ڵ�� �Ѿ��.
        * �׷��� �� �Լ��� ���Ʒ��� mutex_lock�� mutex_unlock �Լ��� ���°��̴�.
        */
        pthread_cond_wait(&thread_cond, &mutex);
        pthread_mutex_unlock(&mutex);
 
        /* usleep���� �����̸� ���ָ� ������� ����Ǵٰ� ���������.
        * ������ �ʹ� �ٻڰ� �۵��� �ϰԵǸ� OS�� �������� �����층�� �� ����
        * ���ԵǾ �׷���. �׷��� usleep���� �ణ�� �����̸� �༭ �����층��
        * �ǵ��� ����� �Ѵ�.
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

       /* �� �������� �� �κп� usleep�� ���ԵǸ� �� �ѹ��� �ڵ尡 ����ǰ� ���������.
        * �� ������ �� ���캸�� �׻� do_read �Լ��� ���� ����� ���¿��� �ñ׳��� ���
        * ���� �־�� ����� �۵��� �ϰ� �ȴ�. �׷��� ���⿡ usleep�� ���ԵǸ� 
        * ��ٸ��� ���� �����̰� �ɸ��� ���������� ����ؼ�  ������ ������ ���� �Ǿ
        * �����۵��� ���� �ʴ°� ����.
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
 
    /* ���� ������ ���̿� usleep�� �ּ� OS�� �����带 �����ٸ� �� �� �ֵ��� ���ִ°��� ����. */
 
    usleep(100);
 
    thr_id = pthread_create(&p_thread[0], NULL, (void *)do_write, NULL);
 
    pthread_join(p_thread[0], (void **) status);
    pthread_join(p_thread[1], (void **) status);
 
    return 0;
}
