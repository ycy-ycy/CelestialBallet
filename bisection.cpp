#include "library.h"

double bisection(std::function<double(double)> f, double x_min, double x_max, int n_max = 1000, double tol = 1e-10){
  double x_mid = (x_min + x_max) / 2.0;
  double f_min = f(x_min);
  double f_max = f(x_max);
  double f_mid = f(x_mid);
  double error = std::abs(x_max - x_min);
  int n = 0;
  while (error > tol && n < n_max){
    if (f_min * f_mid < 0){
      x_max = x_mid;
      f_max = f_mid;
    } else {
      x_min = x_mid;
      f_min = f_mid;
    }
    x_mid = (x_min + x_max) / 2.0;
    f_mid = f(x_mid);
    error = std::abs(x_max - x_min);
    n++;
  }

  if (error > tol){
    x_mid = std::numeric_limits<double>::quiet_NaN();
  }

  return x_mid;
}
