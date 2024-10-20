#include "library.h"

celestialBody::celestialBody(double mass, double radius, double omega, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0) : entity(x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0){
  M = mass;
  r = radius;
  w = omega;
  fluctuation_R = 0.0;
}

std::tuple<double,double> celestialBody::getAngles(double x_r, double y_r, double z_r){
  double delta_x = x_r - x;
  double delta_y = y_r - y;
  double delta_z = z_r - z;
  Vector3D delta = Vector3D(delta_x, delta_y, delta_z).normalized();
  Vector3D xHat = Vector3D(std::cos(psi) * std::cos(phi) - std::cos(theta) * std::sin(phi) * std::sin(psi),
                              std::cos(psi) * std::sin(phi) + std::cos(theta) * std::cos(phi) * std::sin(psi),
                              std::sin(psi) * std::sin(theta)
                             ).normalized();
  Vector3D yHat = Vector3D(- std::sin(psi) * std::cos(phi) - std::cos(theta) * std::sin(phi) * std::cos(psi),
                           - std::sin(psi) * std::sin(phi) + std::cos(theta) * std::cos(phi) * std::cos(psi),
                           std::cos(psi) * std::sin(theta)
                          ).normalized();
  Vector3D zHat = Vector3D(std::sin(theta) * std::sin(phi),
                         - std::sin(theta) * std::cos(phi),
                         std::cos(theta)
                        ).normalized();
  double z_comp = delta.dot(zHat);
  double y_comp = delta.dot(yHat);
  double x_comp = delta.dot(xHat);
  double theta_out = std::acos(z_comp);
  double phi_out;
  if (std::abs(x_comp) <= 1e-10){
    if (y_comp > 1e-10) {phi_out = PI/2.0;}
    else if (y_comp < -1e-10) {phi_out = -PI/2.0;}
    else {phi_out = 0.0;}
  }
  else if (x_comp > 0.0){
    phi_out = std::atan(y_comp/x_comp);
  }
  else{
    phi_out = std::atan(y_comp/x_comp) + PI;
  }
  return std::make_tuple(theta_out, phi_out);
}

double celestialBody::radius(double theta, double phi){
  return r;
}

std::function<double(double)> celestialBody::rayDistance(ray* photon){
  double x_s = x;
  double y_s = y;
  double z_s = z;
  double x_r = photon->x;
  double y_r = photon->y;
  double z_r = photon->z;
  double vx_r = photon->vx;
  double vy_r = photon->vy;
  double vz_r = photon->vz;
  double r_s = r;
  std::function<double(double)> f = [x_s, y_s, z_s, x_r, y_r, z_r, vx_r, vy_r, vz_r, r_s] (double x_p) -> double {
    double delta_x = x_s - x_p * vx_r - x_r;
    double delta_y = y_s - x_p * vy_r - y_r;
    double delta_z = z_s - x_p * vz_r - z_r;
    return r_s - std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
  };
  return f;
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

std::tuple<int,int,int> star::color(double theta, double phi, double intensity){
  intensity *= (I + fluctuation_I * getNoise(&noise_I, theta, phi));
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
  r += fluctuation_R * getNoise(&noise_r, theta, phi);
  g += fluctuation_g * getNoise(&noise_g, theta, phi);
  b += fluctuation_b * getNoise(&noise_b, theta, phi);
  int r_out = std::clamp(static_cast<int>(std::round(r * intensity)),0,255);
  int g_out = std::clamp(static_cast<int>(std::round(g * intensity)),0,255);
  int b_out = std::clamp(static_cast<int>(std::round(b * intensity)),0,255);
  return std::make_tuple(r_out, g_out, b_out);
}

double star::radius(double theta, double phi){
  return r + fluctuation_R * getNoise(&noise_R, theta, phi);
}

std::function<double(double)> star::rayDistance(ray* photon){
  // TODO : add angle dependence radius
  double x_s = x;
  double y_s = y;
  double z_s = z;
  double x_r = photon->x;
  double y_r = photon->y;
  double z_r = photon->z;
  double vx_r = photon->vx;
  double vy_r = photon->vy;
  double vz_r = photon->vz;
  double r_s = r;
  std::function<double(double)> f = [x_s, y_s, z_s, x_r, y_r, z_r, vx_r, vy_r, vz_r, r_s] (double x_p) -> double {
    double delta_x = x_s - x_p * vx_r - x_r;
    double delta_y = y_s - x_p * vy_r - y_r;
    double delta_z = z_s - x_p * vz_r - z_r;
    return r_s - std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
  };
  return f;
}

planet::planet(double mass, double radius, double omega, double reflection, double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, double theta_0, double phi_0, double psi_0, double fluctuation_reflection) : celestialBody(mass, radius, omega, x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0){
  rf = reflection;
  fluctuation_r = fluctuation_reflection;
  noise_r.SetSeed(randomSeed());
  noise_r.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
}

double planet::radius(double theta, double phi){
  return r;
}

std::function<double(double)> planet::rayDistance(ray* photon){
  double x_s = x;
  double y_s = y;
  double z_s = z;
  double x_r = photon->x;
  double y_r = photon->y;
  double z_r = photon->z;
  double vx_r = photon->vx;
  double vy_r = photon->vy;
  double vz_r = photon->vz;
  double r_s = r;
  std::function<double(double)> f = [x_s, y_s, z_s, x_r, y_r, z_r, vx_r, vy_r, vz_r, r_s] (double x_p) -> double {
    double delta_x = x_s - x_p * vx_r - x_r;
    double delta_y = y_s - x_p * vy_r - y_r;
    double delta_z = z_s - x_p * vz_r - z_r;
    return r_s - std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
  };
  return f;
}

double planet::getReflection(double theta, double phi){
  return rf + fluctuation_r * getNoise(&noise_r, theta, phi);
}

void planet::reflect(ray* photon, double theta, double phi){
  double delta_x = photon->x - x;
  double delta_y = photon->y - y;
  double delta_z = photon->z - z;
  Vector3D delta = Vector3D(delta_x, delta_y, delta_z).normalized();
  Vector3D incident = Vector3D(photon->vx, photon->vy, photon->vz).normalized();
  double dot = delta.dot(incident);
  photon->vx = -2.0 * dot * delta.x + incident.x;
  photon->vy = -2.0 * dot * delta.y + incident.y;
  photon->vz = -2.0 * dot * delta.z + incident.z;
  photon->I *= getReflection(theta, phi);
  photon->x += photon->vx * r;
}