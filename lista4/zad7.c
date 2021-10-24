#include <stdio.h>
char * napis = "Witajcie moi mili ...";
int main(){
  unsigned int index =0;
  for (index; ; index++){ // brak warunku stopu, następuje naruszenie ochrony pamięci
                          // sygnał - SIGENGV  strace -t ./a.out do pomiaru czasu, z flagą -t
                          // na koncu są operacje co wykonuja sie najdluzej
    printf("%c",napis[index]);
  }
  return 0;
}
