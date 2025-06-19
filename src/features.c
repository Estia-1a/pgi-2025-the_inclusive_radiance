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
    unsigned char *data = NULL;
    int w = 0, h = 0, channels = 0;

    if (read_image_data(source_path, &data, &w, &h, &channels) != 0) {
        fputs("error: impossible de charger l’image « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }

    printf("dimension: %d, %d\n", w, h);
    free_image_data(data);
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
        free_image_data(data);
        return;
    }
    int r = data[0];
    int g = data[1];
    int b = data[2];
    printf("first_pixel: %d, %d, %d\n", r, g, b);
    free_image_data(data);
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
        free_image_data(data);
        return;
    }
    if (width < 10) {
        printf("Image must be at least 10 pixels wide\n");
        free_image_data(data);
        return;
    }
    int pixel_index = 9 * channels;
    int r = data[pixel_index];
    int g = data[pixel_index + 1];
    int b = data[pixel_index + 2];
    printf("tenth_pixel: %d, %d, %d\n", r, g, b);
    free_image_data(data);
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
    free_image_data(data);
}

void max_pixel(char *source_path, FILE* ) 
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
    free_image_data(data);
}

void min_pixel(char *source_path, FILE*)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &data, &w, &h, &ch) != 0) {
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
            int rr = data[idx], gg = data[idx + 1], bb = data[idx + 2];
            int sum = rr + gg + bb;
            if (sum < min_sum) {
                min_sum = sum;
                mx = x; my = y;
                r = rr; g = gg; b = bb;
            }
        }
    }
    printf("min_pixel (%d, %d): %d, %d, %d\n", mx, my, r, g, b);
    free_image_data(data);
}

typedef struct { unsigned char R, G, B; } PixelRGB;

static PixelRGB* get_pixel(unsigned char *data, unsigned int width, unsigned int height,
                           unsigned int channels, unsigned int x, unsigned int y) {
    if (!data || x >= width || y >= height) return NULL;
    return (PixelRGB*)(data + ((size_t)y * width + x) * channels);
}

void print_pixel(const char *filename, int x, int y)
{
    unsigned char *data;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels)) return;
    PixelRGB *p = get_pixel(data, width, height, channels, x, y);
    if (p) printf("print_pixel (%d,%d): %u,%u,%u\n", x, y, p->R, p->G, p->B);
    free_image_data(data);
}

void color_red(const char *filename)
{
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
   
    read_image_data(filename, &data, &width, &height, &n);
 
    int size = width * height * n;
 
    for (int i = 0; i < size; i += n) {
        data[i+1] = 0;      
        data[i+2] = 0;      
    }
 
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);    
}

void max_component(char *source_path, char component, FILE*) 
{
    unsigned char *data = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &data, &w, &h, &ch) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int comp_idx = (component == 'G') ? 1 : (component == 'B') ? 2 : 0;
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
    printf("max_component %c (%d, %d): %d\n", component, bx, by, v);
    free_image_data(data);
}

void min_component(char *source_path, char component, FILE*) 
{
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;
    if (read_image_data(source_path, &data, &width, &height, &channels) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int idx_comp = (component == 'G') ? 1 : (component == 'B') ? 2 : 0;
    int best = 256, bx = 0, by = 0, value = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels + idx_comp;
            int cur = data[i];
            if (cur < best) {
                best = cur; bx = x; by = y; value = cur;
            }
        }
    }
    printf("min_component %c (%d, %d): %d\n", component, bx, by, value);
    free_image_data(data);
}

void stat_report(const char *source_path)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &data, &w, &h, &ch) != 0) return;

    FILE *out = fopen("stat_report.txt", "w");
    if (!out) { free_image_data(data); return; }

    fprintf(out, "dimension: %d, %d\n\n", w, h);

    int maxs = -1, mx = 0, my = 0;
    int mins = INT_MAX, ix = 0, iy = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            int i = (y * w + x) * ch;
            int r = data[i], g = data[i+1], b = data[i+2];
            int s = r + g + b;
            if (s > maxs) { maxs = s; mx = x; my = y; }
            if (s < mins) { mins = s; ix = x; iy = y; }
        }
    fprintf(out, "max_pixel (%d, %d): %d, %d, %d\n\n",
            mx, my,
            data[(my*w+mx)*ch],
            data[(my*w+mx)*ch+1],
            data[(my*w+mx)*ch+2]);
    fprintf(out, "min_pixel (%d, %d): %d, %d, %d\n\n",
            ix, iy,
            data[(iy*w+ix)*ch],
            data[(iy*w+ix)*ch+1],
            data[(iy*w+ix)*ch+2]);

    for (int c = 0; c < 3; c++) {
        int bestMax = -1, bx = 0, by = 0;
        int bestMin = 256, nx = 0, ny = 0;
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++) {
                int v = data[(y*w+x)*ch + c];
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
    free_image_data(data);
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

void color_green(const char *filename) {
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
   
    read_image_data(filename, &data, &width, &height, &n);
 
    int size = width * height * n;
 
    for (int i = 0; i < size; i += n) {
        data[i] = 0;      
        data[i + 2] = 0;      
    }
 
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);    
}

void scale_nearest(const char *source_path, float scale)
{
    unsigned char *src = NULL;
    int ow = 0, oh = 0, ch = 0;
    if (read_image_data(source_path, &src, &ow, &oh, &ch) != 0) return;
    int nw = (int)(ow * scale);
    int nh = (int)(oh * scale);
    unsigned char *dst = malloc(nw * nh * ch);
    if (!dst) { free(src); return; }
    for (int y = 0; y < nh; y++) {
        int sy = (int)floorf(y / scale);
        if (sy < 0) sy = 0; else if (sy >= oh) sy = oh - 1;
        for (int x = 0; x < nw; x++) {
            int sx = (int)floorf(x / scale);
            if (sx < 0) sx = 0; else if (sx >= ow) sx = ow - 1;
            for (int c = 0; c < ch; c++)
                dst[(y * nw + x) * ch + c] = src[(sy * ow + sx) * ch + c];
        }
    }
    write_image_data("image_out.bmp", dst, nw, nh, ch);
    free(src);
    free(dst);
}

void scale_bilinear(const char *path, float scale)
{
    unsigned char *src = NULL;
    int ow = 0, oh = 0, ch = 0;
    if (read_image_data(path, &src, &ow, &oh, &ch) != 0) return;
    int nw = (int)(ow * scale), nh = (int)(oh * scale);
    unsigned char *dst = malloc(nw * nh * ch);
    if (!dst) { free(src); return; }
    for (int y = 0; y < nh; y++) {
        float gy = y / scale;
        int y0 = (int)gy, y1 = y0 + 1 < oh ? y0 + 1 : oh - 1;
        float dy = gy - y0;
        for (int x = 0; x < nw; x++) {
            float gx = x / scale;
            int x0 = (int)gx, x1 = x0 + 1 < ow ? x0 + 1 : ow - 1;
            float dx = gx - x0;
            for (int c = 0; c < ch; c++) {
                int i00 = (y0 * ow + x0) * ch + c;
                int i01 = (y0 * ow + x1) * ch + c;
                int i10 = (y1 * ow + x0) * ch + c;
                int i11 = (y1 * ow + x1) * ch + c;
                float v = (1 - dx) * (1 - dy) * src[i00]
                        + dx * (1 - dy) * src[i01]
                        + (1 - dx) * dy       * src[i10]
                        + dx * dy             * src[i11];
                dst[(y * nw + x) * ch + c] = (unsigned char)(v + 0.5f);
            }
        }
    }
    write_image_data("image_out.bmp", dst, nw, nh, ch);
    free(src);
    free(dst);
}

void color_desaturate(const char *source_path)
{
    unsigned char *src = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &src, &w, &h, &ch)) return;
    unsigned char *dst = malloc(w * h * ch);
    if (!dst) { free(src); return; }

    for (int i = 0; i < w * h; i++) {
        int idx = i * ch;
        int r = src[idx];
        int g = src[idx + 1];
        int b = src[idx + 2];
        int mn = r < g ? (r < b ? r : b) : (g < b ? g : b);
        int mx = r > g ? (r > b ? r : b) : (g > b ? g : b);
        unsigned char v = (unsigned char)((mn + mx) / 2);
        dst[idx]     = v;
        dst[idx + 1] = v;
        dst[idx + 2] = v;
        if (ch == 4) dst[idx + 3] = src[idx + 3];
    }

    write_image_data("image_out.bmp", dst, w, h, ch);
    free(src);
    free(dst);
}

void color_blue(const char *filename) {
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
   
    read_image_data(filename, &data, &width, &height, &n);
 
    int size = width * height * n;
 
    for (int i = 0; i < size; i += n) {
        data[i] = 0;      
        data[i + 1] = 0;      
    }
 
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);    
}

void color_gray(const char *filename) {
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
    int gray;
   
    read_image_data(filename, &data, &width, &height, &n);
 
    int size = width * height * n;
 
    for (int i = 0; i < size; i += n) {
        gray = (data[i] + data[i+1] + data[i+2]) / 3;
        data[i] = gray;      
        data[i + 1] = gray;
        data[i + 2] = gray;      
    }
 
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);    
}

void color_invert(const char *filename) {
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
   
    read_image_data(filename, &data, &width, &height, &n);
 
    int size = width * height * n;
 
    for (int i = 0; i < size; i += n) {
        data[i] = 255 - data[i];
        data[i+1] = 255 - data[i+1];      
        data[i+2] = 255 - data[i+2];      
    }
 
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);    
}

void color_gray_luminance(const char *filename) {
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
    int gray;
   
    read_image_data(filename, &data, &width, &height, &n);
 
    int size = width * height * n;
 
    for (int i = 0; i < size; i += n) {
        gray = (data[i]*0.21 + data[i+1]*0.72 + data[i+2]*0.07);
        data[i] = gray;      
        data[i + 1] = gray;
        data[i + 2] = gray;      
    }
 
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);    
}

void rotate_cw(const char *filename) {
    unsigned char *data = NULL;
    int width = 0, height = 0, n = 0;
 
    read_image_data(filename, &data, &width, &height, &n);
 
    int new_width = height;
    int new_height = width;
    int size = width * height * n;
 
    char *rotated_data = malloc(size);
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * n;
            int rota_x = height - 1 - y;
            int rota_y = x;
            int rota_index = (rota_y * new_width + rota_x) * n;
 
            for (int i = 0; i < n; i++) {
                rotated_data[rota_index + i] = data[index + i];
            }
        }
    }

    write_image_data("image_out.bmp", out, new_width, new_height);
    free_image_data(data);
}

void rotate_acw(const char *filename)
{
    unsigned char *data, *out;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels))
        return;

    int new_width  = height;
    int new_height = width;
    size_t total   = (size_t)width * height;
    out = malloc(total * channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = y;
            int new_y = width - 1 - x;
            unsigned char *src = data + ((size_t)y * width + x) * channels;
            unsigned char *dst = out  + ((size_t)new_y * new_width + new_x) * channels;
            for (int c = 0; c < channels; c++)
                dst[c] = src[c];
        }
    }

    write_image_data("image_out.bmp", out, new_width, new_height);
    free_image_data(data);
}

void mirror_horizontal(const char *filename)
{
    unsigned char *data, *out;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels))
        return;
    size_t total = (size_t)width * height;
    out = malloc(total * channels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = width - 1 - x;
            int new_y = y;
            unsigned char *src = data + ((size_t)y * width + x) * channels;
            unsigned char *dst = out  + ((size_t)new_y * width + new_x) * channels;
            for (int c = 0; c < channels; c++)
                dst[c] = src[c];
        }
    }
    write_image_data("image_out.bmp", out, width, height);
    free_image_data(data);
}

void mirror_vertical(const char *filename)
{
    unsigned char *data, *out;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels))
        return;
    size_t total = (size_t)width * height;
    out = malloc(total * channels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = x;
            int new_y = height - 1 - y;
            unsigned char *src = data + ((size_t)y * width + x) * channels;
            unsigned char *dst = out  + ((size_t)new_y * width + new_x) * channels;
            for (int c = 0; c < channels; c++)
                dst[c] = src[c];
        }
    }
    write_image_data("image_out.bmp", out, width, height);
    free_image_data(data);
}

void mirror_total(const char *filename)
{
    unsigned char *data, *out;
    int width, height, channels;
    if (read_image_data((char*)filename, &data, &width, &height, &channels))
        return;
    size_t total = (size_t)width * height;
    out = malloc(total * channels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = width  - 1 - x;
            int new_y = height - 1 - y;
            unsigned char *src = data + ((size_t)y * width + x) * channels;
            unsigned char *dst = out  + ((size_t)new_y * width + new_x) * channels;
            for (int c = 0; c < channels; c++)
                dst[c] = src[c];
        }
    }
    write_image_data("image_out.bmp", out, width, height);
    free_image_data(data);
}