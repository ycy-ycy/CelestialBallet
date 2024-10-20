#include "library.h"

void setBoundaries(double r){
  x_m = -r;
  y_m = -r;
  z_m = -r;
  x_p = r;
  y_p = r;
  z_p = r;
}

void setBoundaries(double x_m_0, double y_m_0, double z_m_0, double x_p_0, double y_p_0, double z_p_0){
  x_m = x_m_0;
  y_m = y_m_0;
  z_m = z_m_0;
  x_p = x_p_0;
  y_p = y_p_0;
  z_p = z_p_0;
}

void setBoundaries(double x, double y, double z){
  x_m = -x;
  y_m = -y;
  z_m = -z;
  x_p = x;
  y_p = y;
  z_p = z;
}

ray::ray(double x_0, double y_0, double z_0, double dx_0, double dy_0, double dz_0, const std::vector<celestialBody*> &allBodies){
  x = x_0;
  y = y_0;
  z = z_0;
  dx = dx_0;
  dy = dy_0;
  dz = dz_0;
  I = 1.0;
  bodies = allBodies;
  distance.resize(bodies.size());
}

std::tuple<int, int, int> ray::color() const{
  // move until reflection or hit a star

  // repeat steps

  // in each step, refresh the distance to each body, move to the closest one

  // if out of bounds, return black

  // if collide, search for the collision point

  // if it's a star, return its color

  // if it's a planet, reflect and continue

  return std::make_tuple(0,0,0);
}