#include <math.h>

#include "vector.h"

vector vec_times(vector v, float multipier) {
    vector new;
    new.x = v.x * multipier;
    new.y = v.y * multipier;
    
    return new;
}

vector new_vector() {
    vector new;
    new.x = 0;
    new.y = 0;
    
    return new;
}

float dist(vector *v1, vector *v2) {
    return sqrt(pow(v2->x - v1->x, 2) + pow(v2->y - v1->y, 2));
}
