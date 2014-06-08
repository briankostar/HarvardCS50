/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

//blank tile
int blank_row;
int blank_col; 

int main(int argc, string argv[])
{
  // greet player
  //greet();

  // ensure proper usage
  if (argc != 2)
    {
      printf("Usage: ./fifteen d\n");
      return 1;
    }

  // ensure valid dimensions
  d = atoi(argv[1]);
  if (d < MIN || d > MAX)
    {
      printf("Board must be between %i x %i and %i x %i, inclusive.\n",
	     MIN, MIN, MAX, MAX);
      return 2;
    }

  // initialize the board
    
  init();
    

  // accept moves until game is won
  while (true)
    {
      // clear the screen
      clear();

      // draw the current state of the board
      draw();

      // saves the current state of the board (for testing)
      save();

      // check for win
      if (won())
        {
	  printf("ftw!\n");
	  break;
        }

      // prompt for move
      printf("Tile to move?: ");
      int tile = GetInt();

      // move if possible, else report illegality
      if (!move(tile))
        {
	  printf("\nIllegal move.\n");
	  usleep(500000);
        }

      // sleep for animation's sake
      usleep(500000);
    }

  // that's all folks
  return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
  printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);
    
}

/**
 * Greets player.
 */
void greet(void)
{
  clear();
  printf("GAME OF FIFTEEN\n");
  //usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
  //draw in reverse order, flip 1 & 2 if tile # is odd(board is even)
  //populate row & col with 2 for loops
  //loop first row until d -1, then within, loop colum
  //for column loop, have a countdown from dxd, draw tile-1, if tile < 1, draw _
    
  int tile_num = d * d - 1;
  
  //loop row d times
  for(int i =0; i < d; i++){
    for(int j = 0; j < d; j++){
      if(tile_num > 0){
	board[i][j] = tile_num;
	//printf(" %d ", tile_num);
	tile_num = tile_num - 1;
      }     
      else{
	board[i][j] = 99;
	blank_row = i;
	blank_col = j;
	//printf(" __");
      }
            
    }
    printf("\n");
  }
  if(d % 2 == 0){
        
    board[d-1][d-3] = 1;
    board[d-1][d-2] = 2;
  }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
  //draw board if there is value
  //if single digit, add space
  printf("\n");
  for(int i =0; i < d; i++){
    for(int j = 0; j < d; j++){
      if (board[i][j] == 99){
	printf(" __ ");    
      }else{
	printf(" %d ", board[i][j]);
      }
      if(board[i][j] < 10){
	printf(" ");    
      }                
    }
    printf("\n\n");
  }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
  //track blank tile, eg [3][3]
  //tiles above, below, left, right is legal, if so,
  //and user's input's position matches legal move's pos, swap position
  //legal = beside blank, and within board
  //search tile's position first. 
  //see each row/col to see if value matches
  int tile_row;
  int tile_col;
  for(int i =0; i < d; i++){
    for(int j = 0; j < d; j++){
      if(board[i][j] == tile){
	tile_row = i;
	tile_col = j;
      }              
    }
  }
  //printf("tile_row:  %i ", tile_row);
  //printf("tile_col:  %i\n", tile_col);
  //printf("blank_row: %i", blank_row);
  //printf("blnk_col:  %i\n", blank_col);
    
  //legal - can only move to where blank is.
  if(tile_row + 1 == blank_row && tile_col == blank_col){
    //swap
    board[blank_row][blank_col] = tile;
    board[tile_row][tile_col] = 99;
    blank_row = tile_row;
    return true;
  }else if(tile_row - 1 == blank_row && tile_col == blank_col){
    board[blank_row][blank_col] = tile;
    board[tile_row][tile_col] = 99;
    blank_row = tile_row;
    return true;
  }else if(tile_col + 1 == blank_col && tile_row == blank_row){
    board[blank_row][blank_col] = tile;
    board[tile_row][tile_col] = 99;
    blank_col = tile_col;
    return true;
  }else if(tile_col - 1 == blank_col && tile_row == blank_row){
    board[blank_row][blank_col] = tile;
    board[tile_row][tile_col] = 99;
    blank_col = tile_col;
    return true;
  }
  return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
  //return true if all numbers pass the test
  int correct_tile = 1;
  int final_tile = d * d - 1;
    
  for(int i =0; i < d; i++){
    for(int j = 0; j < d; j++){
      if(correct_tile <= final_tile){
	if(board[i][j] != correct_tile){
	  //printf("test fail at: %i \n", board[i][j]);
	  //printf("correct_tile: %i\n", correct_tile-1); 
	  return false;
	}
	correct_tile++;
                
      }
            
    }
  }
  return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
  // log
  const string log = "log.txt";

  // delete existing log, if any, before first save
  static bool saved = false;
  if (!saved)
    {
      unlink(log);
      saved = true;
    }

  // open log
  FILE* p = fopen(log, "a");
  if (p == NULL)
    {
      return;
    }

  // log board
  fprintf(p, "{");
  for (int i = 0; i < d; i++)
    {
      fprintf(p, "{");
      for (int j = 0; j < d; j++)
        {
	  fprintf(p, "%i", board[i][j]);
	  if (j < d - 1)
            {
	      fprintf(p, ",");
            }
        }
      fprintf(p, "}");
      if (i < d - 1)
        {
	  fprintf(p, ",");
        }
    }
  fprintf(p, "}\n");

  // close log
  fclose(p);
}
