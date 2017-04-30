#ifndef SHOOTER_H
#define	SHOOTER_H

#include "ship.h"
#include "vector.h"
#include "asteroid.h"

typedef struct shoot {
    float angle, time;
    vector position;
    int speed;
    struct shoot *next, *prev;
} shoot;

shoot *first_s;
shoot *last_s;

shoot* new_shoot(ship *);
void update_shoots();
void del_shoot(shoot *);
asteroid *hit_shoot(shoot *, asteroid *);

#endif	/* SHOOTER_H */
