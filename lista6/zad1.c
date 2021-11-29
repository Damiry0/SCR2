#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#define MaxSize 16
int main(int argc, char *argv[])
{
    int fd[2],file, count; // fd - przechowuje file describtory 
    //fd[0]=odczyt/fd[1]=zapis
    char readbuffer[MaxSize]; //bufor dla potoku

    pipe(fd); // tworzenie potoku
    pid_t childpid;           // przechowuje id procesu potomnego
    if((childpid = fork()) == -1) // tworzenie procesu potomnego 
        {
                perror("Nie udalo sie utorzyc procesu potomnego.zamykam");
                exit(0);
        }
    if (childpid == 0) //rodzic
    {
        close(fd[1]);
        while ((count = read(fd[0], readbuffer, MaxSize)))
        {
            write(1, " # ", 2 * sizeof(char));
            write(1, readbuffer, count);
            write(1, " # ", 2 * sizeof(char));
        }
        close(fd[0]);
    }
    else if(childpid>0) //dziecko
    {
        close(fd[0]);
        file = open(argv[1], O_RDONLY);
        /* Odczyt danych z potoku */
        while ((count = read(file, readbuffer, MaxSize)) > 0)
        {
            if(write(fd[1], readbuffer, count)<0);
        }
        close(fd[1]);
    }
    else
    {
        printf("Something went wrong.Closing.");
        exit(0);
     }

}