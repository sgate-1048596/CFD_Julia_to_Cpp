#include "calculate/include/cal_error.h"
#include "calculate/include/calculate.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  // 参数设置
  const double x_l = -1.0;
  const double x_r = 1.0;
  const double dx = 0.025;
  const int nx = static_cast<int>((x_r - x_l) / dx);

  const double dt = 0.0025;
  const double t_total = 1.0;
  const int nt = static_cast<int>(t_total / dt);

  const double alpha = 1.0 / (M_PI * M_PI);

  SAVE_DATA save_data(nx, nt);
  Err err(nx);
  calculate_fields(nx, nt, x_l, x_r, dx, dt, t_total, alpha, save_data);
  cal_field_error(nx, nt, save_data, err);
  // 写入误差文件
  ofstream out_file("output.txt");
  out_file << "Error details:\n";
  out_file << "L-2 Norm = " << scientific << setprecision(16) << err.rms_error
           << "\n";
  out_file << "Maximum Norm = " << scientific << setprecision(16)
           << err.max_error << "\n";
  out_file.close();

  // 写入最终场数据
  ofstream field_file("field_final.csv");
  field_file << "x ue un uerror\n";
  for (int i = 0; i <= nx; ++i) {
    field_file << fixed << setprecision(16) << save_data.x[i] << " "
               << save_data.u_e[i] << " " << save_data.un[nt][i] << " "
               << err.u_error[i] << "\n";
  }
  field_file.close();

  return 0;
}
