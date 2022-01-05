#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE *fp;

int countLines()
{
    int count=0;
    for (char c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    return count+1;
}
int main()
{
    if ((fp = fopen("/home/damiry/Desktop/SCR/SCR2/lista10/test-dict-mini.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    printf("Number of lines:%d",countLines());
    int numberOfLines= countLines();
    const char *strs[numberOfLines];
    for (int i = 0; i < numberOfLines; ++i) {
        strs[i]
        printf("%s \n",strs[i]);
    }
    fclose(fp);
    return 0;
}


