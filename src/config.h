

#ifndef CONFIG_H
#define	CONFIG_H

#include <allegro5/allegro.h>

#define FPS 60

#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480

#define BACKGROUND_COLOR al_map_rgb(0, 0, 0)

#define SHIP_COLOR al_map_rgb(250, 210, 0)

#define SHOOT_TTL 5
#define SHOOT_SPEED 5
#define SHOOT_TTL_STEP 0.1
#define SHOOT_COLOR al_map_rgb(255, 255, 255)

#define ASTEROID_SPEED 2
#define ASTEROID_MAX_LVL 3
#define ASTEROID_COUNT 2
#define ASTEROID_COLOR al_map_rgb(0,0,255)

#endif /* CONFIG_H */
