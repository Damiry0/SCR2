#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int signo)
{
    if (signo == SIGALRM)
        {
            printf("Otrzymanao sygnał. Progrram zostanie zakonczony.");
        exit(0);
        }
    else if (signo == SIGTERM)
        {
            printf("Otrzymanao sygnał. Progrram wróci do dalszego wykonywania.");
        }
    else if (signo == SIGUSR1)
        {
             for(int j=0;j<1000;j++)
        {
            printf("Dodatkowa iteracja nr: %d",j);
        }
        }
    else if (signo == SIGUSR2)
       {}
}


int main(){
    if (signal(SIGALRM, sig_handler) == SIG_ERR);
    if (signal(SIGTERM, sig_handler) == SIG_ERR);
    if (signal(SIGUSR1, sig_handler) == SIG_ERR);
    if (signal(SIGUSR2, sig_handler) == SIG_ERR);

    int i=0;
    do{
        i++;
        usleep(70000); // dziala tyllko na linuxie, mikrosekundy
        printf("%d /n",i);
    }
    while(1);
}
// 14 - SIGALRM , 15 - SIGTERM , SIGUSR1, SIGUSR2

// ps aux | grep ./a.out - search for pid
// top -u 30  //zmiana czestotliwosci odswiezania polecia top