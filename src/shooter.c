#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "shooter.h"
#include "ship.h"
#include "game.h"

shoot* new_shoot(ship *sh) {
    shoot *new = malloc(sizeof(shoot));
    new->position = sh->position;
    new->angle = sh->angle;
    new->speed = SHOOT_SPEED;
    new->time = SHOOT_TTL;
    
    new->next = NULL;
    new->prev = last_s;
    last_s = new;
    if(new->prev)
        new->prev->next = new;
    else
        first_s = new;
    
    return new;
}

void update_shoots() {
    shoot *pt;
    pt = first_s;
    while(pt != NULL) {
        pt->time -= SHOOT_TTL_STEP;
        if(pt->time <= 0) {
            del_shoot(pt);
            break;
        }
        
        move_object(&pt->position, pt->angle, pt->speed);
        
        pt = pt->next;
    }
    
}

void del_shoot(shoot *s) {
    if(s->prev)
        s->prev->next = s->next;
    else
        first_s = s->next;
    
    if(s->next)
        s->next->prev = s->prev;
    else
        last_s = s->prev;
    
    free(s);
}

void del_shoots(shoot *s) {
    shoot *p = s, *tmp;
    while(p != NULL) {
        tmp = p->next;
        del_shoot(p);
        p = tmp;
    }
}

asteroid *hit_shoot(shoot *s, asteroid *a) {
    shoot *pt = s;
    asteroid *ret;
    
    while(pt != NULL) {
        ret = collision(a, pt->position);
        if(ret) {
            pt->time = 0;
            return ret;
        }
        pt = pt->next;
    }
    
    return NULL;
}
