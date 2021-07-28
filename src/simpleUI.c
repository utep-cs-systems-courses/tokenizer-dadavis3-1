#include <stdio.h>

int main(){

  char phrase[100];
  printf("Input a phrase to be echoed\nTo exit the loop type only 'q'\n");

  while(1){
    printf("Enter phrase: ");
    fgets(phrase,100,stdin);
    if(phrase[0] == 'q'){
      printf("You quitted");
      break;
    }
    printf("Echoed phrase: %s\n", phrase, "\n");
  }
  
  return 0;

}
