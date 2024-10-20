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
  vx = dx_0;
  vy = dy_0;
  vz = dz_0;
  I = 1.0;
  bodies = allBodies;
}

std::tuple<int, int, int> ray::color(){
  // move until reflection or hit a star

  // repeat steps
  while (true) {
    // if out of bounds, return black
    if (x < x_m || x > x_p || y < y_m || y > y_p || z < z_m || z > z_p) { return std::make_tuple(0,0,0); }

    // refresh distance to each body
    updateDistances();

    // move as far as possible
    bool collide = move();

    // if collide, search for the collision point
    if (collide){
      // pass self to the closest body and get a function to calculate distance to surface
      std::function<double(double)> distanceToSurface = closest_body->rayDistance(this);
      // use bisection to find the exact point of collision
      double x_p = bisection(distanceToSurface, -(closest_body->r + closest_body->fluctuation_R) * 0.6, (closest_body->r + closest_body->fluctuation_R) * 0.6);
      // if not collide, continue
      if (std::isnan(x_p)) { continue; }
      // move
      x += vx * x_p;
      y += vy * x_p;
      z += vz * x_p;
      // anlges on the celestial body
      std::tuple<double, double> angles = closest_body->getAngles(x,y,z);
      // if it's a star, return its color
      if (star* collideStar = dynamic_cast<star*>(closest_body)){
        return collideStar->color(std::get<0>(angles), std::get<1>(angles), I);
      }
      // if it's a planet, reflect and continue
      if (planet* collidePlanet = dynamic_cast<planet*>(closest_body)){
        collidePlanet->reflect(this, std::get<0>(angles), std::get<1>(angles));
      }
    }

    return std::make_tuple(0,0,0);
  }
}

void ray::updateDistances(){
  distances.clear();
  min_dist = 0;
  closest_body = nullptr;
  for (int i = 0; i < bodies.size(); i++) {
    double delta_x = bodies[i]->x - x;
    double delta_y = bodies[i]->y - y;
    double delta_z = bodies[i]->z - z;
    double dist = std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
    if (!closest_body) {
      min_dist = dist < min_dist? dist : min_dist;
      closest_body = bodies[i];
    }
    else{
      min_dist = dist;
      closest_body = bodies[i];
    }
    distances.push_back(std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z));
  }
}

bool ray::move(){
  x += vx * min_dist;
  y += vy * min_dist;
  z += vz * min_dist;
  double delta_x = closest_body->x - x;
  double delta_y = closest_body->y - y;
  double delta_z = closest_body->z - z;
  double dist = std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
  return dist <= (closest_body->r + closest_body->fluctuation_R) * 1.12; // add a small margin to avoid missing collisions
}