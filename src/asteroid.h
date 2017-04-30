
#ifndef ASTEROID_H
#define	ASTEROID_H

#include <stdbool.h>

#include "vector.h"
#include "config.h"

typedef struct asteroid {
    float angle,
          speed,
          radius;
    vector position;
    int lvl;
    struct asteroid *next,
                    *prev;
} asteroid;

asteroid *first_a;
asteroid *last_a;

asteroid* new_asteroid(int);
void del_asteroid(asteroid *);
void del_asteroids(asteroid *);

void split_asteroid(asteroid *);

void update_asteroids();

bool point_in_asteroid(asteroid *, vector *);
asteroid *collision(asteroid *, vector);

#endif	/* ASTEROID_H */

