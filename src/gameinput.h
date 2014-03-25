#ifndef GAMEINPUT_H
#define GAMEINPUT_H


#include <allegro.h>
#include "blocksyturvy.h"
#include "gamecontrol.h"


typedef struct {
  int key;
  int released;
  int timer; // Update every tick while the key is pressed
  int delay; // Number of ticks to wait until the action for this key is performed again
} KEY_CONTROL;


void startup_input();
void perform_key_control(KEY_CONTROL *key_control, void (function)());
void user_input();


#endif

