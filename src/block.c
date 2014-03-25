#include "block.h"




BLOCK_LIST * insert_block(BLOCK_LIST *blocks, BLOCK *block) {
  return g_slist_append(blocks, block);
}  




BLOCK_LIST * remove_block(BLOCK_LIST *blocks, BLOCK *block) {
  return g_slist_remove(blocks, block);
}




int block_list_length(BLOCK_LIST *list) {
  return g_slist_length(list);
}




typedef struct {
  int x;
  int y;
} POSITION;




int compare_block_position(gconstpointer a, gconstpointer b) {
  
  BLOCK *block;
  POSITION *pos;
  
  block = (BLOCK *) a;
  pos = (POSITION *) b;
  
  if (block != NULL) {
    if (block->hpos == pos->x && block->vpos == pos->y) {
      return 0;
    }
  }
  return 1;
}




BLOCK * find_block(BLOCK_LIST *blocks, int x, int y) {
  
  GSList *list;
  POSITION pos;
  pos.x = x;
  pos.y = y;
  
  list = g_slist_find_custom(blocks, &pos, compare_block_position);
  
  if (list != NULL) {
    return (BLOCK *)list->data;
  }
  
  return NULL;
  
}




int neighbor_block(BLOCK *block1, BLOCK *block2) {
  
  if (block1 == NULL || block2 == NULL) {
    return 0;
  }
  
  if (
    (block1->hpos + 1 == block2->hpos && block1->vpos == block2->vpos) ||
    (block1->hpos - 1 == block2->hpos && block1->vpos == block2->vpos) ||
    (block1->hpos == block2->hpos && block1->vpos + 1 == block2->vpos) ||
    (block1->hpos == block2->hpos && block1->vpos - 1 == block2->vpos)
  ) {
    return 1;
  }
  
  return 0;
  
}




BLOCK_LIST * find_block_combo(BLOCK_LIST *list, BLOCK *block, BLOCK_LIST *combo) {
  
  BLOCK_LIST *ptr;
  
  if (list == NULL) {
    return NULL;
  }
  
  if (block == NULL) {
    return NULL;
  }
  
  ptr = list;
  
  // For all blocks
  while (ptr != NULL) {
    
    // If it is touching and if it is the same color
    if (neighbor_block(block, (BLOCK *)ptr->data) && ((BLOCK *)ptr->data)->image == block->image) {
      
      // If it is not in the list
      if (g_slist_find(combo, ptr->data) == NULL) {
        
        // Remove the block
        //blocks = remove_block(blocks, ptr);
        
        // Put it in the list
        combo = insert_block(combo, ptr->data);
        
        // Find combo blocks
        combo = find_block_combo(list, (BLOCK *)ptr->data, combo);
        
      }
      
    }
    
    ptr = ptr->next;
      
  }
  
  return combo;
  
}




int blocks_collide(BLOCK_LIST *blocks, BLOCK_LIST *other_blocks, int h_change, int v_change, int h_wrap, int v_wrap) {
  
  int hpos;
  int vpos;
  
  if (blocks != NULL) {
    
    hpos = ((BLOCK *)(blocks->data))->hpos + h_change;
    if (hpos >= h_wrap) {
      hpos -= h_wrap;
    } else if (hpos < 0) {
      hpos += h_wrap;
    }
    vpos = ((BLOCK *)(blocks->data))->vpos + v_change;
    if (vpos >= v_wrap) {
      vpos -= v_wrap;
    } else if (vpos < 0) {
      vpos += v_wrap;
    }
    
    if (find_block(other_blocks, hpos, vpos) != NULL) {
      return TRUE;
    }
    
    return blocks_collide(blocks->next, other_blocks, h_change, v_change, h_wrap, v_wrap);
    
  }
  
  return FALSE;
  
}




void move_blocks(BLOCK_LIST *blocks, int h_change, int v_change, int h_wrap, int v_wrap) {
  if (blocks != NULL) {
    ((BLOCK *)(blocks->data))->hpos += h_change;
    if (((BLOCK *)(blocks->data))->hpos >= h_wrap) {
      ((BLOCK *)(blocks->data))->hpos -= h_wrap;
    } else if (((BLOCK *)(blocks->data))->hpos < 0) {
      ((BLOCK *)(blocks->data))->hpos += h_wrap;
    }
    ((BLOCK *)(blocks->data))->vpos += v_change;
    if (((BLOCK *)(blocks->data))->vpos >= v_wrap) {
      ((BLOCK *)(blocks->data))->vpos -= v_wrap;
    } else if (((BLOCK *)(blocks->data))->vpos < 0) {
      ((BLOCK *)(blocks->data))->vpos += v_wrap;
    }
    move_blocks(blocks->next, h_change, v_change, h_wrap, v_wrap);
  }
}




BLOCK * highest_block(BLOCK_LIST *blocks, int column, int direction) {
  
  BLOCK *highest;
  
  if (blocks != NULL) {
    
    highest = highest_block(blocks->next, column, direction);
    
    /**
     * If this block isn't even in the column
     * we are looking at then just skip it.
     */
    if (((BLOCK *)(blocks->data))->hpos != column) {
      return highest;
    }
    
    if (highest == NULL) {
      return ((BLOCK *)(blocks->data));
    }
    
    if (direction == UPPER && ((BLOCK *)(blocks->data))->vpos > highest->vpos) {
      return ((BLOCK *)(blocks->data));
    }
    
    if (direction == LOWER && ((BLOCK *)(blocks->data))->vpos < highest->vpos) {
      return ((BLOCK *)(blocks->data));
    }
    
    return highest;
    
  }
  
  return NULL;
  
}




void free_blocks(BLOCK_LIST *blocks) {
  g_slist_free(blocks);
}

