#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;
void calc_filter(double kernel[][5]) {
   double sigma = 1.0;
   double p;
   double q = 2.0 * sigma * sigma;
   double sum = 0.0;
   for (int x = -2; x <= 2; x++) {
      for (int y = -2; y <= 2; y++) {
         p = x * x + y * y;
         kernel[x + 2][y + 2] = (exp(-p / q)) / (M_PI * q);
         sum += kernel[x + 2][y + 2];
      }
   }
   for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
         kernel[i][j] /= sum;
}