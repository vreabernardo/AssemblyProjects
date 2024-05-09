#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#define IMAGE_FILENAME "mandel.ppm"
#define COLORMAP "color.map"
#define MAX_ITERATIONS 255
#define NUM_COLORS MAX_ITERATIONS + 1

unsigned char *buffer;

unsigned char computePoint(double cr, double ci);
void updateImage(unsigned char *buffer, unsigned int x, unsigned int y, unsigned char val, unsigned int base);

/* The "compute" function computes the Mandelbrot function over every
   point on a grid that is "nx" points wide by "ny" points tall, where
   (xmin,ymin) and (xmax,ymax) give two corners of the region the
   complex plane. */
void compute(unsigned char *buffer, int nx, int ny, double xmin, double ymin, double xmax, double ymax)
{
  double delta_x = (xmax - xmin) / nx;
  double delta_y = (ymax - ymin) / ny;
  int x, y;
  for (y = 0; y < ny; y++)
  {
    double y_value = ymin + delta_y * y;
    for (x = 0; x < nx; x++)
    {
      double x_value = xmin + delta_x * x;
      unsigned char v = computePoint(x_value, y_value);
      // updateImage(buffer, x, y, v, nx);
      printf("%d \n", v);
    }
    break;
  }
}

/* Output the data contained in the buffer to a Portable Pixmap format
   image file (P6 - Binary Mode).  The parameter "max" should be an upper bound
   for the data values in the buffer. Also there should be a colormap in the
   working directory with the name defined by file_colormap. */
void output_ppm(char *filename, char *file_colormap, unsigned char *buffer, int nx, int ny, int maxC)
{
  int i, r[maxC], g[maxC], b[maxC];
  FILE *f, *f2;
  f = fopen(filename, "w");
  assert(f);
  f2 = fopen(file_colormap, "r");
  assert(f2);
  for (i = 0; i < maxC; i++)
  {
    fscanf(f2, "%d %d %d\n", &r[i], &g[i], &b[i]);
  }
  fprintf(f, "P6\n");
  fprintf(f, "%d %d\n", nx, ny);
  fprintf(f, "%d\n", maxC - 1);
  for (i = 0; i < nx * ny; i++)
  {
    fputc(r[(int)buffer[i]], f);
    fputc(g[(int)buffer[i]], f);
    fputc(b[(int)buffer[i]], f);
  }
  fclose(f);
  fclose(f2);
}

int main(int argc, char **argv)
{
  struct timeval s, t;
  gettimeofday(&s, NULL);
  if (argc != 3)
  {
    printf("Usage: %s size_x size_y\n", argv[0]);
    return 0;
  }
  int nx = atoi(argv[1]);
  int ny = atoi(argv[2]);
  /*
  float xmin = (float)atof(argv[3]);
  float ymin = (float)atof(argv[4]);
  float xmax = (float)atof(argv[5]);
  float ymax = (float)atof(argv[6]);
  */
  // printf("--- Mandelbrot --- \nThe generated image will be %d x %d.\n", nx, ny);

  // printf("Starting Mandelbrot Computation!\n");
  buffer = (unsigned char *)calloc(nx * ny, sizeof(unsigned char));
  compute(buffer, nx, ny, -1, -1, 1, 1);
  // gettimeofday(&t, NULL);
  //("Mandelbrot Computation Complete! Elapsed time (ms) = %ld\n", (t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000);
  // printf("Writing image...\n");
  // output_ppm(IMAGE_FILENAME, COLORMAP, buffer, nx, ny, NUM_COLORS);
  // gettimeofday(&t, NULL);
  // printf("Full execution time (ms) = %ld\n", (t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000);
  // printf("The end!\n");
  free(buffer);
  return (EXIT_SUCCESS);
}
