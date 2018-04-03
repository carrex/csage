#ifndef CONFIG_H
#define CONFIG_H

/* To be replaced by JSON/YAML/something as a loaded config */

#define LOGIC_FPS 1000.0 / 120.0
#define WINDOW_TITLE "CSage"
#define WINDOW_X SDL_WINDOWPOS_CENTERED
#define WINDOW_Y SDL_WINDOWPOS_CENTERED

struct Config {
    int16 windoww, windowh;
};

#endif
