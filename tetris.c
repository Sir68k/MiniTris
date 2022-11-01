#include "tetris.h"
#include "firmware.h"
#include "display.h"
#include "button.h"

static const uint8_t tetrominos[]  = {0b00001111, 0b11001100, 0b01001110, 0b01101100, 0b11000110, 0b10001110, 0b00101110};
static const uint8_t tetrominosS[] = {4, 2, 3, 3, 3, 3, 3};


static uint8_t getTetrominoBlock(uint8_t tetromino[], uint8_t x, uint8_t y)
{  
   return (tetromino[y/2] >> 7-(y%2*4 + x) ) & 1;
}

static void setTetrominoBlock(uint8_t tetromino[], uint8_t x, uint8_t y, uint8_t value)
{  
   tetromino[y/2] |= value << 7-(y%2*4 + x);
}

static void rotateTetromino(uint8_t tetromino[], uint8_t s, uint8_t tetromino_out[])
{  
  for (int x=0; x<s; x++)
    for (int y=0; y<s; y++)
      setTetrominoBlock(tetromino_out, y, s-x-1, getTetrominoBlock(tetromino, x, y));
}

static void drawTetromino(uint8_t tetromino[], uint8_t s, int8_t xx, int8_t yy, uint8_t value)
{
  for (int x=0; x<s; x++)
    for (int y=0; y<s; y++)
      if (getTetrominoBlock(tetromino, x, y) && yy + y >= 0)
        set_pixel(yy+y, 7-(xx+x), value);
}

static uint8_t checkCollision(uint8_t tetromino[], uint8_t s, int8_t xx, int8_t yy)
{
  if (yy == TETRIS_HEIGHT - 1) return 1;
  
  for (int x=0; x<s; x++)
    for (int y=0; y<s; y++)
      if (getTetrominoBlock(tetromino, x, y) && read_pixel(yy+y, 7-(xx+x)))
        return 1;
        
  return 0; 
}

static void gameOver()
{
  queue_direct_display_cmd("\xc0\x00 GAME ",8);
  update_display(); 
  tron_dly_tsk(100);

  queue_direct_display_cmd("\xc0\x00 OVER ",8);
  update_display(); 
  tron_dly_tsk(200);
  
  reset();
}

static void displaySetLine(int x, int d) {
  for (int y=0; y<7; y++) {
    set_pixel(x, y, (d >> y) & 1);
  }
}

static int displayGetLine(int x) {
  int res = 0;
  for (int y=0; y<7; y++) {
    res = res | (read_pixel(x, y) << y);
  }
  return res;
}


void playTetris()
{
  //clear_display();
  
  uint8_t t_type    = get_sys_ltime() & 7;// % 7; // RANDOM
  if (t_type==7) t_type=0;
  uint8_t t_block[] = {tetrominos[t_type], 0};
  uint8_t t_size    = tetrominosS[t_type];
  int8_t t_x        = 2;
  int8_t t_y        = -1;
  
  long last_move = 0;
  uint8_t lines = 0;
  
  drawTetromino(t_block, t_size, t_x, t_y, 1);
  update_display();
  
  //Remove it from the buffer, we only want to see it if we are going to update the display
  //Now we can use the buffer for calculations (collision, etc)
  drawTetromino(t_block, t_size, t_x, t_y, 0);
  
  int key;
  uint32_t millis;

  while (1)
  {    
    millis = get_sys_ltime();
    //here we store if we really need to update the display
    uint8_t update = 0;
    
    //Fall down!
    if (millis - last_move > TETRIS_FALL_DELAY)
    {
      last_move = millis;
      
      if (checkCollision(t_block, t_size, t_x, t_y + 1))
      {
        drawTetromino(t_block, t_size, t_x, t_y, 1);
        t_type    = millis & 7; //RANDOM
        if (t_type==7) t_type=0;
        t_block[0] = tetrominos[t_type];
        t_block[1] = 0; 
        t_size    = tetrominosS[t_type];
        t_x       = 2;
        t_y       = -1;
        
        if (checkCollision(t_block, t_size, t_x, t_y))
        {
          gameOver();
          return; 
        }
      }
      else
        t_y++;
       
      update = 1;
    }

    update_buttons();

    //Move tetromino left
    if(check_button(KeyLeft))
    {
      if (!checkCollision(t_block, t_size, t_x-1, t_y))
        t_x--;
      update = 1;
    } 
    
    //Move tetromino right
    if(check_button(KeyRight))
    {
      if (!checkCollision(t_block, t_size, t_x+1, t_y))
        t_x++;
      update = 1;
    } 
  
    //Rotate tetromino
    if(check_button(KeyUp))
    {
      uint8_t t[] = {0, 0};
      rotateTetromino(t_block, t_size, t);
      if (!checkCollision(t, t_size, t_x, t_y))
      {
        t_block[0] = t[0];
        t_block[1] = t[1];
      }
      update = 1;
    } 
    
    //Check if we need to clear a full line
    uint8_t moveDown = 0;
    for (int yy=TETRIS_HEIGHT-1; yy>=0; yy--)
    {
       if (moveDown)
         displaySetLine(yy+1, displayGetLine(yy));
       else if (displayGetLine(yy) == 0b1111111)
         moveDown = 1; 
    }
    if (moveDown)
    {
      displaySetLine(0, 0); //clear the top row
      lines++; //update score
    }
         
    //Did we clear a line or change the tetromino? Update the display
    if(moveDown || update)
    {
      drawTetromino(t_block, t_size, t_x, t_y, 1);
      update_display(); 
      drawTetromino(t_block, t_size, t_x, t_y, 0);
    }
    
    //Move tetromino down. There is a reason it's here on the end.
    if (check_button(KeyDown))
    {
      //Basically, we make that the falldown routine will get called. Less work and you can hard place blocks this way :)
      last_move = 0;
      continue;
    }
    
    //Small delay, just so that our CPU has some breathing time
    tron_dly_tsk(4);
  }  
}
