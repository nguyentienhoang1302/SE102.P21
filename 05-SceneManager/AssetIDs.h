#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_TREE	6
#define OBJECT_TYPE_CLOUD	7
#define OBJECT_TYPE_COLORBLOCK	8
#define OBJECT_TYPE_PIPE	9
#define OBJECT_TYPE_MBLOCK	10
#define OBJECT_TYPE_MUSHROOM 11
#define OBJECT_TYPE_DARKZONE 12

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_GROUND 50000
#define ID_SPRITE_GROUND_BEGIN (ID_SPRITE_GROUND+1000)
#define ID_SPRITE_GROUND_MIDDLE (ID_SPRITE_GROUND+2000)
#define ID_SPRITE_GROUND_END (ID_SPRITE_GROUND+3000)
#define ID_SPRITE_GROUND_LOWERBEGIN (ID_SPRITE_GROUND+4000)
#define ID_SPRITE_GROUND_LOWERMIDDLE (ID_SPRITE_GROUND+5000)
#define ID_SPRITE_GROUND_LOWEREND (ID_SPRITE_GROUND+6000)
#define ID_SPRITE_GROUND_SMILEYGROUND (ID_SPRITE_GROUND+7000)
#define ID_SPRITE_GROUND_BLUEBRICK (ID_SPRITE_GROUND+8000)

#define ID_SPRITE_TREE 60000
#define ID_SPRITE_TREE_TOPLEFT (ID_SPRITE_TREE+1000)
#define ID_SPRITE_TREE_TOPRIGHT (ID_SPRITE_TREE+2000)
#define ID_SPRITE_TREE_LEFT (ID_SPRITE_TREE+3000)
#define ID_SPRITE_TREE_MIDDLE (ID_SPRITE_TREE+4000)
#define ID_SPRITE_TREE_RIGHT (ID_SPRITE_TREE+5000)
#define ID_SPRITE_TREE_BOTLEFT (ID_SPRITE_TREE+6000)
#define ID_SPRITE_TREE_BOTRIGHT (ID_SPRITE_TREE+7000)
#define ID_SPRITE_TREE_BUSH (ID_SPRITE_TREE+8000)
#define ID_SPRITE_TREE_DARKTOPLEFT (ID_SPRITE_TREE+9100)
#define ID_SPRITE_TREE_DARKTOPRIGHT (ID_SPRITE_TREE+9200)
#define ID_SPRITE_TREE_DARKLEFT (ID_SPRITE_TREE+9300)
#define ID_SPRITE_TREE_DARKRIGHT (ID_SPRITE_TREE+9400)

#define ID_SPRITE_CLOUD 70000
#define ID_SPRITE_CLOUD_TOPLEFT (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_TOPMIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_TOPRIGHT (ID_SPRITE_CLOUD+3000)
#define ID_SPRITE_CLOUD_BOTTOMLEFT (ID_SPRITE_CLOUD+4000)
#define ID_SPRITE_CLOUD_BOTTOMMIDDLE (ID_SPRITE_CLOUD+5000)
#define ID_SPRITE_CLOUD_BOTTOMRIGHT (ID_SPRITE_CLOUD+6000)

#define ID_SPRITE_COLORBLOCK 80000
#define ID_SPRITE_CCOLORBLOCK_WHITE_1 (ID_SPRITE_COLORBLOCK+1001)
#define ID_SPRITE_CCOLORBLOCK_WHITE_2 (ID_SPRITE_COLORBLOCK+1002)
#define ID_SPRITE_CCOLORBLOCK_WHITE_3 (ID_SPRITE_COLORBLOCK+1003)
#define ID_SPRITE_CCOLORBLOCK_WHITE_4 (ID_SPRITE_COLORBLOCK+1004)
#define ID_SPRITE_CCOLORBLOCK_WHITE_5 (ID_SPRITE_COLORBLOCK+1005)
#define ID_SPRITE_CCOLORBLOCK_WHITE_6 (ID_SPRITE_COLORBLOCK+1006)
#define ID_SPRITE_CCOLORBLOCK_WHITE_7 (ID_SPRITE_COLORBLOCK+1007)
#define ID_SPRITE_CCOLORBLOCK_WHITE_8 (ID_SPRITE_COLORBLOCK+1008)
#define ID_SPRITE_CCOLORBLOCK_WHITE_9 (ID_SPRITE_COLORBLOCK+1009)
#define ID_SPRITE_CCOLORBLOCK_PINK_1 (ID_SPRITE_COLORBLOCK+2001)
#define ID_SPRITE_CCOLORBLOCK_PINK_2 (ID_SPRITE_COLORBLOCK+2002)
#define ID_SPRITE_CCOLORBLOCK_PINK_3 (ID_SPRITE_COLORBLOCK+2003)
#define ID_SPRITE_CCOLORBLOCK_PINK_4 (ID_SPRITE_COLORBLOCK+2004)
#define ID_SPRITE_CCOLORBLOCK_PINK_5 (ID_SPRITE_COLORBLOCK+2005)
#define ID_SPRITE_CCOLORBLOCK_PINK_6 (ID_SPRITE_COLORBLOCK+2006)
#define ID_SPRITE_CCOLORBLOCK_PINK_7 (ID_SPRITE_COLORBLOCK+2007)
#define ID_SPRITE_CCOLORBLOCK_PINK_8 (ID_SPRITE_COLORBLOCK+2008)
#define ID_SPRITE_CCOLORBLOCK_PINK_9 (ID_SPRITE_COLORBLOCK+2009)
#define ID_SPRITE_CCOLORBLOCK_BLUE_1 (ID_SPRITE_COLORBLOCK+3001)
#define ID_SPRITE_CCOLORBLOCK_BLUE_2 (ID_SPRITE_COLORBLOCK+3002)
#define ID_SPRITE_CCOLORBLOCK_BLUE_3 (ID_SPRITE_COLORBLOCK+3003)
#define ID_SPRITE_CCOLORBLOCK_BLUE_4 (ID_SPRITE_COLORBLOCK+3004)
#define ID_SPRITE_CCOLORBLOCK_BLUE_5 (ID_SPRITE_COLORBLOCK+3005)
#define ID_SPRITE_CCOLORBLOCK_BLUE_6 (ID_SPRITE_COLORBLOCK+3006)
#define ID_SPRITE_CCOLORBLOCK_BLUE_7 (ID_SPRITE_COLORBLOCK+3007)
#define ID_SPRITE_CCOLORBLOCK_BLUE_8 (ID_SPRITE_COLORBLOCK+3008)
#define ID_SPRITE_CCOLORBLOCK_BLUE_9 (ID_SPRITE_COLORBLOCK+3009)
#define ID_SPRITE_CCOLORBLOCK_GREEN_1 (ID_SPRITE_COLORBLOCK+4001)
#define ID_SPRITE_CCOLORBLOCK_GREEN_2 (ID_SPRITE_COLORBLOCK+4002)
#define ID_SPRITE_CCOLORBLOCK_GREEN_3 (ID_SPRITE_COLORBLOCK+4003)
#define ID_SPRITE_CCOLORBLOCK_GREEN_4 (ID_SPRITE_COLORBLOCK+4004)
#define ID_SPRITE_CCOLORBLOCK_GREEN_5 (ID_SPRITE_COLORBLOCK+4005)
#define ID_SPRITE_CCOLORBLOCK_GREEN_6 (ID_SPRITE_COLORBLOCK+4006)
#define ID_SPRITE_CCOLORBLOCK_GREEN_7 (ID_SPRITE_COLORBLOCK+4007)
#define ID_SPRITE_CCOLORBLOCK_GREEN_8 (ID_SPRITE_COLORBLOCK+4008)
#define ID_SPRITE_CCOLORBLOCK_GREEN_9 (ID_SPRITE_COLORBLOCK+4009)

#define ID_SPRITE_PIPE 90000
#define ID_SPRITE_PIPE_TOPLEFT (ID_SPRITE_PIPE+1000)
#define ID_SPRITE_PIPE_TOPRIGHT (ID_SPRITE_PIPE+2000)
#define ID_SPRITE_PIPE_BOTTOMLEFT (ID_SPRITE_PIPE+3000)
#define ID_SPRITE_PIPE_BOTTOMRIGHT (ID_SPRITE_PIPE+4000)
#define ID_SPRITE_PIPE_DARK_TOPLEFT (ID_SPRITE_PIPE+5000)
#define ID_SPRITE_PIPE_DARK_TOPRIGHT (ID_SPRITE_PIPE+6000)
#define ID_SPRITE_PIPE_DARK_BOTTOMLEFT (ID_SPRITE_PIPE+7000)
#define ID_SPRITE_PIPE_DARK_BOTTOMRIGHT (ID_SPRITE_PIPE+8000)

#define ID_SPRITE_MBLOCK 100000
#define ID_ANI_MBLOCK (ID_SPRITE_MBLOCK+1000)
#define ID_ANI_MBLOCK_EMPTY (ID_SPRITE_MBLOCK+2000)

#define ID_SPRITE_MUSHROOM 110000
#define ID_ANI_MUSHROOM_RED 110000
#define ID_ANI_MUSHROOM_GREEN 111000

#define ID_SPRITE_DARKZONE 120000
#define ID_SPRITE_DARKZONE_BEGIN (ID_SPRITE_DARKZONE+1000)
#define ID_SPRITE_DARKZONE_MIDDLE (ID_SPRITE_DARKZONE+2000)
#define ID_SPRITE_DARKZONE_END (ID_SPRITE_DARKZONE+3000)