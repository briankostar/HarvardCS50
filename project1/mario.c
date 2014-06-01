#include <stdio.h>
#include <cs50.h>

int main(void){
  //do {
  //printf("Height: ");
  int x = 25;
    
  while(x < 0 || x > 23){
    printf("Height: ");
    x = GetInt();
  }
  //}
  //while (x < 0 && x > 23);
    
  int y = x;
  for (int i = 0; i < x; i++){
        
    for (int j = 1; j < y; j++){
      printf(" ");
    }
    y = y - 1;
    for (int k = 0; k < i; k++){
      printf("#");
    }
    printf("##\n");   
  }
    
}
