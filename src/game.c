#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>

#include "game.h"
#include "config.h"
#include "asteroid.h"
#include "shooter.h"

game* new_game(vector s) {
    game *g = malloc(sizeof(game));
    g->Ship = new_ship(vec_times(s, 0.5));
    g->Size = s;
    g->status = Pause;
    
    // TODO: add asteroids
    int i;
    for(i = 0; i <= ASTEROID_COUNT; i++)
        new_asteroid(ASTEROID_MAX_LVL);
    
    return g;
}

void del_game(game *g) {
    del_asteroids(first_a);  
    del_shoots(first_s);
    free(g);
}

bool font() {
    ttf_font = NULL;
    al_init_font_addon();
    if(!al_init_ttf_addon())
        return false;
    ttf_font = al_load_ttf_font("font.ttf", 20, 0);
    return ttf_font != NULL;
}

void update_game(game *g) {
    if(g->status == Quit) {
        del_game(g);
    } else {
        if(first_a == NULL)
            g->status = Win;
        else {
            update_shoots();
            update_asteroids();
            update_collisions();

            update_ship(g, first_a);
        }
    }
}

void draw_game(game *g) {
    int i;
    
    al_clear_to_color(BACKGROUND_COLOR);
    if(g->status == Pause || g->status == Win || g->status == Lose)
        draw_menu(g);
    else if(g->status != Quit) {
        draw_ship(g);
        draw_shoots(g);
        draw_asteroids(g);
    }
}

void draw_ship(game *game) {
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_rotate_transform(&trans, game->Ship.angle);
    al_translate_transform(&trans,
                           (int)game->Ship.position.x,
                           (int)game->Ship.position.y);
    al_use_transform(&trans);
    
    float w = game->Ship.time >= 0 ? 1 : 4;
    
    al_draw_line(-8, 20, 0, 0, SHIP_COLOR, w);
    al_draw_line(8, 20, 0, 0, SHIP_COLOR, w);
    al_draw_line(-6, 15, -1, 15, SHIP_COLOR, w);
    al_draw_line(6, 15, 1, 15, SHIP_COLOR, w);
}

void draw_shoots(game *g) {
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_use_transform(&trans);
    
    shoot *pt;
    pt = first_s;
    while(pt != NULL) {
        al_draw_pixel(pt->position.x, pt->position.y, SHOOT_COLOR);
        pt = pt->next;
    }
}

void draw_asteroids(game *g) {
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_use_transform(&trans);
    
    asteroid *pt = first_a;
    while(pt != NULL) {
        al_draw_line(
                pt->position.x, pt->position.y + pt->lvl*10,
                pt->position.x + pt->lvl*10, pt->position.y,
                ASTEROID_COLOR, 2.0
        );
        al_draw_line(
                pt->position.x, pt->position.y - pt->lvl*10,
                pt->position.x + pt->lvl*10, pt->position.y,
                ASTEROID_COLOR, 2.0
        );
        al_draw_line(
                pt->position.x, pt->position.y + pt->lvl*10,
                pt->position.x - pt->lvl*10, pt->position.y,
                ASTEROID_COLOR, 2.0
        );
        al_draw_line(
                pt->position.x, pt->position.y - pt->lvl*10,
                pt->position.x - pt->lvl*10, pt->position.y,
                ASTEROID_COLOR, 2.0
        );
        
        pt = pt->next;
    }
}

void draw_menu(game *g) {
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_use_transform(&trans);
    
    int x, y;
    x = (g->Size.x - 60) / 2;
    y = 0;
    al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y, ALLEGRO_ALIGN_LEFT, "MENU");
    
    
    char *msg;
    
    if(g->status == Win || g->status == Lose) {
        x = (g->Size.x - 250) / 2;
        y = 50;
        msg = g->status == Win ? "YOU WON!! GAME OVER" : "YOU LOST. GAME OVER";
        al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y, ALLEGRO_ALIGN_LEFT, msg);
    }
    
    msg = "'c' to configure";
    x = (g->Size.x - 640+100) / 2;
    y = (g->Size.y + 5) / 2;
    al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y,
                 ALLEGRO_ALIGN_LEFT, msg);
    
    msg = "Enter to play";
    x = (g->Size.x - 640+100) / 2;
    y = (g->Size.y + 50) / 2;
    al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y,
                 ALLEGRO_ALIGN_LEFT, msg);
    
    msg = "Escape to exit";
    x = (g->Size.x - 640+100) / 2;
    y = (g->Size.y + 100) / 2;
    al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y,
                 ALLEGRO_ALIGN_LEFT, msg);
    
    msg = "Use the arrow keys to move and space to shoot";
    y = g->Size.y - 130;
    x = (g->Size.x - 640+100)/2;
    al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y,
                 ALLEGRO_ALIGN_LEFT, msg);
    
    msg = "If your ship is bold, you cannot be destroyed";
    y = g->Size.y - 80;
    x = (g->Size.x - 640+100)/2;
    al_draw_text(ttf_font, al_map_rgb(200, 200, 200), x, y,
                 ALLEGRO_ALIGN_LEFT, msg);
}

void bound_position(vector *p) {
    while(p->x > 640.0) {
        p->x -= 640.0;
    }
    while(p->x < 0.0) {
        p->x += 640.0;
    }
    while(p->y > 480.0) {
        p->y -= 480.0;
    }
    while(p->y < 0.0) {
        p->y += 480.0;
    }
}

void move_object(vector *pos, float angle, int speed) {
    pos->x -= speed * sin(-angle);
    pos->y -= speed * cos(-angle);
    bound_position(pos);
}

void update_collisions() {
    asteroid *shot = hit_shoot(first_s, first_a);
    if(shot != NULL) {
        split_asteroid(shot);
    }
}

void update_ship(game *g, asteroid *a) {
    if(g->Ship.time >= 0)
        g->Ship.time -= 0.1;
    
    if(collision(a, g->Ship.position) && g->Ship.time <= 0) {
        if(--g->Ship.life <= 0)
            g->status = Lose;
        g->Ship.position = vec_times(g->Size, 0.5);
        g->Ship.time = 5;
    }
}
