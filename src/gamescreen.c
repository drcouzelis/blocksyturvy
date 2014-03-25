#include "gamescreen.h"




int screen_width = 640;
int screen_height = 480;
int color_depth = 8;

int fullscreen = 0;




int toggle_fullscreen() {
  
  if (fullscreen) {
    return start_window();
  }
  
  return start_fullscreen();
  
}




int start_window() {
  
  set_color_depth(color_depth);
  
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_width, screen_height, 0, 0)) {
    printf("Failed to set graphics mode to windowed %dx%d. \n", screen_width, screen_height);
    return 0;
  }
  
  fullscreen = 0;
  
  return 1;
  
}




int start_fullscreen() {
  
  set_color_depth(color_depth);
  
  if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screen_width, screen_height, 0, 0)) {
    printf("Failed to set graphics mode to fullscreen %dx%d. \n", screen_width, screen_height);
    return 0;
  }
  
  fullscreen = 1;
  
  return 1;
  
}	

