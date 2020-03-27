#pragma once
#include <hist.hpp>

void add_2d_point(float X, float Y, Histogram &hist);
Histogram get_2d_hist(float Xmin, float Xmax, float Ymin, float Ymax,
                      int Xbins_num, int Ybins_num);
void test_2d_hist();
void test_outside_the_limits();
void print_flat_2d_hist(Histogram &hist);