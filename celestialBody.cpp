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

star::star(double mass, double radius, double omega, double temperature, double intensity, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0) : celestialBody(mass, radius, omega, x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0){
  T = temperature;
  I = intensity;
}

std::tuple<int,int,int> star::color(double theta, double phi){
  double intensity = I;
  double r,g,b;

  if (T<1000.0){ // red
    r = 255.0;
    g = 0.0;
    b = 0.0;
  }
  else if (T<4000.0){ // yellow
    double t = (T-1000.0)/3000.0;
    r = 255.0;
    g = 192.0 * t;
    b = 64.0 * t;
  }
  else if (T<7000.0){ // blue
    double t = (T-4000.0)/3000.0;
    r = 255.0 * (1.0-t);
    g = 192.0 - 64.0 * t;
    b = 255.0 * t;
  }
  else if (T<8800.0){
    double t = (T-7000.0)/1800.0;
    r = 255.0 * t;
    g = 128.0 + 127.0 * t;
    b = 255.0;
  }
  else{ // white
    r = 255.0;
    g = 255.0;
    b = 255.0;
  }
  int r_out = std::round(r * intensity);
  int g_out = std::round(g * intensity);
  int b_out = std::round(b * intensity);
  return std::make_tuple(r_out, g_out, b_out);
}