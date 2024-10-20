# include "library.h"

rk45::rk45(int num_eq, double tolerance_abs, double tolerance_rel){
  n_eq = num_eq;
  atol = tolerance_abs;
  rtol = tolerance_rel;

  y_tmp.resize(n_eq);
  y_err.resize(n_eq);
  k1.resize(n_eq);
  k2.resize(n_eq);
  k3.resize(n_eq);
  k4.resize(n_eq);
  k5.resize(n_eq);
  k6.resize(n_eq);
  k7.resize(n_eq);

  r1.resize(n_eq);
  r2.resize(n_eq);
  r3.resize(n_eq);
  r4.resize(n_eq);
  r5.resize(n_eq);
}

std::vector<double> rk45::solve(double t0, double tf, std::vector<double> p0, std::function<std::vector<double>(std::vector<double>)> dpdt)
{
  pf.clear();

  // initial conditions
  h = 0.1; // arbitrary initial step size
  double x = t0;
  std::vector<double> y = p0;
  double err = 1.0;
  // err_prev is for you to implement the more advanced step size control
  double err_prev = 1.0;
  // store k1 which is dydx at the initial condition
  k1 = dpdt(p0);

  double x_prev = x;
  std::vector<double> y_prev = y; // y_prev stores the value of y from the previous step
  std::vector<double> y_next = y; // y_next stores the value of y in the next step
  std::vector<double> y_out(n_eq); // This stores the value for dense output

  while (x <= tf) {
    // Do not update y in place, since there is no guarantee it is accepted
    y_next = step(x, y, dpdt);

    err = error(y_next);
    // If err is fortuitously too small, set it to some lower bound
    err = std::max(err, 1.0e-10);

    // Accept the step if the scalar error is below 1, otherwise reject it and
    // do not move forward
    if (err < 1.0) {
      x_prev = x;
      x += h;
      k1 = k7;
      // store the current error as err_prev
      err_prev = err;
      // Update y_prev and y accordingly
      y_prev = y;
      y = y_next;
    }

    // Adjust h as needed
    double S = 0.9; // safety factor
    if (err_prev < 1.0) {
      // If the previous step was accepted, we can use the step size control
      double err_alpha = 0.7 / 5.0;
      double err_beta = 0.4 / 5.0;
      h = S * h * std::pow(err, -err_alpha) * std::pow(err_prev, err_beta);
    } else {
      // If the previous step was rejected, do not increase the step size
      h = std::min(h, S * h * std::pow(1.0 / err, 0.2));
    }
    h = std::max(h, hmin);
    h = std::min(h, hmax);

    // Uncomment the following line to see the step size and error at each step
    // std::cout << "x = " << x << ", h = " << h << ", err = " << err << std::endl;
  }

  compute_dense_rs(y, y_prev, x - x_prev);
  double th = (tf - x_prev) / (x - x_prev);
  for (int i = 0; i < n_eq; i++) {
    y_out[i] = r1[i] + th * (r2[i] + (1.0 - th) * (r3[i] + th * (r4[i] + (1.0 - th) * r5[i])));
  }


  return y_out;
}

std::vector<double> rk45::step(double t, std::vector<double> &p, std::function<std::vector<double>(std::vector<double>)> dpdt)
{
  // Compute the next step in y, given x and y of the current step
  std::vector<double> y_n(p.size());

  // First step
  for (int i = 0; i < p.size(); i++) {
    y_tmp[i] = p[i] + h * a21 * k1[i];
  }

  // Second step
  k2 = dpdt(y_tmp);
  for (int i = 0; i < p.size(); i++) {
    y_tmp[i] = p[i] + h * (a31 * k1[i] + a32 * k2[i]);
  }

  // Third step
  k3 = dpdt(y_tmp);
  for (int i = 0; i < p.size(); i++) {
    y_tmp[i] = p[i] + h * (a41 * k1[i] + a42 * k2[i] + a43 * k3[i]);
  }

  // Fourth step
  k4 = dpdt(y_tmp);
  for (int i = 0; i < p.size(); i++) {
    y_tmp[i] = p[i] + h * (a51 * k1[i] + a52 * k2[i] + a53 * k3[i] +
                            a54 * k4[i]);
  }

  // Fifth step
  k5 = dpdt(y_tmp);
  for (int i = 0; i < p.size(); i++) {
    y_tmp[i] = p[i] + h * (a61 * k1[i] + a62 * k2[i] + a63 * k3[i] +
                            a64 * k4[i] + a65 * k5[i]);
  }

  // Sixth step
  k6 = dpdt(y_tmp);
  for (int i = 0; i < p.size(); i++) {
    y_n[i] = p[i] + h * (a71 * k1[i] + a72 * k2[i] + a73 * k3[i] +
                            a74 * k4[i] + a75 * k5[i] + a76 * k6[i]);
  }
  k7 = dpdt(y_n);

  // Estimate y_err for each y in the vector using the difference
  // between y1 and y2
  for (int i = 0; i < p.size(); i++) {
    y_err[i] = h * (e1 * k1[i] + e3 * k3[i] + e4 * k4[i] + e5 * k5[i] +
                      e6 * k6[i] + e7 * k7[i]);
  }

  return y_n;
}

double rk45::error(const std::vector<double> &p)
{
  double err = 0.0;
      for (int i = 0; i < n_eq; i++) {
        double scale = atol + std::max(std::abs(p[i]), std::abs(p[i])) * rtol;
        err += std::pow(y_err[i] / scale, 2);
      }
      return std::sqrt(err / n_eq);
}

void rk45::compute_dense_rs(const std::vector<double> &y_next, const std::vector<double> &y, double h)
{
  // Compute the coefficients r1, r2, r3, r4, r5
  for (int i = 0; i < n_eq; i++) {
    r1[i] = y[i];
    r2[i] = y_next[i] - y[i];
    r3[i] = y[i] + h * k1[i] - y_next[i];
    r4[i] = 2.0 * (y_next[i] - y[i]) - h * (k1[i] + k7[i]);
    r5[i] = h * (d1 * k1[i] + d3 * k3[i] + d4 * k4[i] + d5 * k5[i] +
                  d6 * k6[i] + d7 * k7[i]);
  }
}

// const double rk45::c2 = 1.0 / 5.0;
// const double rk45::c3 = 3.0 / 10.0;
// const double rk45::c4 = 4.0 / 5.0;
// const double rk45::c5 = 8.0 / 9.0;

// We impose a minimum and maximum step size
const double rk45::hmin = 1.0e-10;
const double rk45::hmax = 1.0;

const double rk45::a21 = 1.0 / 5.0;
const double rk45::a31 = 3.0 / 40.0;
const double rk45::a32 = 9.0 / 40.0;
const double rk45::a41 = 44.0 / 45.0;
const double rk45::a42 = -56.0 / 15.0;
const double rk45::a43 = 32.0 / 9.0;
const double rk45::a51 = 19372.0 / 6561.0;
const double rk45::a52 = -25360.0 / 2187.0;
const double rk45::a53 = 64448.0 / 6561.0;
const double rk45::a54 = -212.0 / 729.0;
const double rk45::a61 = 9017.0 / 3168.0;
const double rk45::a62 = -355.0 / 33.0;
const double rk45::a63 = 46732.0 / 5247.0;
const double rk45::a64 = 49.0 / 176.0;
const double rk45::a65 = -5103.0 / 18656.0;

// Note that a71, a72, a73, a74, a75, a76 are essentially the coefficients of the 5th order solution
const double rk45::a71 = 35.0 / 384.0;
const double rk45::a72 = 0.0;
const double rk45::a73 = 500.0 / 1113.0;
const double rk45::a74 = 125.0 / 192.0;
const double rk45::a75 = -2187.0 / 6784.0;
const double rk45::a76 = 11.0 / 84.0;

// These coefficients are used to estimate the error in the solution. They are essentially
// the coefficients of the 5th order solution minus the 4th order solution, i.e. b_i - b_i^*.
const double rk45::e1 = 71.0 / 57600.0;
const double rk45::e2 = 0.0;
const double rk45::e3 = -71.0 / 16695.0;
const double rk45::e4 = 71.0 / 1920.0;
const double rk45::e5 = -17253.0 / 339200.0;
const double rk45::e6 = 22.0 / 525.0;
const double rk45::e7 = -1.0 / 40.0;

// These are the coefficients for dense output
const double rk45::d1 = -12715105075.0 / 11282082432.0;
const double rk45::d2 = 0.0;
const double rk45::d3 = 87487479700.0 / 32700410799.0;
const double rk45::d4 = -10690763975.0 / 1880347072.0;
const double rk45::d5 = 701980252875.0 / 199316789632.0;
const double rk45::d6 = -1453857185.0 / 822651844.0;
const double rk45::d7 = 69997945.0 / 29380423.0;

