#include <math.h>
#include "dynarr.h"
#include "utilities.h"

typedef struct MetaBall {
    float x;
    float y;
    float radius;
 // float sharpness; 
} MetaBall; 



typedef struct FiniteFourier {
//holds type Vec3. Amplitude, frequency, offset. 
    dynarr terms;
} FiniteFourier;

void fin_fourier_init( FiniteFourier* f) {
    f->terms = dynarr_new(sizeof(float) * 3, 8);
} 

void fin_fourier_del(FiniteFourier* f) {
    dynarr_delete(&f->terms);
}

FiniteFourier fin_fourier_new_rand(
    int term_count, float max_amp, float max_frequency,  float diminishing_fac) {

    FiniteFourier f; 
    fin_fourier_init(&f);
    for(int i = 0; i < term_count; i++ ) {
        float amp = pow(diminishing_fac, i) * norm_rand() * max_amp; //wrong. Should not be times max_amp; 
        float frequency = (1.0 / pow(diminishing_fac, i) ) * norm_rand() * max_frequency; // also wrong
        float offset = norm_rand() * frequency;

        float terms[3] = {amp, frequency, offset};
        dynarr_push(&f.terms, terms);
    }

    return f;
}

float fin_fourier_calc(FiniteFourier* f, float t) {
    // printf("time = %f\n", t);
    float acc = 0;
    for(int i = 0; i < f->terms.len; i++ ) {
        //term has 3 elements.
        float* term = (float*)dynarr_get(&f->terms, i); 
        float amp = term[0];
        float frequency = term[1];
        float offset = term[2]; 
        acc += amp * cos(frequency * t - offset);
        free(term);
    }
    return acc; 
}


typedef struct Wanderer { 
    MetaBall m;
    FiniteFourier delta_x;
    FiniteFourier delta_y;
    float time;
} Wanderer;

void wander_init(Wanderer* w) {
    float radius_min = 0.1;
    float radius_max = 0.3;

    float radius = norm_rand() * (radius_max - radius_min) + radius_min; 

    w->m = (MetaBall){.x = 0, .y = 0, .radius = radius};
    w->delta_x = fin_fourier_new_rand(1, 0.3, 3.0, 0.1);
    w->delta_y = fin_fourier_new_rand(1, 0.3, 3.0, 0.1);
    w->time = 0;
}

void wanderer_update(Wanderer* w, float delta_t) {
    w->time += delta_t;

    // float delta_x = fin_fourier_calc(&w->delta_x, w->time);
    // float delta_y = fin_fourier_calc(&w->delta_y, w->time);

    // w->m.x += delta_x;
    // w->m.y += delta_y;


    w->m.x = fin_fourier_calc(&w->delta_x, w->time);
    w->m.y = fin_fourier_calc(&w->delta_y, w->time); 
}