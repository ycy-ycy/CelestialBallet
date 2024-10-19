#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>

class rk45{
public:
  rk45(int num_eq);
  
  std::vector<double> solve(double t0, double tf, std::vector<double> p0, std::function<std::vector<double>(std::vector<double>)> dpdt);
};

#endif