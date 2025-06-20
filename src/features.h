#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();

#endif

void dimension(const char *source_path);

void first_pixel(char *source_path);

void tenth_pixel(char *source_path);

void second_line(const char *source_path);

void max_pixel(char *source_path, FILE*);

void min_pixel(char *source_path, FILE*);

void print_pixel(const char *filename,int x,int y);

void color_red(const char *filename);

void max_component(char *, char , FILE*);

void min_component(char *, char, FILE*);

void stat_report(const char *source_path);

void scale_crop(const char *source_path, int cx, int cy, int w, int h);

void scale_nearest(const char *source_path, float scale);

void color_green(const char *filename);

void scale_bilinear(const char *path, float scale);

void color_desaturate(const char *source_path);

void color_blue(const char *filename);

void color_gray(const char *filename);

void color_invert(const char *filename);

void color_gray_luminance(const char *filename);

void rotate_cw(const char *filename);

void rotate_acw(const char *filename);

void mirror_horizontal(const char *filename);

void mirror_vertical(const char *filename);

void mirror_total(const char *filename);