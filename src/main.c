#include <allegro.h>
#include <stdio.h>
#include <malloc.h>
#include <glib.h>
#include "block.h"
#include "blocksyturvy.h"
#include "gamecontrol.h"
#include "gameinput.h"
#include "gamescreen.h"




#define BLACK 16
#define WHITE 31





BITMAP *buffer;
volatile int timer = 0;
volatile int game_time = 0;




/**
 * To keep the game running at the correct frames per second
 */
void do_timer(void) {
  timer++;
} END_OF_FUNCTION (do_timer);




/**
 * To display the current frames per second
 */
void game_time_ticker() {
  game_time++;
}
END_OF_FUNCTION(game_time_ticker)




void startup_game() {
  
  allegro_init();
  
  install_timer();
  
  LOCK_VARIABLE(timer);
  LOCK_FUNCTION(do_timer);
  install_int_ex(do_timer, BPS_TO_TIMER(GAME_TICKER));
  
  LOCK_VARIABLE(game_time);
  LOCK_FUNCTION(game_time_ticker);
  install_int_ex(game_time_ticker, BPS_TO_TIMER(10));

  timer = 0;
  game_time = 0;
  
  srand(time(NULL));
  
  startup_input();
  
  if (start_window() == 0) {
    exit(0);
  }
  
  startup_playarea();
  
  buffer = create_bitmap(SCREEN_W, SCREEN_H);
  clear_to_color(buffer, BLACK);
  
  clear_to_color(screen, BLACK);
  
}




void main_loop() {
  
  int timemark;
  int fps;
  int frames_done;
  int old_time;
  int done;
  PALLETE mypallete;
  
  fps = 0;
  frames_done = 0;
  old_time = 0;
  done = FALSE;
  
  BITMAP *background_bmp;
  
  background_bmp = load_bitmap("../share/background.bmp", mypallete);
  
  while (!done && !key[KEY_ESC]) {
    
    if (key[KEY_F]) {
      toggle_fullscreen();
    }
    
    while (timer == 0) {
      rest(100 / GAME_TICKER);
    }
    
    while (timer > 0) {
      
      timemark = timer;
      
      user_input();
      
      timer--;
      
      if (timemark <= timer)
        break;
      
    }
    
    if (game_time - old_time >= 10) {//i.e. a second has passed since we last measured the frame rate
      fps = frames_done;
      //fps now holds the the number of frames done in the last second
      //you can now output it using textout_ex et al.

      //reset for the next second
      frames_done = 0;
      old_time = game_time;
    }

    blit(background_bmp, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    
    draw_playarea(buffer);
    textprintf_ex(buffer, font, 10, 10, WHITE, -1, "FPS %d", fps);
    
    vsync();
    blit(buffer, screen, 0,0, 0,0, buffer->w, buffer->h);
    
    frames_done++;
    
  }
  
  destroy_bitmap(background_bmp);
  
}




void shutdown_game() {
  shutdown_playarea();
}




int main(int argc, char **argv) {
  
  startup_game();
  
  main_loop();
  
  shutdown_game();

  return 0;
}
END_OF_MAIN()

