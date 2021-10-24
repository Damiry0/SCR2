#include <stdio.h>
#include <unistd.h>

int main(){
    int i=0;
    do{
        i++;
        sleep(1);
        printf("%d \n",i);
    }
    while(1);
}
// 14 - SIGALRM , 15 - SIGTERM , SIGUSR1, SIGUSR2


// top -u 30  //zmiana czestotliwosci odswiezania polecia top