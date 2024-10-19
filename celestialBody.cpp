#include "library.h"

celestialBody::celestialBody(double mass, double radius, double x_0, double y_0, double z_0, double theta_0, double phi_0, double psi_0){
  M = mass;
  r = radius;
  x = x_0;
  y = y_0;
  z = z_0;
  theta = theta_0;
  phi = phi_0;
  psi = psi_0;
}