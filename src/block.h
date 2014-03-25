#ifndef BLOCK_H
#define BLOCK_H


#include <allegro.h>
#include <glib.h>
#include <stdio.h>
#include "blocksyturvy.h"


typedef GSList BLOCK_LIST;


typedef struct {
  BITMAP *image;
  int hpos;
  int vpos;
} BLOCK;


// YOU LEFT OFF HERE!!
typedef struct {
  BLOCK_LIST *blocks;
  int direction;
  int lowest_vpos;
} BLOCK_SET;


BLOCK_LIST * insert_block(BLOCK_LIST *blocks, BLOCK *block);
BLOCK_LIST * remove_block(BLOCK_LIST *blocks, BLOCK *block);
int block_list_length(BLOCK_LIST *list);

int blocks_collide(BLOCK_LIST *blocks, BLOCK_LIST *other_blocks, int h_change, int v_change, int h_wrap, int v_wrap);

void move_blocks(BLOCK_LIST *blocks, int h_change, int v_change, int h_wrap, int v_wrap);

BLOCK_LIST * find_block_combo(BLOCK_LIST *list, BLOCK *block, BLOCK_LIST *combo);

BLOCK * find_block(BLOCK_LIST *blocks, int x, int y);
BLOCK * highest_block(BLOCK_LIST *blocks, int column, int direction);

void free_blocks(BLOCK_LIST *blocks);


#endif

