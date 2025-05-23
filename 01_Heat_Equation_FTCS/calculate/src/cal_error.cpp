

#include <algorithm>
#include <cal_error.h>
#include <calculate.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// 计算误差
void cal_field_error(const int &nx, const int &nt, const SAVE_DATA &save_data,
                     Err &err) {
  for (int i = 0; i <= nx; ++i) {
    err.u_error[i] = save_data.un[nt][i] - save_data.u_e[i];
  }
  err.rms_error = compute_l2norm(nx, err.u_error);
  err.max_error =
      *max_element(err.u_error.begin(), err.u_error.end(),
                   [](double a, double b) { return abs(a) < abs(b); });
  err.max_error = abs(err.max_error);
}
// namespace calculate
