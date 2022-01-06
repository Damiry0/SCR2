#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>

#define BUF_SIZE 1000

struct leak
        {
            int id;
            char MD5_password[33];
            char* email;
            char* username;
        };

FILE *dict,*pass;

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


int countLines()
{
    int count=1; // counting EOF as well
    for (char c = getc(dict); c != EOF; c = getc(dict))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    return count;
}
void loadPassword()
{
    struct leak leakedPassowords;
    if ((pass = fopen("/home/damiry/Desktop/SCR/SCR2/lista10/test-data1.txt", "r")) == NULL ){
        printf("Error! opening file"); // Program exits if the file pointer returns NULL.
        exit(1);
    }

    while (fscanf(pass,"%d  %s  %s  %s",&leakedPassowords.id,leakedPassowords.MD5_password,leakedPassowords.email,leakedPassowords.username))
    // close file
    fclose (pass);
}

int main()
{
    char buf[BUF_SIZE];
    if ((dict = fopen("/home/damiry/Desktop/SCR/SCR2/lista10/test-dict-mini.txt", "r")) == NULL  ){
        printf("Error! opening file"); // Program exits if the file pointer returns NULL.
        exit(1);
    }
    printf("Number of lines:%d",countLines());
    int numberOfLines= countLines();
     char *strs[numberOfLines];
    for (int i = 0; i < numberOfLines; ++i) {
//        getline()
//        strcpy(strs[i],buf);
//        printf("%s \n",buf);
    }
   // loadPassword();
    fclose(dict);
    return 0;
}


