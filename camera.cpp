#include "library.h"

// Constructor definition
camera::camera(double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, 
               double theta_0, double phi_0, double psi_0, 
               double fieldOfView, double aspectRatio)
    : entity(x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0)
{
  // Initialize the camera's field of view, aspect ratio, near and far planes
  double fov = fieldOfView;
  double ar = aspectRatio;
}

std::tuple<double, double, double> camera::generateRay(double u, double v) const
{
  // Convert field of view from degrees to radians
  double fovRadians = (fov * PI) / 180.0;

  // Compute the direction vectors for the camera
  Vector3D forward = Vector3D(std::cos(psi) * std::cos(phi) - std::cos(theta) * std::sin(phi) * std::sin(psi),
                              std::cos(psi) * std::sin(phi) + std::cos(theta) * std::cos(phi) * std::sin(psi),
                              std::sin(psi) * std::sin(theta)
                             ).normalized();  // Forward direction
  Vector3D left = Vector3D(- std::sin(psi) * std::cos(phi) - std::cos(theta) * std::sin(phi) * std::cos(psi),
                           - std::sin(psi) * std::sin(phi) + std::cos(theta) * std::cos(phi) * std::cos(psi),
                           std::cos(psi) * std::sin(theta)
                          ).normalized();     // Right direction (perpendicular to forward and up)
  Vector3D up = Vector3D(std::sin(theta) * std::sin(phi),
                         - std::sin(theta) * std::cos(phi),
                         std::cos(theta)
                        ).normalized();       // Up direction

  // Calculate the image plane dimensions
  double imagePlaneHeight = 2.0 * std::tan(fovRadians / 2.0); // Height of image plane
  double imagePlaneWidth = imagePlaneHeight * aspect;    // Width depends on aspect ratio

  // Calculate pixel position on the image plane
  Vector3D pixelPos = forward 
                    - left * (u - 0.5) * imagePlaneWidth 
                    + up * (v - 0.5) * imagePlaneHeight;

  // Return normalized ray direction (ray is starting from camera position)
  return pixelPos.normalized().toTuple();
}


std::tuple<int, int, int> camera::rayTrace(double u, double v, const std::vector<celestialBody*> &bodies) const
{
  std::tuple<double, double, double> direction = generateRay(u, v);
  ray traced(x, y, z, std::get<0>(direction), std::get<1>(direction), std::get<2>(direction), bodies);
  return traced.color();
}