#ifndef MAIN_H
#define MAIN_H

#define LOGIC_FPS 1000.0 / 120.0
#define WINDOW_TITLE "Engine"
#define WINDOW_X SDL_WINDOWPOS_CENTERED
#define WINDOW_Y SDL_WINDOWPOS_CENTERED

struct Config {
    int16 windoww, windowh;
    int32 wflags, rflags;
} config;

SDL_Window* window;
SDL_GLContext context;

bool load_config(void);
void quit(void);

#endif
