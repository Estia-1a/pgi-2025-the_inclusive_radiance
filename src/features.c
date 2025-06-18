#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void dimension(const char *source_path)
{
    unsigned char *pixels = NULL;
    int w = 0, h = 0, channels = 0;

    if (read_image_data(source_path, &pixels, &w, &h, &channels) != 0) {
        fputs("error: impossible de charger l’image « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }

    printf("dimension: %d, %d\n", w, h);
    free(pixels);
}

void first_pixel(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    int result = read_image_data(source_path, &data, &width, &height, &channels);
    if (result != 0) {
        printf("Error reading image\n");
        return;
    }
    if (channels < 3) {
        printf("Need at least 3 channels\n");
        free(data);
        return;
    }
    int r = data[0];
    int g = data[1];
    int b = data[2];
    printf("first_pixel: %d, %d, %d\n", r, g, b);
    free(data);
}

void tenth_pixel(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    int result = read_image_data(source_path, &data, &width, &height, &channels);
    if (result != 0) {
        printf("Error reading image\n");
        return;
    }
    if (channels < 3) {
        printf("Need at least 3 channels\n");
        free(data);
        return;
    }
    if (width < 10) {
        printf("Image must be at least 10 pixels wide\n");
        free(data);
        return;
    }
    int pixel_index = 9 * channels;
    int r = data[pixel_index];
    int g = data[pixel_index + 1];
    int b = data[pixel_index + 2];
    printf("tenth_pixel: %d, %d, %d\n", r, g, b);
    free(data);
}

void second_line(const char *source_path)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, c = 0;
    if (read_image_data(source_path, &data, &w, &h, &c) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int offset = w * c;
    int r = data[offset];
    int g = data[offset + 1];
    int b = data[offset + 2];
    printf("second_line: %d, %d, %d\n", r, g, b);
    free(data);
}

void max_pixel(const char *source_path)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &data, &w, &h, &ch) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int max_sum = -1;
    int max_x = 0, max_y = 0, r = 0, g = 0, b = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y * w + x) * ch;
            int rr = data[idx];
            int gg = data[idx + 1];
            int bb = data[idx + 2];
            int sum = rr + gg + bb;
            if (sum > max_sum) {
                max_sum = sum;
                max_x = x; max_y = y;
                r = rr; g = gg; b = bb;
            }
        }
    }
    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, r, g, b);
    free(data);
}

void min_pixel(const char *source_path)
{
    unsigned char *buf = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &buf, &w, &h, &ch) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int min_sum = INT_MAX;
    int mx = 0, my = 0, r = 0, g = 0, b = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y * w + x) * ch;
            int rr = buf[idx], gg = buf[idx + 1], bb = buf[idx + 2];
            int sum = rr + gg + bb;
            if (sum < min_sum) {
                min_sum = sum;
                mx = x; my = y;
                r = rr; g = gg; b = bb;
            }
        }
    }
    printf("min_pixel (%d, %d): %d, %d, %d\n", mx, my, r, g, b);
    free(buf);
}

typedef struct { unsigned char R, G, B; } PixelRGB;

static PixelRGB* get_pixel(unsigned char *data, unsigned int width, unsigned int height,
                           unsigned int channels, unsigned int x, unsigned int y) {
    if (!data || x >= width || y >= height) return NULL;
    return (PixelRGB*)(data + ((size_t)y * width + x) * channels);
}

void print_pixel(const char *filename, int x, int y) {
    unsigned char *data;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels)) return;
    PixelRGB *p = get_pixel(data, width, height, channels, x, y);
    if (p) printf("print_pixel (%d,%d): %u,%u,%u\n", x, y, p->R, p->G, p->B);
    free(data);
}

void color_red(const char *filename){
    unsigned char *data, *out;
    int width,height,channels;
    if(read_image_data((char*)filename,&data,&width,&height,&channels)) return;
    size_t total = (size_t)width*height;
    out = malloc(total*channels);
    for(size_t i=0;i<total;i++){
        unsigned char *src = data + i*channels;
        unsigned char *dst = out  + i*channels;
        dst[0] = src[0];
        if(channels>1) dst[1] = 0;
        if(channels>2) dst[2] = 0;
        if(channels>3) dst[3] = src[3];
    }
    write_image_data("image_out.bmp",out,width,height);
    free(data);
    free(out);
}

void max_component(const char *source_path, char comp)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &data, &w, &h, &ch) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int comp_idx = (comp == 'G') ? 1 : (comp == 'B') ? 2 : 0;
    int best = -1, bx = 0, by = 0, v = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y * w + x) * ch + comp_idx;
            int cur = data[idx];
            if (cur > best) {
                best = cur;
                bx = x; by = y; v = cur;
            }
        }
    }
    printf("max_component %c (%d, %d): %d\n", comp, bx, by, v);
    free(data);
}

void min_component(const char *source_path, char comp)
{
    unsigned char *dat = NULL;
    int width = 0, height = 0, channels = 0;
    if (read_image_data(source_path, &dat, &width, &height, &channels) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int idx_comp = (comp == 'G') ? 1 : (comp == 'B') ? 2 : 0;
    int best = 256, bx = 0, by = 0, value = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels + idx_comp;
            int cur = dat[i];
            if (cur < best) {
                best = cur; bx = x; by = y; value = cur;
            }
        }
    }
    printf("min_component %c (%d, %d): %d\n", comp, bx, by, value);
    free(dat);
}

void stat_report(const char *source_path)
{
    unsigned char *buf = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &buf, &w, &h, &ch) != 0) return;

    FILE *out = fopen("stat_report.txt", "w");
    if (!out) { free(buf); return; }

    fprintf(out, "dimension: %d, %d\n\n", w, h);

    int maxs = -1, mx = 0, my = 0;
    int mins = INT_MAX, ix = 0, iy = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            int i = (y * w + x) * ch;
            int r = buf[i], g = buf[i+1], b = buf[i+2];
            int s = r + g + b;
            if (s > maxs) { maxs = s; mx = x; my = y; }
            if (s < mins) { mins = s; ix = x; iy = y; }
        }
    fprintf(out, "max_pixel (%d, %d): %d, %d, %d\n\n",
            mx, my,
            buf[(my*w+mx)*ch],
            buf[(my*w+mx)*ch+1],
            buf[(my*w+mx)*ch+2]);
    fprintf(out, "min_pixel (%d, %d): %d, %d, %d\n\n",
            ix, iy,
            buf[(iy*w+ix)*ch],
            buf[(iy*w+ix)*ch+1],
            buf[(iy*w+ix)*ch+2]);

    for (int c = 0; c < 3; c++) {
        int bestMax = -1, bx = 0, by = 0;
        int bestMin = 256, nx = 0, ny = 0;
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++) {
                int v = buf[(y*w+x)*ch + c];
                if (v > bestMax) { bestMax = v; bx = x; by = y; }
                if (v < bestMin) { bestMin = v; nx = x; ny = y; }
            }
        char comp = (c==0?'R':c==1?'G':'B');
        fprintf(out, "max_component %c (%d, %d): %d\n\n",
                comp, bx, by, bestMax);
        fprintf(out, "min_component %c (%d, %d): %d\n\n",
                comp, nx, ny, bestMin);
    }

    fclose(out);
    free(buf);
}

void scale_crop(const char *source_path, int cx, int cy, int w, int h)
{
    unsigned char *orig = NULL;
    int ow = 0, oh = 0, ch = 0;
    if (read_image_data(source_path, &orig, &ow, &oh, &ch) != 0) return;

    unsigned char *out = malloc(w * h * ch);
    if (!out) { free(orig); return; }

    int halfw = w / 2, halfh = h / 2;
    for (int y = 0; y < h; y++) {
        int sy = cy - halfh + y;
        if (sy < 0) sy = 0;
        if (sy >= oh) sy = oh - 1;
        for (int x = 0; x < w; x++) {
            int sx = cx - halfw + x;
            if (sx < 0) sx = 0;
            if (sx >= ow) sx = ow - 1;
            for (int c = 0; c < ch; c++) {
                out[(y * w + x) * ch + c] = orig[(sy * ow + sx) * ch + c];
            }
        }
    }

    write_image_data("image_out.bmp", out, w, h, ch);
    free(orig);
    free(out);
}

void color_green(const char *filename)
{
    unsigned char *data, *out;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels)) return;

    size_t total = (size_t)width * height;
    out = malloc(total * channels);
    for (size_t i = 0; i < total; i++) {
        unsigned char *src = data + i * channels;
        unsigned char *dst = out  + i * channels;
        if (channels > 0) dst[0] = 0;
        if (channels > 1) dst[1] = src[1];
        if (channels > 2) dst[2] = 0;
        if (channels > 3) dst[3] = src[3];
    }

    write_image_data("image_out.bmp", out, width, height);
    free(data);
    free(out);
}