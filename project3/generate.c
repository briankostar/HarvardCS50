/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
  // check we have 2 or 3 argument
  if (argc != 2 && argc != 3)
    {
      printf("Usage: ./generate n [s]\n");
      return 1;
    }

  // save the first arg as int n, with atoi(str->int)
  int n = atoi(argv[1]);

  // if 3 arg given, use the 2nd arg as seed, if not, use time as seed
  //unsigned int casts seed into only + int
  if (argc == 3)
    {
      srand((unsigned int) atoi(argv[2]));
    }
  else
    {
      srand((unsigned int) time(NULL));
    }

  // loop for each number in n, and print w modulo limit 65536
  for (int i = 0; i < n; i++)
    {
      printf("%i\n", rand() % LIMIT);
    }

  // that's all folks
  return 0;
}
