#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>
#include <signal.h>

#define BUF_SIZE 1000
#define PASS_LENGTH 33

FILE *dict, *pass;

struct thread {
    int id;
    char **tab;
    int size;
};

char *filenamePasswords = "/home/damiry/Desktop/SCR/SCR2/lista10/test-data1.txt"; // TODO relative path
char *filenameDictionaries = "/home/damiry/Desktop/SCR/SCR2/lista10/test-dict-mini.txt";
char passwords[BUF_SIZE][PASS_LENGTH];
int countConsumer0 = 0, countConsumer1 = 0, countConsumer2 = 0,brokenPasswords=0;


int countLinesInFile(FILE *fp);

int longestLineInFile(FILE *fp);

void readPasswordsFile(FILE *fp);

int checkLetter(const char *tab, int x);

void bytes2md5(const char *data, int len, char *md5buf);

void dictionaryAppending(char tab[], long tier);

void checkPassword(char *tab, char *passReal);

void *producer(void *vargp);

void* consumer(void* vargp);

void sigHandler(int signum);


int main() {
    readPasswordsFile(pass);
    if ((dict = fopen(filenameDictionaries, "r")) == NULL) {
        printf("Error! opening file"); // Program exits if the file pointer returns NULL.
        exit(1);
    }
    int lines = countLinesInFile(dict);
    int longestLine = longestLineInFile(dict);
    char dictionaries[lines][longestLine];
    char dictionariesFull[2][lines][longestLine];
    for (int i = 0; i < lines; i++) {
        fscanf(dict, "%s", dictionaries[i]);
        switch (checkLetter(dictionaries[i], lines)) {
            case 0: {
                strcpy(dictionariesFull[0][countConsumer0], dictionaries[i]);
                countConsumer0++;
            }
                break;
            case 1: {
                strcpy(dictionariesFull[1][countConsumer1], dictionaries[i]);
                countConsumer1++;
            }
                break;
            case 2: {
                strcpy(dictionariesFull[2][countConsumer2], dictionaries[i]);
                countConsumer2++;
            }
                break;
        }
    }

    char **sorted_array_0 = malloc((countConsumer0) * sizeof(char *));
    char **sorted_array_1 = malloc((countConsumer1) * sizeof(char *));
    char **sorted_array_2 = malloc((countConsumer2) * sizeof(char *));
    for (int i = 0; i < countConsumer0; i++) {
        strcpy(&sorted_array_0[i], dictionariesFull[0][i]);
    }
    for (int i = 0; i < countConsumer1; i++) {
        strcpy(&sorted_array_1[i], dictionariesFull[1][i]);

    }
    for (int i = 0; i < countConsumer2; i++) {
        strcpy(&sorted_array_2[i], dictionariesFull[2][i]);
    }
    char ***sorted_array[3] = {
            sorted_array_0, sorted_array_1, sorted_array_2
    };
    int array_sizes[3] = {
            countConsumer0, countConsumer1, countConsumer2
    };


    pthread_t consument, producers[3];
    struct thread threadData[3];

    for (int i = 0; i < 3; ++i) {
        threadData[i].id = i;
        threadData[i].tab = sorted_array[i];
        threadData[i].size = array_sizes[i];
        int rc = pthread_create(&producers[i], NULL, producer, (void *) &threadData[i]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_join(producers[0], NULL);
    fclose(dict);
    fclose(pass);
    pthread_exit(NULL);
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

int checkLetter(const char *tab, int x) {
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

void checkPassword(char *tab, char *passReal) {
    struct stat statsPasswords;
    stat(filenamePasswords, &statsPasswords);
    long sizePasswords = statsPasswords.st_size / PASS_LENGTH;
    for (int i = 0; i < sizePasswords; ++i) {
        if (passwords[i][0] == '#') continue;
        if (strcmp(tab, passwords[i]) == 0) {
            printf("Haslo zlamane: %s   Odpowiadajacy slownik: %s \n", passReal, tab);
            passwords[i][0] = '#';
            brokenPasswords++;
            //TODO register that password and send to main pthread
        }
    }
}

void dictionaryAppending(char tab[], long tier) {
    char str[BUF_SIZE];
    long multiplicationFactor = pow(10, tier);
    int start;
    if (tier == 0)start = 0;
    else {
        start = pow(10, tier - 1);
    }
    char md5[33]; // 32 characters + null terminator
    for (int i = start * 10; i < 10 * multiplicationFactor; ++i) {
        sprintf(str, "%d", i); // cyfry
        char *tmp = strdup(tab);
        strcat(tmp, str); // po
        bytes2md5(tmp, strlen(tmp), md5);
        checkPassword(md5, tmp);
        strcat(str, tmp); //przed
        checkPassword(md5, str);
    }
}

void *producer(void *vargp) {
    struct thread *o = (struct thread *) vargp;
    int size = o->size;
    for (int i = 0; i < size; i++) {
        printf("prod= %d ", o->id);
        printf("haslo:%s \n", &o->tab[i]);
    }
    for (int i = 0; i < size; i++) {
        char md5[33];
        bytes2md5(&o->tab[i], strlen(&o->tab[i]), md5);
        checkPassword(md5, &o->tab[i]);
    }
    int tier = 0;
    while (1) {
        for (int i = 0; i < size; i++) {
            dictionaryAppending(&o->tab[i], tier); //infinite loop
        }
        tier++;
    }
}

void readPasswordsFile(FILE *fp) {
    if ((fp = fopen(filenamePasswords, "r")) == NULL) {
        printf("Error! opening file"); // Program exits if the file pointer returns NULL.
        exit(1);
    }
    struct stat statsPasswords;
    stat(filenamePasswords, &statsPasswords);
    long sizePasswords = statsPasswords.st_size / PASS_LENGTH;

    for (int i = 0; i < sizePasswords; i++) {
        fscanf(fp, "%s", passwords[i]); //"%s%*c"
    }
    for (int i = 0; i < sizePasswords; i++) {
        printf("%d : %s \n", i, passwords[i]);
    }
}

void* consumer(void* vargp)
{
    signal(SIGINT,sigHandler);
}

void sigHandler(int signum)
{
    printf("Otrzymano sygnal. \n Zlamanych hasel: %d",brokenPasswords);
    exit(1);
}

