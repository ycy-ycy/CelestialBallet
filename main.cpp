#include "library.h"

int main(){
  setBoundaries(150.0);
  camera* cam = new camera(-100.0,-0.0,0.0,-0.2,0.1,0.0,0.0,0.0,0.0,20.0,1.0);
  std::vector<celestialBody*> bodies;
  bodies.push_back(new star(1000.0,1.0,1.0,6300.0,1.0,0.0,4.0,0.0,0.0,0.0,-8.0,0.0,0.0,0.0));
  bodies.push_back(new star(1000.0,1.0,1.0,2000.0,1.0,0.0,-4.0,0.0,0.0,0.0,8.0,0.0,0.0,0.0));
  for (int i=0;i<121;i++){
    cam->takePhoto(bodies,"test/" + std::to_string(i) + ".dat",600,8);
    updateAll(cam, bodies, 1.0/30.0);
  }
  return 0;
}