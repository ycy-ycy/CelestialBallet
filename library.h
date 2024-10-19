#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>

class rk45{
public:
  rk45(int num_eq);
  
  std::vector<double> solve(double t0, double tf, std::vector<double> p0, std::function<std::vector<double>(std::vector<double>)> dpdt);
};

class celestialBody{
public:
  celestialBody(double mass, double radius, double x_0, double y_0, double z_0, double theta_0, double phi_0, double psi_0);
private:
  double x, y, z, theta, phi, psi;
  double M, r;
};

#endif