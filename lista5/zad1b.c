#include <stdio.h>
#include <stdlib.h>
int main() {
   // printf() displays the string inside quotation
   char* pPath;
   pPath = getenv ("LOGNAME");
   if(pPath!=NULL)
  	 printf("Hello,%s",pPath);
   return 0;
}
