#include "library.h"

int main(){
  setBoundaries(20.0);
  camera* cam = new camera(-10.0,-0.0,0.0,-0.2,0.1,0.0,0.0,0.0,0.0,15.0,1.0);
  std::vector<celestialBody*> bodies;
  bodies.push_back(new star(1.0,1.0,1.0,2000.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0));
  for (int i=0;i<121;i++){
    cam->takePhoto(bodies,"test/" + std::to_string(i) + ".dat",400,8);
    updateAll(cam, bodies, 1.0/60.0);
  }
  return 0;
}