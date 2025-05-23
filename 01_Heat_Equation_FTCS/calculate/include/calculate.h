#pragma once

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

double compute_l2norm(int nx, const vector<double> &r);

struct SAVE_DATA {
  vector<double> x;
  vector<double> u_e;
  vector<vector<double>> un;

  SAVE_DATA(int nx, int nt)
      : x(nx + 1), u_e(nx + 1), un(nt + 1, vector<double>(nx + 1, 0.0)) {};
};

void calculate_fields(const int &nx, const int &nt, const double &x_l,
                      const double &x_r, const double &dx, const double &dt,
                      const double &t_total, const double &alpha,
                      SAVE_DATA &save_data);

// namespace calculate
