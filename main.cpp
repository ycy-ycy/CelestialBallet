#include "library.h"

int main(){
  camera* cam = new camera(-10.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,10.0,1.0);
  std::vector<celestialBody*> bodies;
  bodies.push_back(new star(1.0,1.0,1.0,2000.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0));
  cam->takePhoto(bodies,"test/photo.dat",400,8);
  return 0;
}