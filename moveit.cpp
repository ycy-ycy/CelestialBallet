#include "library.h"

void rotateAll(const std::vector<celestialBody*> &bodies, double delta_t){
  for (celestialBody* body : bodies){
    body->psi += body->w * delta_t;
  }
}

void updateAll(camera* cam, const std::vector<celestialBody*> &bodies, double delta_t){
  std::function<std::vector<double>(std::vector<double>)> motion_eq = gravity(cam, bodies);
  std::vector<double> p0 = getPosition(cam, bodies);
  rk45 solver(6+6*bodies.size(), 1e-8, 1e-8);
  std::vector<double> p_f = solver.solve(0, delta_t, p0, motion_eq);
  updatePosition(cam, bodies, p_f);
}