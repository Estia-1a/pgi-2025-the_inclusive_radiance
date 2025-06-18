#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();

#endif

void dimension(const char *source_path);

void first_pixel(char *source_path);

void tenth_pixel(char *source_path);

void second_line(const char *source_path);

void max_pixel(const char *source_path);

void min_pixel(const char *source_path);

void print_pixel(const char *filename,int x,int y);

void color_red(const char *filename);

void max_component(const char *source_path, char comp);

void min_component(const char *source_path, char comp);

void stat_report(const char *source_path);

void scale_crop(const char *source_path, int cx, int cy, int w, int h);

void scale_nearest(const char *source_path, float scale);

void color_green(const char *filename);