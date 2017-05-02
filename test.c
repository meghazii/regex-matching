#include <stdio.h>

int main(){

  int tab[256];
  tab['a'] = 'a';
  
  //for(int i = 0; i < 256; i++){
  printf("%d --> %d\n", 'a',tab['a']);
    //}
  
  return 0;
}
