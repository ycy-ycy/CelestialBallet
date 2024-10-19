#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <tuple>

class rk45{
public:
  rk45(int num_eq);
  
  std::vector<double> solve(double t0, double tf, std::vector<double> p0, std::function<std::vector<double>(std::vector<double>)> dpdt);
};

class celestialBody{
public:
  celestialBody(double mass, double radius, double omega, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0);
  
private:
  double x, y, z;
  double theta, phi, psi;
  double vx, vy, vz;
  double M, r;
  double w;
};

class star : celestialBody{
public:
  star(double mass, double radius, double omega, double temperature, double intensity, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0);

  std::tuple<int,int,int> color(double theta, double phi);

private:
  double T, I;
};

class planet : celestialBody{

};

#endif