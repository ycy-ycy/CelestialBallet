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

void updatePosition(camera* cam, const std::vector<celestialBody*> &bodies, const std::vector<double> &p){
  cam->x = p[0];
  cam->y = p[1];
  cam->z = p[2];
  cam->vx = p[3];
  cam->vy = p[4];
  cam->vz = p[5];
  for(int i = 0; i < bodies.size(); i++){
    bodies[i]->x = p[6 + i * 6];
    bodies[i]->y = p[7 + i * 6];
    bodies[i]->z = p[8 + i * 6];
    bodies[i]->vx = p[9 + i * 6];
    bodies[i]->vy = p[10 + i * 6];
    bodies[i]->vz = p[11 + i * 6];
  }
}