//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//paddle
#define PADDLE_X 70
#define PADDLE_Y 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initLives(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
  // seed pseudorandom number generator
  srand48(time(NULL));

  // instantiate window
  GWindow window = newGWindow(WIDTH, HEIGHT);

  // instantiate bricks
  initBricks(window);

  // instantiate ball, centered in middle of window
  GOval ball = initBall(window);
  double v_x = (drand48()+1) * 2;
  double v_y = (drand48()+1) * 2;

  // instantiate paddle, centered at bottom of window
  GRect paddle = initPaddle(window);

  // instantiate scoreboard, centered in middle of window, just above ball
  GLabel label = initScoreboard(window);
    
  GLabel life = initLives(window);

  // number of bricks initially
  int bricks = COLS * ROWS;

  // number of lives initially
  int lives = LIVES;

  // number of points initially
  int points = 0;

  // keep playing until game over
  waitForClick();
  while (lives > 0 && bricks > 0)
    {
      GEvent event = getNextEvent(MOUSE_EVENT);
      if (event != NULL){
	if (getEventType(event) == MOUSE_MOVED){
	  int x_paddle = getWidth(paddle);
	  double x_pos = getX(event) - x_paddle / 2;
	  if(x_pos < 0){
	    x_pos = 0;
	  }
	  if(x_pos > WIDTH - x_paddle){
	    x_pos = WIDTH - x_paddle;
	  }
	  setLocation(paddle, x_pos, 530);
	}
      }
      //bounce the ball left right, up down
      //make ball move at angle 
      //init velocity with drand48

      int r = RADIUS;
      move(ball, v_x, v_y);
      // bounce off right
      if (getX(ball) + r*2 >= getWidth(window)){
	v_x = -v_x;
      }
      // bounce off left edge of window
      else if (getX(ball) <= 0){
	v_x = -v_x;
      }
      // at bottom, lose life, pause til click, restart
      else if (getY(ball) + r*2 >= getHeight(window)){
	lives--;
	char s[2];
	sprintf(s, "%i", lives);
	setLabel(life, s);
	setLocation(ball, (WIDTH/2 - 10), (HEIGHT/2 - 10));
	v_x = (drand48()+1) * 2;
	v_y = (drand48()+1) * 2;
	waitForClick();
            
      }
      // bounce off left edge of window
      else if (getY(ball) <= 0){
	v_y = -v_y;
      }
        
        
      //ball collides with paddle
      GObject object = detectCollision(window, ball);
      //printf("object");
      if (object != NULL){
        
	if (object == paddle){
	  //printf("paddle ");
	  if(v_y > 0){
	    v_y = v_y * -1 ;
	  }
                
	}
	//get sement error if object is null!
	//ah fuck, since paddle is also grect, this counter acts it.
	if (strcmp(getType(object), "GRect") == 0 && object != paddle)
	  {
	    //printf("brick ");
	    v_y = -v_y;
	    removeGWindow(window, object);
	    points++;
	    bricks--;
	    updateScoreboard(window, label, points);
	    //sprintf sends output to 1st arg (at buffer or RAM address) rather than std as string
	    //get 3 chars RAM, or 12 bites. 1 +1 for each digit, upto 99, then /0 to store as string
	    //char s[3];
	    //points++;
	    //sprintf(s, "%i", points);
	    //setLabel(label, s);
	  }
      }
      pause(10);
    }

  // wait for click before exiting
  waitForClick();

  // game over
  closeGWindow(window);
  return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
  //init bricks with ROWS 5 and COLS 10
  //each brick is GRect
  int row = ROWS;
  int col = COLS;   
  int bricky = 10;
  int brickx = 35;
    
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      GRect brick = newGRect((j*(brickx+5))+2, 50+(i*(bricky+5)), brickx, bricky);
      setFilled(brick, true);
      switch(i){
      case 0:
	setColor(brick, "RED");
	break;
      case 1:
	setColor(brick, "ORANGE");
	break;
      case 2:
	setColor(brick, "YELLOW");
	break;
      case 3:
	setColor(brick, "GREEN");
	break;
      case 4:
	setColor(brick, "BLUE");
	break;
      default:
	setColor(brick, "BLACK");
      }
            
      add(window, brick); 
    }
  }

}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
  int d = RADIUS*2;
  GOval ball = newGOval((WIDTH/2 - d/2), (HEIGHT/2 - d/2), d, d);
  setFilled(ball, true);
  setColor(ball, "BLACK");
  add(window, ball);
  return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
  // declare x,y of paddle
  int x = PADDLE_X;
  int y = PADDLE_Y;

  //only x moves

  //calc coordinates of paddle based on mouse
  GRect paddle = newGRect(165, 530, x, y);
  setFilled(paddle, true);
  setColor(paddle, "BLACK");
  add(window, paddle); 
    
  return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
  GLabel label = newGLabel("0");
  setFont(label, "SansSerif-36");
  double x = (getWidth(window) - getWidth(label)) / 2;
  double y = (getHeight(window) - getHeight(label)) / 2;
  setLocation(label, x, y);
  add(window, label);

  return label;
}

GLabel initLives(GWindow window){
  GLabel lives = newGLabel("Lives: ");
  setFont(lives, "SansSerif-24");
  setLocation(lives, 270, 30);
  add(window, lives);
    
  GLabel left = newGLabel("3");
  setFont(left, "SansSerif-24");
  setLocation(left, 350, 30);
  add(window, left);
    
  return left;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
  // update label
  char s[12];
  sprintf(s, "%i", points);
  setLabel(label, s);

  // center label in window
  double x = (getWidth(window) - getWidth(label)) / 2;
  double y = (getHeight(window) - getHeight(label)) / 2;
  setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
  // ball's location
  double x = getX(ball);
  double y = getY(ball);

  // for checking for collisions
  GObject object;

  // check for collision at ball's top-left corner
  object = getGObjectAt(window, x, y);
  if (object != NULL)
    {
      return object;
    }

  // check for collision at ball's top-right corner
  object = getGObjectAt(window, x + 2 * RADIUS, y);
  if (object != NULL)
    {
      return object;
    }

  // check for collision at ball's bottom-left corner
  object = getGObjectAt(window, x, y + 2 * RADIUS);
  if (object != NULL)
    {
      return object;
    }

  // check for collision at ball's bottom-right corner
  object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
  if (object != NULL)
    {
      return object;
    }

  // no collision
  return NULL;
}
