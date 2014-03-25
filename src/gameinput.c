#include "gameinput.h"




KEY_CONTROL action_key;
KEY_CONTROL right_key;
KEY_CONTROL left_key;
KEY_CONTROL up_key;
KEY_CONTROL down_key;




void startup_input() {

  install_keyboard();
  
  action_key.key = KEY_SPACE;
  action_key.released = TRUE;
  action_key.timer = 0;
  action_key.delay = GAME_TICKER / 4;

  right_key.key = KEY_RIGHT;
  right_key.released = TRUE;
  right_key.timer = 0;
  right_key.delay = GAME_TICKER / 4;

  left_key.key = KEY_LEFT;
  left_key.released = TRUE;
  left_key.timer = 0;
  left_key.delay = GAME_TICKER / 4;

  up_key.key = KEY_UP;
  up_key.released = TRUE;
  up_key.timer = 0;
  up_key.delay = GAME_TICKER / 4;

  down_key.key = KEY_DOWN;
  down_key.released = TRUE;
  down_key.timer = 0;
  down_key.delay = GAME_TICKER / 4;

}




void perform_key_control(KEY_CONTROL *key_control, void (function)()) {
  
  if (key[key_control->key]) {
    if (key_control->released) {
      
      // Perform action
      function();
      
      key_control->timer = 0;
      
    } else {
      key_control->timer++;
    }
    
    key_control->released = FALSE;
    
    if (key_control->timer >= key_control->delay) {
      key_control->released = TRUE;
    }
    
  } else {
    key_control->released = TRUE;
  }
  
}




void user_input() {
  
  perform_key_control(&up_key, up_key_action);
  perform_key_control(&down_key, down_key_action);
  perform_key_control(&left_key, left_key_action);
  perform_key_control(&right_key, right_key_action);
  perform_key_control(&action_key, action_key_action);
  
}


