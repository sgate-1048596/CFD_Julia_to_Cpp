#pragma once
#include "calculate.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Err {
  vector<double> u_error;
  double rms_error;
  double max_error;
  Err(int nx) : u_error(nx + 1) {}
};

void cal_field_error(const int &nx, const int &nt, const SAVE_DATA &save_data,
                     Err &err);
// namespace calculate
