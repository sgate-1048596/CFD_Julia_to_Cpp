
#include <algorithm>
#include <calculate.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

double compute_l2norm(int nx, const vector<double> &r) {
  double rms = 0.0;
  for (int i = 1; i < nx; ++i) { // 对应Python中的range(1, nx)
    rms += pow(r[i], 2);
  }
  return sqrt(rms / (nx - 1));
}

void calculate_fields(const int &nx, const int &nt, const double &x_l,
                      const double &x_r, const double &dx, const double &dt,
                      const double &t_total, const double &alpha,
                      SAVE_DATA &save_data) {
  // 初始条件
  for (int i = 0; i <= nx; ++i) {
    save_data.x[i] = x_l + dx * i;
    save_data.un[0][i] = -sin(M_PI * save_data.x[i]);
    save_data.u_e[i] =
        -exp(-t_total) * sin(M_PI * save_data.x[i]); // 对应t=1.0的精确解
  }

  // 边界条件
  save_data.un[0][0] = 0.0;
  save_data.un[0][nx] = 0.0;

  const double beta = alpha * dt / pow(dx, 2);

  // 时间推进
  for (int k = 1; k <= nt; ++k) {
    for (int i = 1; i < nx; ++i) { // 内部节点更新
      save_data.un[k][i] =
          save_data.un[k - 1][i] +
          beta * (save_data.un[k - 1][i + 1] - 2 * save_data.un[k - 1][i] +
                  save_data.un[k - 1][i - 1]);
    }
    // 应用边界条件
    save_data.un[k][0] = 0.0;
    save_data.un[k][nx] = 0.0;
  }
}
// namespace calculate
