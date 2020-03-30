#ifndef GAMELIB_H
#define GAMELIB_H
#include <SDL2/SDL.h>
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define N_MISSILES 32
#define GAME_END 1

using std::string;

enum GAME_STATE {
                 GAME_STATE_BEGIN, // 0
                 GAME_STATE_DONE,  // 1
                 GAME_STATE_OVER,  // 2
};
enum CONTROL_DIRECTION {
                         CONTROL_DIR_NONE, // 0
                         CONTROL_DIR_LEFT, // 1
                         CONTROL_DIR_RIGHT,// 2
                         CONTROL_DIR_UP,   // 3
                         CONTROL_DIR_DOWN, // 4
};

typedef SDL_Rect coord_t;

typedef struct color_s {
  uint8_t r,g,b;
} color_t;

typedef struct control_s {
  CONTROL_DIRECTION direction;
} control_t;

typedef struct player_s {
  control_t control;      // direction
  coord_t   position;     // where the player is
} player_t;


typedef struct game_s {
  SDL_Renderer *renderer; // graphics
  GAME_STATE game_state;  // game running?
  int tick_counter = 0;   // time
  player_t player;        // player
  coord_t walls[4];
} game_t;


void draw_rectangle(SDL_Renderer *p_renderer, SDL_Rect rect, color_t color);
void render(void *data);
void game_main();
unsigned int logic(unsigned int t, void *data);
void draw_text(SDL_Renderer *p_renderer, SDL_Rect rect, color_t color, char*text);
int collide(coord_t *a, coord_t *b);
#endif
