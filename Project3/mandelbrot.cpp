#include <iostream>
#include <fstream>
#include <cmath>
#include <omp.h>

// Define the dimensions of the image and the maximum number of iterations
#define WIDTH 1024
#define HEIGHT 1024
#define MAX_ITER 1000

int main() {
    int i, j, k, iter, nthreads;
    double x, y, zx, zy, zx2, zy2, cx, cy;
    double xmin = -2.0, xmax = 1.0, ymin = -1.5, ymax = 1.5;
    double dx = (xmax - xmin) / WIDTH;
    double dy = (ymax - ymin) / HEIGHT;

    // Allocate memory for the pixel array
    int *pixels = new int[WIDTH * HEIGHT];

    // Parallelize the computation of the Mandelbrot set using OpenMP
    #pragma omp parallel shared(pixels) private(i,j,k,iter,x,y,zx,zy,zx2,zy2,cx,cy,nthreads)
    {
        // Get the number of threads being used
        #pragma omp master
        nthreads = omp_get_num_threads();

        // Parallelize the outer loop using OpenMP
        #pragma omp for collapse(2)
        for (i = 0; i < WIDTH; i++) {
            for (j = 0; j < HEIGHT; j++) {
                // Convert pixel coordinates to complex coordinates
                cx = xmin + i * dx;
                cy = ymin + j * dy;

                // Initialize the complex number z to 0
                zx = 0.0;
                zy = 0.0;

                // Initialize the iteration count to 0
                iter = 0;

                // Iterate over the formula z_{n+1} = z_n^2 + c until the modulus of z exceeds 2 or the maximum number of iterations is reached
                while (zx2 + zy2 < 4.0 && iter < MAX_ITER) {
                    zx2 = zx * zx;
                    zy2 = zy * zy;
                    zy = 2.0 * zx * zy + cy;
                    zx = zx2 - zy2 + cx;
                    iter++;
                }

                // Assign the color of the pixel based on the number of iterations required to exceed the modulus of 2
                if (iter == MAX_ITER) {
                    pixels[j * WIDTH + i] = 0;
                } else {
                    pixels[j * WIDTH + i] = static_cast<int>(log(iter) / log(MAX_ITER) * 255);
                }
            }
        }
    }

    // Write the result to a file in the PPM format
    std::ofstream outfile("mandelbrot.ppm", std::ios::binary);
    outfile << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    for (i = 0; i < WIDTH * HEIGHT; i++) {
        outfile << static_cast<char>(pixels[i]);
        outfile << static_cast<char>(pixels[i]);
        outfile << static_cast<char>(pixels[i]);
    }
    outfile.close();

    // Deallocate memory for the pixel array
    delete[] pixels;

    return 0;
}
