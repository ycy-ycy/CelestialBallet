#include "library.h"

celestialBody::celestialBody(double mass, double radius, double omega, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0) : entity(x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0){
  M = mass;
  r = radius;
  w = omega;
}

star::star(double mass, double radius, double omega, double temperature, double intensity, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0, double fluctuation_intensity, double fluctuation_radius, double fluctuation_r, double fluctuation_g, double fluctuation_b) : celestialBody(mass, radius, omega, x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0){
  T = temperature;
  I = intensity;
  fluctuation_I = fluctuation_intensity;
  fluctuation_R = fluctuation_radius;
  fluctuation_r = fluctuation_r;
  fluctuation_g = fluctuation_g;
  fluctuation_b = fluctuation_b;
  noise_I.SetSeed(randomSeed());
  noise_R.SetSeed(randomSeed());
  noise_r.SetSeed(randomSeed());
  noise_g.SetSeed(randomSeed());
  noise_b.SetSeed(randomSeed());
  noise_I.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  noise_R.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  noise_r.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  noise_g.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  noise_b.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
}

std::tuple<int,int,int> star::color(double theta, double phi){
  double intensity = I + fluctuation_I * noise_I.GetNoise(theta, phi);
  double r,g,b;

  if (T<1000.0){ // red
    r = 255.0;
    g = 0.0;
    b = 0.0;
  }
  else if (T<4000.0){ // yellow
    double t = (T-1000.0)/3000.0;
    r = 255.0;
    g = 192.0 * t;
    b = 64.0 * t;
  }
  else if (T<7000.0){ // blue
    double t = (T-4000.0)/3000.0;
    r = 255.0 * (1.0-t);
    g = 192.0 - 64.0 * t;
    b = 255.0 * t;
  }
  else if (T<8800.0){
    double t = (T-7000.0)/1800.0;
    r = 255.0 * t;
    g = 128.0 + 127.0 * t;
    b = 255.0;
  }
  else{ // white
    r = 255.0;
    g = 255.0;
    b = 255.0;
  }
  r += fluctuation_R * noise_R.GetNoise(theta, phi);
  g += fluctuation_g * noise_g.GetNoise(theta, phi);
  b += fluctuation_b * noise_b.GetNoise(theta, phi);
  int r_out = std::clamp(static_cast<int>(std::round(r * intensity)),0,255);
  int g_out = std::clamp(static_cast<int>(std::round(g * intensity)),0,255);
  int b_out = std::clamp(static_cast<int>(std::round(b * intensity)),0,255);
  return std::make_tuple(r_out, g_out, b_out);
}