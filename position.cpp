#include "library.h"

std::vector<double> getPosition(camera* cam, const std::vector<celestialBody*> &bodies){
  std::vector<double> position(6 + bodies.size() * 6);
  position[0] = cam->x;
  position[1] = cam->y;
  position[2] = cam->z;
  position[3] = cam->vx;
  position[4] = cam->vy;
  position[5] = cam->vz;
  for(int i = 0; i < bodies.size(); i++){
    position[6 + i * 6 + 0] = bodies[i]->x;
    position[6 + i * 6 + 1] = bodies[i]->y;
    position[6 + i * 6 + 2] = bodies[i]->z;
    position[6 + i * 6 + 3] = bodies[i]->vx;
    position[6 + i * 6 + 4] = bodies[i]->vy;
    position[6 + i * 6 + 5] = bodies[i]->vz;
  }
  return position;
}