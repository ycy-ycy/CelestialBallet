#include "library.h"

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

  // if collide, search for the collision point

  // if it's a star, return its color

  // if it's a planet, reflect and continue

  return std::make_tuple(0,0,0);
}