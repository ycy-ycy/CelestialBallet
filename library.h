#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <tuple>
#include <omp.h>

class rk45{
public:
  rk45(int num_eq, double tolerance_abs, double tolerance_rel);

  std::vector<double> solve(double ti, double tf, std::vector<double> p0, std::function<std::vector<double>(std::vector<double>)> dpdt);

private:
  std::vector<double> step(double t, std::vector<double> &p, std::function<std::vector<double>(std::vector<double>)> dpdt);
  double error(const std::vector<double> &y);
  void compute_dense_rs(const std::vector<double> &y_next, const std::vector<double> &y, double h);
  
  int n_eq;
  double atol, rtol;
  double h;
  std::vector<double> pf;

  // We impose a minimum and maximum step size
  static const double hmin, hmax;

  // These are temporary variables used to store the coefficients. You are allowed to
  // define additional temporary variables if you need them.
  std::vector<double> k1, k2, k3, k4, k5, k6, k7, y_tmp, y_err; 

  // These are temporary variables used to store the coefficients
  // used in dense output
  std::vector<double> r1, r2, r3, r4, r5;

  // static const double c2, c3, c4, c5;
  static const double a21, a31, a32, a41, a42, a43, a51, a52, a53, a54, a61, a62, a63, a64, a65;
  static const double a71, a72, a73, a74, a75, a76;
  static const double e1, e2, e3, e4, e5, e6, e7;
  static const double d1, d2, d3, d4, d5, d6, d7;
};

class entity{
public:
  entity(double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0);

public:
  double x, y, z;
  double theta, phi, psi;
  double vx, vy, vz;
};

class celestialBody : entity{
public:
  celestialBody(double mass, double radius, double omega, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0);

public:
  double M, r;
  double w; // rotate
};

class star : celestialBody{
public:
  star(double mass, double radius, double omega, double temperature, double intensity, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0);

  std::tuple<int,int,int> color(double theta, double phi);

public:
  double T, I;
};

class planet : celestialBody{

};

class camera : entity{};

std::function<std::vector<double>(std::vector<double>)> gravity(camera* cam, const std::vector<celestialBody*> &bodies);

#endif