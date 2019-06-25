#ifndef _MANDELBROT_H
#define _MANDELBROT_H

#include "math.h"

typedef struct complex {
    long double x;
    long double y;
} t_complex;

typedef struct mand_result {
    unsigned int n;
    t_complex z;
} t_mand_result;

int mand_max_iter;

void mand_init(int max_iter){
    mand_max_iter = max_iter;
}

inline double mand_abs(t_complex i){
    return sqrt(i.x*i.x+i.y*i.y);
}

inline double mand_abs2(t_complex i){
    return i.x*i.x+i.y*i.y;
}

inline int mand_compute(t_complex c){

    t_complex o;
    t_complex z;

    o.x = 0;
    o.y = 0;
    z.x = 0;
    z.y = 0;

    int n = 0;

    while(n < mand_max_iter && mand_abs2(z) <= 4){

        o.x = z.x * z.x - z.y * z.y; 
        o.y = 2*z.x*z.y;

        z.x = o.x;
        z.y = o.y;

        z.x += c.x;
        z.y += c.y;

        n++; 
    }

    return n;
}

inline t_mand_result mand_compute_adv(t_complex c){

    t_complex o;
    t_complex z;
    t_mand_result r;

    o.x = 0;
    o.y = 0;
    z.x = 0;
    z.y = 0;

    int n = 0;

    while(n < mand_max_iter && mand_abs2(z) <= 4){

        o.x = z.x * z.x - z.y * z.y; 
        o.y = 2*z.x*z.y;

        z.x = o.x;
        z.y = o.y;

        z.x += c.x;
        z.y += c.y;

        n++; 
    }

    r.n = n;
    r.z = z;

    return r;
}

#endif
