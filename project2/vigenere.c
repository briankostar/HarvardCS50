#include <cs50.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[]){
  if (argc !=2){
    printf("Arg # is wrong. Usage: ./asciimath key\n");
    return 1;
  }
  for(int i = 0, n = strlen(argv[1]); i < n; i++){
    if(isalpha(argv[1][i]) == 0){
      printf("Type only alphabets!");
      return 1;
    }
  }
  //store key
  string key = argv[1];
  //get text
  string p = GetString();
  //printf("Ciphertext: ");
    
    
    
  //rotate the key under text. 
  //How? 1. get length of text, no, length of alphachars combined.
  //For each char, if its alpha, assign a number rotating.. modulo here.
  int kposition = 0;
  int klength = strlen(key);
  for(int i = 0, n = strlen(p); i < n; i++){
    if(isalpha(p[i])){
      //get key char's position in int. Eg, A is 0, first at pos 0.
      int x = kposition % klength;
      char alpha = key[x];
      int mk = toupper((int) alpha) - 65; 
      //printf("alpha: %d", alpha);
      //printf("mk: %d", mk);
      kposition += 1; 
      //now caesar cipher using alphapos as key
      //ah shit, have to do this sep. for upper and lower..
      if(isupper(p[i])){
	int letter = (int) p[i];
	//printf("letter: %d\n", letter);
	int result = (letter + mk) % 91;
	if (result < 65){
	  result += 65;
	}
	//printf("result: %d\n", result);
	char result_c = (char) result;
	//printf("result char: %c\n", result_c);
	printf("%c", result_c);
      }
      else{
	//printf("and %c is lower\n", p[i]);
	int letter = (int) p[i];
	//printf("letter: %d\n", letter);
	int result = (letter + mk) % 123;
	if (result < 97){
	  result += 97;
	}
	//printf("result: %d\n", result);
	char result_c = (char) result;
	//printf("result char: %c\n", result_c);
	printf("%c", result_c);
      }
            
    }else{
      printf("%c", p[i]);
    }
    
  }
  printf("\n");
}

