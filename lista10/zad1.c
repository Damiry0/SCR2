#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>

#define BUF_SIZE 1000
#define PASS_LENGTH 33

FILE *dict, *pass;
char *filenamePasswords = "/home/damiry/Desktop/SCR/SCR2/lista10/test-data1.txt";
char *filenameDictionaries = "/home/damiry/Desktop/SCR/SCR2/lista10/test-dict-mini.txt";


int countLinesInFile(FILE *fp);

int longestLineInFile(FILE *fp);

int checkLetter(const char *tab, int x);

void bytes2md5(const char *data, int len, char *md5buf);

void passwordBreaking(char tab[],int tier)
{
    char str[BUF_SIZE];
    long multiplicationFactor= pow(10,tier);
    int start;
    if(tier==0)start=0;
    else
    {
        start= pow(10,tier-1);
    }
    char md5[33]; // 32 characters + null terminator
    for (int i = start*10; i < 10*multiplicationFactor; ++i) {

            sprintf(str,"%d",i);
            char* tmp=strdup(tab);
            strcat(tmp,str); // po
          //  bytes2md5(tmp, strlen(tmp), md5);
           // if()
          //  strcat(str,tmp); // przed
           printf("poka:%s \n",tmp);
    }
    //passwordBreaking(tab,tier+1); // infite recursion
}



int main() {
// passwords
    char passwords[BUF_SIZE][PASS_LENGTH];
    if ((pass = fopen(filenamePasswords, "r")) == NULL) {
        printf("Error! opening file"); // Program exits if the file pointer returns NULL.
        exit(1);
    }
    struct stat statsPasswords;
    stat(filenamePasswords, &statsPasswords);
    int sizePasswords = statsPasswords.st_size / PASS_LENGTH;

    for (int i = 0; i < sizePasswords; i++) {
        fscanf(pass, "%s", passwords[i]); //"%s%*c"
    }
    for (int i = 0; i < sizePasswords; i++) {
        printf("%d : %s \n", i, passwords[i]);
    }

    // dictionaries
    if ((dict = fopen(filenameDictionaries, "r")) == NULL) {
        printf("Error! opening file"); // Program exits if the file pointer returns NULL.
        exit(1);
    }
    int lines = countLinesInFile(dict);
    char dictionaries[lines][longestLineInFile(dict)];
    char dictionariesFull[2][lines][longestLineInFile(dict)];
    int countConsumer0 = 0,countConsumer1=0,countConsumer2=0;
    for (int i = 0; i < lines; i++) {
        fscanf(dict, "%s", dictionaries[i]);
        switch (checkLetter(dictionaries[i],lines)) {
            case 0:
            {
                strcpy(dictionariesFull[0][countConsumer0],dictionaries[i]);
                countConsumer0++;
            }
            break;
            case 1:
            {
                strcpy(dictionariesFull[1][countConsumer1],dictionaries[i]);
                countConsumer1++;
            }
            break;
            case 2:
            {
                strcpy(dictionariesFull[2][countConsumer2],dictionaries[i]);
                countConsumer2++;
            }
            break;
        }
    }
    printf("przerwa \n");
    for (int i = 0; i < countConsumer2; i++) {
        printf("%d : %s \n", i, dictionariesFull[2][i]);
    }
    //breaking
    int tier=0;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<countConsumer2;i++)
        {
            passwordBreaking(dictionariesFull[2][i], tier);
        }
        tier++;
    }
#pragma clang diagnostic pop
//    const char *test = "Wrong99";
//    char md5[33]; // 32 characters + null terminator
//    bytes2md5(test, strlen(test), md5);
//    printf("%s ======================> %s\n", test, md5);




    // watki
    //pthread_t consument;


    fclose(dict);
    fclose(pass);
    return 0;
}

int countLinesInFile(FILE *fp) {
    char c;
    int count = 1;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') { count++; }

    rewind(fp);
    return count;
}

int longestLineInFile(FILE *fp) {
    int largest = 0, current = 0;// Line counter (result)
    char c;  // To store a character read from file
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            if (current > largest) {
                largest = current;
            }
            current = 0;
        } else {
            current++;
        }
    }
    rewind(fp);
    return largest;
}
int checkLetter(const char *tab, int x)
{
    for (int j = 0; j < x; ++j) {
        if (islower(tab[0]) && (islower(tab[1]))) return 0;
        else if (isupper(tab[0]) && (islower(tab[1]))) return 1;
        else if (isupper(tab[0]) && (isupper(tab[1]))) return 2;
    }
    return -1;
}

void bytes2md5(const char *data, int len, char *md5buf) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data, len);
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);
    for (i = 0; i < md_len; i++) {
        snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
    }
}


