#include "library.h"

celestialBody::celestialBody(double mass, double radius, double omega, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0){
  M = mass;
  r = radius;
  x = x_0;
  y = y_0;
  z = z_0;
  vx = vx_0;
  vy = vy_0;
  vz = vz_0;
  theta = theta_0;
  phi = phi_0;
  psi = psi_0;
  w = omega;
}

star::star(double mass, double radius, double omega, double temperature, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0) : celestialBody(mass, radius, omega, x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0){
  T = temperature;
}