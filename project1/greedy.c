#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void){

  float user_input = -1;
  int counter =0;
  int remainder =0;
    
  while(user_input < 0){
    printf("How much change is owed? \n");
    user_input = GetFloat();
  }

  int input = round(user_input * 100.0);
  remainder = input;
    
  if (input >= 25){
    counter += input / 25;
    remainder = input % 25;
  }
  if (remainder >= 10){
    counter += remainder / 10;
    remainder = remainder % 10;
  }
  if (remainder >= 5){
    counter += remainder / 5;
    remainder = remainder % 5;
  }
  if (remainder >= 1){
    counter += remainder / 1;
    remainder = remainder % 1;
  }
  printf("%i\n", counter);
}
