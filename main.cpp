#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>
#include <time.h>

#include "gamelib.h"
#include <string.h>

using namespace std;

void render(void *data) {
  game_t *game = (game_t*)data;
  // make screen black
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);
  /* render code */
  for(int i=0;i<4;i++) {
    draw_rectangle(game->renderer, game->walls[i], {.r=100,.g=0,.b=100});
  }
  draw_rectangle(game->renderer, game->player.position, {.r=255,.g=0,.b=5});
  /* end render code */
  SDL_RenderPresent(game->renderer);
}

int collision(game_t *game, coord_t next_position) {
  for(int i=0;i<4;i++) {
    if(collide(&game->walls[i],&next_position)) {
      return 1; // if hit a wall
    }
  }
  return 0;
}
unsigned int logic(unsigned int t, void *data) {
  game_t *game = (game_t*)data;
  /* game logic */
  if(game->tick_counter%10==0) {
    coord_t position = game->player.position;
    switch(game->player.control.direction) {
    case CONTROL_DIR_LEFT:
      position.x-=2;
      break;
    case CONTROL_DIR_RIGHT:
      position.x+=2;
      break;
    case CONTROL_DIR_UP:
      position.y-=2;
      break;
    case CONTROL_DIR_DOWN:
      position.y+=2;
      break;
    default:
      break;
    }
    if(!collision(game, position)) {
      game->player.position = position;
    }
  }

  /* end game logic */

  // queue render event
  if(game->tick_counter%15==0) {
    SDL_UserEvent p_userevent;
    p_userevent.type = SDL_USEREVENT;
    p_userevent.code = 0;
    p_userevent.data1 = (void*)render;
    p_userevent.data2 = data;

    SDL_Event p_event;
    p_event.type = SDL_USEREVENT;
    p_event.user = p_userevent;

    SDL_PushEvent(&p_event);
  }
  game->tick_counter ++;
  return t;
}
int main(int argc, char* args[]) {
  game_main();
  return 0;
}
