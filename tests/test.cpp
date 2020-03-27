#include <cassert>
#include <hist.hpp>
#include <iostream>
#include <test.hpp>
#include <vector>

void add_2d_point(float X, float Y, Histogram &hist) {
  std::vector<float> point;
  point.push_back(X);
  point.push_back(Y);
  hist.fill(point);
}

Histogram get_2d_hist(float Xmin, float Xmax, float Ymin, float Ymax,
                      int Xbins_num, int Ybins_num) {
  std::vector<size_t> bins_nums;
  std::vector<std::pair<float, float>> limits;

  bins_nums.push_back(Xbins_num);
  bins_nums.push_back(Ybins_num);
  limits.push_back(std::pair<float, float>(Xmin, Xmax));
  limits.push_back(std::pair<float, float>(Ymin, Ymax));

  auto hist = Histogram(bins_nums, limits);
  return hist;
}

void test_2d_hist() {
  auto hist = get_2d_hist(0, 10, 0, 10, 10, 10);
  add_2d_point(3, 4, hist);
  add_2d_point(0.1, 0.1, hist);
  print_flat_2d_hist(hist);
}

void print_flat_2d_hist(Histogram &hist) {
  size_t i = 1;
  auto dimensions = hist.dims_bin_num();
  auto width = dimensions[1];
  for (const auto &col : hist.get_hist()) {
    std::cout << col << " | ";
    if (i++ % width == 0)
      std::cout << "\n";
  }
  std::cout << i;
  std::cout << "\n";
}

void test_outside_the_limits() {
  auto hist = get_2d_hist(0, 10, 0, 10, 10, 10);
  const auto clean_hist = hist.get_hist();
  add_2d_point(11, 11, hist);
  add_2d_point(-1, -1, hist);
  print_flat_2d_hist(hist);
  assert(clean_hist == hist.get_hist());
}
