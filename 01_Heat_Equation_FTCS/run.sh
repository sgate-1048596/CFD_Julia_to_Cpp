#!/bin/bash
if [ -e "build" ]; then
  echo "存在build目录"
  rm -rf build
else
  touch build
fi
cmake -B build
cd build
make
./main_program

# 对比图（实线+虚线）
gnuplot <<PLOT
set terminal pngcairo enhanced font "arial,12" size 1280,720
set output "solution_comparison.png"
set title "Heat Equation Solution (t=1.0)"
set xlabel "x coordinate"
set ylabel "u value"
set grid
set key left

# 精确解用实线（lw 3），数值解用虚线（dashtype 2）
plot "field_final.csv" using 1:2 with lines lw 3 lt rgb "navy" title "Exact solution", \
     "" using 1:3 with lines lw 3 lt rgb "coral" dashtype 2 title "Numerical solution"
PLOT

# 误差图（加粗实线）
gnuplot <<PLOT
set terminal pngcairo enhanced font "arial,12" size 1280,720
set output "error_distribution.png"
set title "Numerical Error Distribution"
set xlabel "x coordinate"
set ylabel "Error"
set grid
set key right

# 误差线使用加粗红色实线
plot "field_final.csv" using 1:4 with lines lw 2.5 lt rgb "red" title "Error"
PLOT
echo " 打开comparison.png 和 error.png 查看结果"
