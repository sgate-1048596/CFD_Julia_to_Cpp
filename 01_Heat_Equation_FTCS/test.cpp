#include <algorithm>
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

  // 初始化数组
  vector<double> x(nx + 1);
  vector<double> u_e(nx + 1);
  vector<vector<double>> un(nt + 1,
                            vector<double>(nx + 1, 0.0)); // 时间步从0到nt

  // 初始条件
  for (int i = 0; i <= nx; ++i) {
    x[i] = x_l + dx * i;
    un[0][i] = -sin(M_PI * x[i]);
    u_e[i] = -exp(-t_total) * sin(M_PI * x[i]); // 对应t=1.0的精确解
  }

  // 边界条件
  un[0][0] = 0.0;
  un[0][nx] = 0.0;

  const double beta = alpha * dt / pow(dx, 2);

  // 时间推进
  for (int k = 1; k <= nt; ++k) {
    for (int i = 1; i < nx; ++i) { // 内部节点更新
      un[k][i] = un[k - 1][i] + beta * (un[k - 1][i + 1] - 2 * un[k - 1][i] +
                                        un[k - 1][i - 1]);
    }
    // 应用边界条件
    un[k][0] = 0.0;
    un[k][nx] = 0.0;
  }

  // 计算误差
  vector<double> u_error(nx + 1);
  for (int i = 0; i <= nx; ++i) {
    u_error[i] = un[nt][i] - u_e[i];
  }
  double rms_error = compute_l2norm(nx, u_error);
  double max_error =
      *max_element(u_error.begin(), u_error.end(),
                   [](double a, double b) { return abs(a) < abs(b); });
  max_error = abs(max_error);

  // 写入误差文件
  ofstream out_file("output.txt");
  out_file << "Error details:\n";
  out_file << "L-2 Norm = " << scientific << setprecision(16) << rms_error
           << "\n";
  out_file << "Maximum Norm = " << scientific << setprecision(16) << max_error
           << "\n";
  out_file.close();

  // 写入最终场数据
  ofstream field_file("field_final.csv");
  field_file << "x ue un uerror\n";
  for (int i = 0; i <= nx; ++i) {
    field_file << fixed << setprecision(16) << x[i] << " " << u_e[i] << " "
               << un[nt][i] << " " << u_error[i] << "\n";
  }
  field_file.close();

  return 0;
}
