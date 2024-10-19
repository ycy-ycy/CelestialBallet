#include "library.h"

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalized() const {
  double len = length();
  if (len == 0) return Vector3D(0, 0, 0); // Prevent division by zero
  return Vector3D(x / len, y / len, z / len);
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
  return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
  return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator*(double scalar) const {
  return Vector3D(x * scalar, y * scalar, z * scalar);
}

double Vector3D::dot(const Vector3D& v) const {
  return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::cross(const Vector3D& v) const {
  return Vector3D(
      y * v.z - z * v.y,
      z * v.x - x * v.z,
      x * v.y - y * v.x
  );
}

std::tuple<double, double, double> Vector3D::toTuple() const {
  return std::make_tuple(x, y, z);
}

void Vector3D::print() const {
  std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}