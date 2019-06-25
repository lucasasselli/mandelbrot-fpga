#ifndef _PALETTE_H
#define _PALETTE_H

typedef struct rgb {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} t_rgb;

int palette_size;

t_rgb base_colors_y[6];
float base_colors_x[6];

t_rgb* palette_colors;

int linInterpolate(float x1, float y1, float x2, float y2, float x){
    float m = (y2-y1)/(x2-x1);
    float q = y1-m*x1;

    return m*x+q;
}

void palette_init(int size){

    palette_size = size;
    palette_colors = (t_rgb*) malloc(sizeof(t_rgb) * palette_size);

    base_colors_y[0] = (t_rgb) {0   , 7   , 100};
    base_colors_y[1] = (t_rgb) {32  , 107 , 203};
    base_colors_y[2] = (t_rgb) {237 , 255 , 255};
    base_colors_y[3] = (t_rgb) {255 , 170 , 0};
    base_colors_y[4] = (t_rgb) {0   , 2   , 0};
    base_colors_y[5] = (t_rgb) {0   , 7   , 100};

    base_colors_x[0] = 0.0;
    base_colors_x[1] = 0.16;
    base_colors_x[2] = 0.42;
    base_colors_x[3] = 0.6425;
    base_colors_x[4] = 0.8575;
    base_colors_x[5] = 1.0;

    for(int palette_index=0; palette_index<palette_size; palette_index++) {

        float palette_k = (float) palette_index / (float) palette_size;

        int palette_segment = 4;
        for (int i=0; i<4; i++){
            if(palette_k >= base_colors_x[i] && palette_k < base_colors_x[i+1]) {
                palette_segment = i;
                break;
            }
        }

        palette_colors[palette_index].red = linInterpolate(base_colors_x[palette_segment], base_colors_y[palette_segment].red, base_colors_x[palette_segment+1], base_colors_y[palette_segment+1].red, palette_k);
        palette_colors[palette_index].green = linInterpolate(base_colors_x[palette_segment], base_colors_y[palette_segment].green, base_colors_x[palette_segment+1], base_colors_y[palette_segment+1].green, palette_k);
        palette_colors[palette_index].blue = linInterpolate(base_colors_x[palette_segment], base_colors_y[palette_segment].blue, base_colors_x[palette_segment+1], base_colors_y[palette_segment+1].blue, palette_k);

#ifdef DEBUG_PALETTE
        printf("Index: %f\t Segment:%d\t R:%d\t G:%d\t B:%d\n", palette_k, palette_segment, palette_colors[palette_index].red, palette_colors[palette_index].green, palette_colors[palette_index].blue);
#endif
    }
}


inline t_rgb palette_getColor(int x){
    return palette_colors[x%palette_size];    
}

#endif
