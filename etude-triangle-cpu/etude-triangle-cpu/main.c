#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

// color_t stores r, g, and b values for output
typedef struct {
  uint8_t r, g, b;
} color_t;

// a predefined color_t which corresponds to black
const color_t kBlack = {0, 0, 0};

// vec2 stores any kind of 2-dimensional real-valued coordinates
typedef struct {
  double x, y;
} vec2;

// for clarity, uint16_t is renamed as pixel_t
typedef uint16_t pixel_t;

// the width and height of the image
const pixel_t kWidth  = 1024;
const pixel_t kHeight = 1024;

// see [^1] for details
vec2 solve(pixel_t x, pixel_t y) {
  double x_ = (double)x - 112.0;
  double y_ = (double)y - 166.0; 
  vec2 ret;
  ret.x = (691.0 * x_ - 399.0 * y_) / (800.0 * 691.0);
  ret.y = (  0.0 * x_ + 800.0 * y_) / (800.0 * 691.0);
  return ret;
}

// calculate the pixel at a given pixel coordinate
color_t renderer(pixel_t x, pixel_t y) {
  color_t ret;
  vec2 tmp = solve(x, y);
  if (0 <= tmp.x && 0 <= tmp.y && tmp.x + tmp.y <= 1) {
    ret.g = tmp.x * 255;
    ret.b = tmp.y * 255;
    ret.r = (1.0 - tmp.x - tmp.y) * 255;
  } else {
    ret = kBlack;
  }
  return ret;
}

int main(int argc, char** argv) {
  // allocate the canvas memory
  color_t* canvas = (color_t*)malloc(kWidth * kHeight * sizeof(color_t));

  // start the timer
  struct timespec time_start = {0, 0}, time_end = {0, 0};
  clock_gettime(CLOCK_REALTIME, &time_start);

  // calculate all the pixels
  for (size_t itr = 0; itr < kWidth * kHeight; ++itr) {
    canvas[itr] = renderer(itr % kWidth, itr / kWidth);
  }

  // stop the timer, calculate the duration and print that
  clock_gettime(CLOCK_REALTIME, &time_end);
  double costTime = (time_end.tv_sec - time_start.tv_sec) * 1e9 +
      time_end.tv_nsec - time_start.tv_nsec;
  printf("duration: %.7fms\n", costTime / 1e6);

  // print the image in the form of ppm, coded in ASCII
  FILE* fp = fopen("out.ppm", "w");
  fprintf(fp, "P3\n%d %d\n255\n", kWidth, kHeight);
  for (size_t h = 1024; h > 0; --h) {
    for (size_t w = 0; w < 1024; ++w) {
      fprintf(fp, "%hhu %hhu %hhu\n",
          canvas[(h - 1) * 1024 + w].r,
          canvas[(h - 1) * 1024 + w].g,
          canvas[(h - 1) * 1024 + w].b);
    }
  }
  fclose(fp);

  free(canvas);
  return 0;
}