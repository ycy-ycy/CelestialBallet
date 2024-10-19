#include "library.h"

std::function<std::vector<double>(std::vector<double>)> gravity(camera* cam, const std::vector<celestialBody*> &bodies){

  std::function<std::vector<double>(std::vector<double>)> f = [bodies] (std::vector<double> p) -> std::vector<double> {

    std::vector<double> result(p.size());

    // motion of the camera
    result[0] = p[3];
    result[1] = p[4];
    result[2] = p[5];
    result[3] = 0.0;
    result[4] = 0.0;
    result[5] = 0.0;

    // motion of celestial bodies
    #pragma omp parallel for num_threads(8)
    for (int i = 0; i < bodies.size(); i++){
      result[6+6*i] = p[9+6*i];
      result[7+6*i] = p[10+6*i];
      result[8+6*i] = p[11+6*i];
      double ax = 0.0, ay = 0.0, az = 0.0;
      for (int j = 0; j < bodies.size(); j++){
        if (i==j) {continue;}
        double x = p[6+6*j] - p[6+6*i];
        double y = p[7+6*j] - p[7+6*i];
        double z = p[8+6*j] - p[8+6*i];
        double r = std::sqrt(x*x + y*y + z*z);
        double M = bodies[j]->M;
        ax += M*x/r/r/r;
        ay += M*y/r/r/r;
        az += M*z/r/r/r;
      }
      result[9+6*i] = ax;
      result[10+6*i] = ay;
      result[11+6*i] = az;
    }

    return result;

  };

  return f;
}