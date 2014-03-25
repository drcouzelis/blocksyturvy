#include "gamecontrol.h"




#define USER_POS 4




int playarea_w = 9;
int playarea_h = 16;
int tile_size = 30;

BITMAP *playarea = NULL;

BLOCK_SET *upper_set = NULL;
BLOCK_SET *lower_set = NULL;

int user_side = LOWER;

BITMAP *blockred = NULL;
BITMAP *blockorange = NULL;
BITMAP *blockyellow = NULL;
BITMAP *blockgreen = NULL;
BITMAP *blockblue = NULL;
BITMAP *blockviolet = NULL;

BITMAP *blockselect = NULL;

BITMAP *playarea_bmp = NULL;




BITMAP *random_block_image() {
  
  int num;
  
  num = rand() % 6;
  
  switch (num) {
    case 0: return blockred;
    case 1: return blockorange;
    case 2: return blockyellow;
    case 3: return blockgreen;
    case 4: return blockblue;
    case 5: return blockviolet;
  }
  
  return blockred;
  
}




void startup_playarea() {
  
  BLOCK *block;
  PALLETE mypallete;
  
  int i, j;
  
  playarea = create_bitmap(playarea_w * tile_size, playarea_h * tile_size);
  
  blockred = load_bitmap("../share/blockred.bmp", mypallete);
  blockorange = load_bitmap("../share/blockorange.bmp", mypallete);
  blockyellow = load_bitmap("../share/blockyellow.bmp", mypallete);
  blockgreen = load_bitmap("../share/blockgreen.bmp", mypallete);
  blockblue = load_bitmap("../share/blockblue.bmp", mypallete);
  blockviolet = load_bitmap("../share/blockviolet.bmp", mypallete);
  blockselect = load_bitmap("../share/blockselect.bmp", mypallete);
  playarea_bmp = load_bitmap("../share/playarea.bmp", mypallete);
  set_palette(mypallete);
  
  upper_set = malloc(sizeof(*upper_set));
  upper_set->blocks = NULL;
  upper_set->direction = UPPER;
  upper_set->lowest_vpos = 0;
  
  lower_set = malloc(sizeof(*lower_set));
  lower_set->blocks = NULL;
  lower_set->direction = LOWER;
  lower_set->lowest_vpos = playarea_h - 1;
  
  for (i = 0; i < playarea_w; i++) {
    for (j = 0; j < 4; j++) {
      
      block = malloc(sizeof(*block));
      block->image = random_block_image();
      block->hpos = i;
      block->vpos = j;
      
      upper_set->blocks = insert_block(upper_set->blocks, block);
      
    }
  }
  
  for (i = 0; i < playarea_w; i++) {
    for (j = playarea_h - 4; j < playarea_h; j++) {
      
      block = malloc(sizeof(*block));
      block->image = random_block_image();
      block->hpos = i;
      block->vpos = j;
      
      lower_set->blocks = insert_block(lower_set->blocks, block);
      
    }
  }
  
}




void shutdown_playarea() {
  destroy_bitmap(blockred);
  destroy_bitmap(blockorange);
  destroy_bitmap(blockyellow);
  destroy_bitmap(blockgreen);
  destroy_bitmap(blockblue);
  destroy_bitmap(blockviolet);
  destroy_bitmap(blockselect);
  destroy_bitmap(playarea);
  
  free_blocks(upper_set->blocks);
  free_blocks(lower_set->blocks);
  
  free(upper_set);
  free(lower_set);
  
  destroy_bitmap(playarea_bmp);
}




void draw_block(BLOCK_LIST *blocks) {
  
  if (blocks != NULL) {
    draw_sprite(playarea, ((BLOCK *)(blocks->data))->image, ((BLOCK *)(blocks->data))->hpos * tile_size, ((BLOCK *)(blocks->data))->vpos * tile_size);
    draw_block(blocks->next);
  }
  
}




void draw_blocks() {
  
  BLOCK *highest;
  int pos;
  
  draw_block(upper_set->blocks);
  draw_block(lower_set->blocks);
  
  if (user_side == UPPER) {
    highest = highest_block(upper_set->blocks, USER_POS, upper_set->direction);
    pos = highest ? highest->vpos : upper_set->lowest_vpos;
  } else if (user_side == LOWER) {
    highest = highest_block(lower_set->blocks, USER_POS, lower_set->direction);
    pos = highest ? highest->vpos : lower_set->lowest_vpos;
  }
  
  draw_sprite(playarea, blockselect, USER_POS * tile_size, pos * tile_size);
  
}




void draw_playarea(BITMAP *buffer) {
  
  blit(playarea_bmp, playarea, buffer->w / 2 - playarea->w / 2, buffer->h / 2 - playarea->h / 2,  0, 0, playarea->w, playarea->h);
  
  draw_blocks();
  
  blit(playarea, buffer, 0, 0, buffer->w / 2 - playarea->w / 2, buffer->h / 2 - playarea->h / 2, playarea->w, playarea->h);
  
}



void up_key_action() {
  if (user_side == LOWER) {
    user_side = UPPER;
  }
}




void down_key_action() {
  if (user_side == UPPER) {
    user_side = LOWER;
  }
}




void left_key_action() {
  if (user_side == LOWER) {
    if (blocks_collide(lower_set->blocks, upper_set->blocks, 1, 0, playarea_w, playarea_h) == FALSE) {
      move_blocks(lower_set->blocks, 1, 0, playarea_w, playarea_h);
    }
  } else if (user_side == UPPER) {
    if (blocks_collide(upper_set->blocks, lower_set->blocks, 1, 0, playarea_w, playarea_h) == FALSE) {
      move_blocks(upper_set->blocks, 1, 0, playarea_w, playarea_h);
    }
  }
}




void right_key_action() {
  if (user_side == LOWER) {
    if (blocks_collide(lower_set->blocks, upper_set->blocks, -1, 0, playarea_w, playarea_h) == FALSE) {
      move_blocks(lower_set->blocks, -1, 0, playarea_w, playarea_h);
    }
  } else if (user_side == UPPER) {
    if (blocks_collide(upper_set->blocks, lower_set->blocks, -1, 0, playarea_w, playarea_h) == FALSE) {
      move_blocks(upper_set->blocks, -1, 0, playarea_w, playarea_h);
    }
  }
}




#define COMBO_SIZE 4




void print_block(gpointer data, gpointer user_data) {
  BLOCK *block = (BLOCK *) data;
  printf("Block at %d %d. \n", block->hpos, block->vpos);
}




void flip_a_block(BLOCK_SET *from_set, BLOCK_SET *to_set) {
  
  BLOCK *block;
  
  int from_hpos, from_vpos;
  int to_hpos, to_vpos;
  
  // Get the pos of the block that is moving
  block = highest_block(from_set->blocks, USER_POS, from_set->direction);
  
  // Check if there is actually block in this column to move
  if (block == NULL) {
    return;
  }
  
  from_hpos = USER_POS;
  from_vpos = block->vpos;
  
  // Get the pos of where the block is moving to
  block = highest_block(to_set->blocks, USER_POS, to_set->direction);
  to_hpos = USER_POS;
  to_vpos = block ? block->vpos + to_set->direction : to_set->lowest_vpos;
  
  // Get the block
  block = find_block(from_set->blocks, from_hpos, from_vpos);
  
  // Remove it from its list
  from_set->blocks = remove_block(from_set->blocks, block);
  
  // Change its pos
  block->hpos = to_hpos;
  block->vpos = to_vpos;
  
  // Add it to the other list
  to_set->blocks = insert_block(to_set->blocks, block);
  
}




void action_key_action() {
  
  BLOCK *block;
  BLOCK_LIST *combo;
  
  int from_hpos, from_vpos;
  int to_hpos, to_vpos;
  
  combo = NULL;
  
  if (user_side == LOWER) {
    
    flip_a_block(lower_set, upper_set);

    /*    
    // Check for a combo
    combo = find_block_combo(upper_set->blocks, block, combo);
    g_slist_foreach(combo, print_block, NULL);
    puts("");
    
    // Make them disappear!
    if (block_list_length(combo) >= COMBO_SIZE) {
      
      // YOU LEFT OFF HERE!!
      while (combo != NULL) {
        
        block = (BLOCK *)combo->data;
        
        // Cycle through every block in the combo
        combo = remove_block(combo, block);
        
        // And remove it from the list
        upper_set->blocks = remove_block(upper_set->blocks, block);
        
        free(block);
        
      }
      
    }
    */
    
  }
  
  if (user_side == UPPER) {
    
    flip_a_block(upper_set, lower_set);
    
  }
  
}

