#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_SIZE 20

int main(int argc, char *argv[])
{
    int fd[2];
    char buffer[MAX_SIZE];
    struct stat stats;
    while (1)
    {
        printf("Filename:");
        scanf("%s", &buffer);

        fd[0] = open(buffer, O_RDONLY,0);
        fd[1] = open("output.txt", O_WRONLY,0);
        
        fstat(fd[0], &stats); // otrzymanie informacji o pliku w podanej strukturze

        ftruncate(fd[1], stats.st_size); // zmiana rozmiaru pliku

        char *tmp = mmap(0, stats.st_size, PROT_READ, MAP_SHARED, fd[0], 0);
        /*
        start- określa adres, od którego odwzorujemy plik
        lenght- liczba bajtów jaką chcemy odwzorować w pamięci
        PROT_READ - pamięć może być czytana
        MAP_READ - pozwala udostpeniac innym procesmm zmapowany obraz
        fd – deskryptor pliku, który chcemy odwzorować w pamięci
        offset – liczba określająca od którego miejsca w pliku chcemy rozpocząć odwzorowywanie.
        */
        write(fd[1], tmp, stats.st_size); // zapis do pliku
        close(fd[0]);
        close(fd[1]); // zamkniecie deksryptorow 
    }

    // mmap();
    // return 0;
}