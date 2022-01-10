#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <sys/stat.h>

#define BUF_SIZE 1000
#define PASS_LENGTH 33

//struct leak

//        {
//            int id;
//            char MD5_password[33];
//            char* email;
//            char* username;
//        };

FILE *dict, *pass;
char *filenamePasswords = "/home/damiry/Desktop/SCR/SCR2/lista10/test-data1.txt";
char *filenameDictionaries = "/home/damiry/Desktop/SCR/SCR2/lista10/test-dict-mini.txt";


int countLinesInFile(FILE *fp);
int longestLineInFile(FILE *fp);



//void bytes2md5(const char *data, int len, char *md5buf) {
//    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
//    const EVP_MD *md = EVP_md5();
//    unsigned char md_value[EVP_MAX_MD_SIZE];
//    unsigned int md_len, i;
//    EVP_DigestInit_ex(mdctx, md, NULL);
//    EVP_DigestUpdate(mdctx, data, len);
//    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
//    EVP_MD_CTX_free(mdctx);
//    for (i = 0; i < md_len; i++) {
//        snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
//    }
//}

int main() {
// passwords
    char passwords[1000][PASS_LENGTH];
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
    for (int i = 0; i < lines; i++) {
        fscanf(dict, "%s", dictionaries[i]);
    }
    for (int i = 0; i < lines; i++) {
        printf("%d : %s \n", i, dictionaries[i]);
    }

    fclose(dict);
    fclose(pass);
    return 0;
}

int countLinesInFile(FILE *fp) {
    char c;
    int count = 1;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
        {count++;}

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


