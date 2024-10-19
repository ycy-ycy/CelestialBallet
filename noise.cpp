#include "library.h"

float getNoise(FastNoiseLite* noise, double theta, double phi){
  float x = std::sin(theta) * std::cos(phi);
  float y = std::sin(theta) * std::sin(phi);
  float z = std::cos(theta);
  return noise->GetNoise(x, y, z);
}