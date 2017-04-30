#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "asteroid.h"
#include "config.h"
#include "game.h"

asteroid *new_asteroid(int lvl) {
    asteroid *a = malloc(sizeof(asteroid));
    
    a->lvl = lvl;
    
    a->position.x = (float)(rand() % DISPLAY_WIDTH);
    a->position.y = (float)(rand() % DISPLAY_HEIGHT);
    a->angle = (float)rand();
    
    vector rad = new_vector();
    rad.x = a->position.x + a->lvl*10;
    rad.y = a->position.y;
    a->radius = dist(&a->position, &rad);
    
    a->speed = ASTEROID_SPEED;
    
    a->next = NULL;
    a->prev = last_a;
    last_a = a;
    if(a->prev)
        a->prev->next = a;
    else
        first_a = a;
    
    return a;
}

void del_asteroid(asteroid *a) {
    if(a->prev)
        a->prev->next = a->next;
    else
        first_a = a->next;
    if(a->next)
        a->next->prev = a->prev;
    else
        last_a = a->prev;
    
    free(a);
}

void del_asteroids(asteroid *a) {
    asteroid *pt = a, *tmp;
    while(pt != NULL) {
        tmp = pt->next;
        del_asteroid(pt);
        pt = tmp;
    }
}

void split_asteroid(asteroid *a) {
    asteroid *new;
    int l = a->lvl;
    a->lvl--;
    while(l--) {
        new = new_asteroid(a->lvl);
        new->position = a->position;
        new->angle = a->angle * rand();
        new->speed += 0.5;
    }
    del_asteroid(a);
}

void update_asteroids() {
    asteroid *pt = first_a;
    while (pt != NULL) {
        if(pt->lvl <= 0) {
            del_asteroid(pt);
            break;
        }
        move_object(&pt->position, pt->angle, pt->speed);
        
        pt = pt->next;
    }
}

bool point_in_asteroid(asteroid *a, vector *v) {
    if(dist(v, &a->position) <= a->radius * 1.2)
        return true;
    return false;
}

asteroid *collision(asteroid *a, vector p) {
    asteroid *pt = a;
    while(pt != NULL) {
        if(point_in_asteroid(pt, &p))
            return pt;
        
        pt = pt->next;
    }
    
    return NULL;
}
