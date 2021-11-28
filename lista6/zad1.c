#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
        FILE    *file;
        int     fd[2], nbytes; // fd - przechowuje file describtory fd[0]=odczyt/fd[1]=zapis
        pid_t   childpid; // przechowuje id procesu potomnego
        char    *string=NULL;
        char    readbuffer[80]; //bufor dla potoku

        pipe(fd); // tworzenie potoku
        
        if((childpid = fork()) == -1) // tworzenie procesu potomnego 
        {
                perror("Nie udalo sie utorzyc procesu potomnego.zamykam");
                exit(0);
        }

        file=fopen(argv[1],"r");
        size_t len=0;
        while(getline(&string,&len,file)!=-1)
        {
            printf("%s",string);
        }
        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("#%s#", readbuffer);
        }
        
        return(0);
}