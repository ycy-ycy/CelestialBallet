#include "library.h"

double getNoise(FastNoiseLite* noise, double theta, double phi){
  float x = std::sin(theta) * std::cos(phi);
  float y = std::sin(theta) * std::sin(phi);
  float z = std::cos(theta);
  return (double)noise->GetNoise(x, y, z);
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distribution(
  std::numeric_limits<int>::min(), 
  std::numeric_limits<int>::max()
);

int randomSeed(){
  return distribution(gen);
}