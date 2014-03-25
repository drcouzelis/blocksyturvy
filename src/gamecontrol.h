#ifndef GAMECONTROL_H
#define GAMECONTROL_H


#include "blocksyturvy.h"
#include "block.h"


void startup_playarea();
void shutdown_playarea();
void draw_playarea(BITMAP *buffer);

void up_key_action();
void down_key_action();
void left_key_action();
void right_key_action();
void action_key_action();


#endif

