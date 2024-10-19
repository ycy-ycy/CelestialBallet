#include "library.h"

// Constructor definition
camera::camera(double x_0, double y_0, double z_0, double vx_0, double vy_0, double vz_0, 
               double theta_0, double phi_0, double psi_0, 
               double fieldOfView, double aspectRatio, double nearP, double farP)
    : entity(x_0, y_0, z_0, vx_0, vy_0, vz_0, theta_0, phi_0, psi_0)
{
  // Initialize the camera's field of view, aspect ratio, near and far planes
  double fov = fieldOfView;
  double ar = aspectRatio;
  double nearPlane = nearP;
  double farPlane = farP;
}

std::tuple<double, double, double> camera::generateRay(double u, double v) const
{
  // Convert field of view from degrees to radians
  double fovRadians = (fov * M_PI) / 180.0;

  // Compute the direction vectors for the camera
  Vector3D forward = Vector3D(cos(psi) * cos(phi) - cos(theta) * sin(phi) * sin(psi),
                              cos(psi) * sin(phi) + cos(theta) * cos(phi) * sin(psi),
                              sin(psi) * sin(theta)
                             ).normalized();  // Forward direction
  Vector3D left = Vector3D(- sin(psi) * cos(phi) - cos(theta) * sin(phi) * cos(psi),
                           - sin(psi) * sin(phi) + cos(theta) * cos(phi) * cos(psi),
                           cos(psi) * sin(theta)
                          ).normalized();     // Right direction (perpendicular to forward and up)
  Vector3D up = Vector3D(sin(theta) * sin(phi),
                         - sin(theta) * cos(phi),
                         cos(theta)
                        ).normalized();       // Up direction

  // Calculate the image plane dimensions
  double imagePlaneHeight = 2.0 * tan(fovRadians / 2.0); // Height of image plane
  double imagePlaneWidth = imagePlaneHeight * aspect;    // Width depends on aspect ratio

  // Calculate pixel position on the image plane
  Vector3D pixelPos = forward 
                    - left * (u - 0.5) * imagePlaneWidth 
                    + up * (v - 0.5) * imagePlaneHeight;

  // Return normalized ray direction (ray is starting from camera position)
  return pixelPos.normalized().toTuple();
}


std::vector<std::vector<std::tuple<int, int, int>>> camera::rayTrace(int width, int height) const
{
  // TODO: Implement ray tracing for the camera
}