#include <math.h>
#include "ship.h"

ship new_ship(vector p) {
    ship s;
    s.position = p;
    s.angle = 0.0;
    s.speed = 3;
    s.life = 3;
    s.time = 3;
    
    return s;
}

void turn_left(ship *s) {
    s->angle -= TURN_SPEED;
}

void turn_right(ship *s) {
    s->angle += TURN_SPEED;
}
