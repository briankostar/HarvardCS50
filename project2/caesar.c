#include <cs50.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[]){
  //printf("%d arguments provided\n", argc);
  for (int i = 0; i < argc; i++){
    //printf("Arg %d: %s\n", i+1, argv[i]);
  }
  // check if arg is 2
  if (argc !=2){
    printf("Arg # is wrong. Usage: ./asciimath key\n");
    return 1;
  }
  //get key, check if key is digit
  int k = atoi(argv[1]);
  //printf("k: %i\n", k);
  if (k == 0){
    //printf("Arg 2 is not a digit!\n");
    return 1;
  }
  //mk will always be from 0~25
  int mk = k % 26;
  //printf("mk: %i\n", mk);
    
    
  //ask user for string
  //printf("Type text:");
  string p = GetString();
  //printf("string saved is: %s\n", p); 
  //get length of string
  int length = strlen(p);
  //printf("string length: %d\n", length);
  //check each char for Alpha, lower/upper
    
  for (int i = 0, n = length; i < n; i++)
    {
      if(isalpha(p[i])){
	//printf("%c is alpha", p[i]);
	if(isupper(p[i])){
	  //printf("and %c is upper\n", p[i]);
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
	}else{
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
  //now, turn each char into coresponding char with k input. 
    
  //use aciimath? convert k+p modulo, get proper output
  //turn char to number
  //int letter = 'A';
  //printf("\nCalculating: %c + %d...\n", letter, key);
  //int result = (letter + key);
  //printf("The ASCII value of %c is %d.\n\n", result, result);
  //return 0? if wrong input just return the argument

}

//return 1 if user writes nothing, or too much

//return 0 if good, promp for text, promp that with "rotated" by k positions
//numbers do not change.
//changed = (plain ) + k % 26
//k = x % 26
//cases must be preserved
//argv[] is array of strings, argc is int with number equal to elements in argv
//int k = atoi(argv[1])
