#pragma once
#include <vector>

class Axis {
public:
  Axis(float bin_size, size_t bins_num, float left, float right);

  Axis(std::vector<float> edges);

  int get_bin_idx(float coord);

  int bin_count();
  auto const min();
  auto const max();

private:
  std::vector<float> edges;
};

class Histogram {
public:
  // Custom bins sizes
  Histogram(std::vector<std::vector<float>> edges);
  // Equal bins sizes
  Histogram(std::vector<size_t> bins_nums,
            std::vector<std::pair<float, float>> limits);

  size_t dims_num();
  std::vector<size_t> dims_bin_num();
  void fill(std::vector<float> coords);
  std::vector<int> get_hist();
  std::vector<std::pair<float, float>> get_limits();

private:
  size_t flatten_index(std::vector<int> index);

  std::vector<Axis> axis;
  std::vector<int> flat_hist;
  std::vector<std::pair<float, float>> limits;
};
