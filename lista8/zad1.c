#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
    long long *myid = (long long *)vargp;
    printf("Hello SCR.Written by thread ID: %d \n", *myid);
}
  
int main()
{
    pthread_t tid;
    for (int i = 0; i < 3; ++i)
        pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
  
    pthread_exit(NULL);
    return 0;
}