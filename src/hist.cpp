#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <hist.hpp>
#include <iostream>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

Axis::Axis(float bin_size, size_t bins_num, float left, float right) {
  edges.resize(bins_num + 1);
  float cur = left;
  for (auto &edge : edges) {
    edge = cur;
    cur += bin_size;
  }
  edges[edges.size() - 1] = right;
}

Axis::Axis(std::vector<float> edges) : edges(edges) {}

int Axis::get_bin_idx(float coord) {
  auto it = std::upper_bound(edges.begin(), edges.end(), coord);
  if (coord < edges.front() || !(it != edges.end())) {
    return -1;
  }
  size_t idx = it - edges.begin();
  return --idx;
}

int Axis::bin_count() { return edges.size() - 1; }
auto const Axis::min() { return edges.front(); }
auto const Axis::max() { return edges.back(); }

// Custom bins sizes
Histogram::Histogram(std::vector<std::vector<float>> edges) {
  // Assert if not sorted
  for (const auto &dimension_edges : edges) {
    axis.push_back(Axis(dimension_edges));
  }

  int flat_size = 1;
  for (const auto &edge : edges) {
    flat_size *= edge.size();
  }
  flat_hist.resize(flat_size);
}
// Equal bins sizes
Histogram::Histogram(std::vector<size_t> bins_nums,
                     std::vector<std::pair<float, float>> limits)
    : limits(limits) {
  assert(("Dimensions must be equal", bins_nums.size() == limits.size()));

  for (size_t i = 0; i < bins_nums.size(); i++) {
    auto limit = limits[i];
    auto bins_num = bins_nums[i];
    auto bin_size = (limit.second - limit.first) / bins_num;

    axis.push_back(Axis(bin_size, bins_num, limit.first, limit.second));
  }

  int flat_size = 1;
  flat_size = std::accumulate(bins_nums.begin(), bins_nums.end(), flat_size,
                              std::multiplies<int>());
  flat_hist.resize(flat_size);
}

size_t Histogram::dims_num() { return axis.size(); }

// Amount of bins in each dimension
std::vector<size_t> Histogram::dims_bin_num() {
  std::vector<size_t> dims;
  for (Axis &ax : axis) {
    dims.push_back(ax.bin_count());
  }
  return dims;
}

void Histogram::fill(std::vector<float> coords) {
  assert(("Dimensions must be equal", coords.size() == axis.size()));

  std::vector<int> index;
  index.reserve(dims_num());

  size_t i = 0;
  for (Axis &ax : axis) {
    auto bin_idx = ax.get_bin_idx(coords[i++]);
    if (bin_idx == -1)
      return;
    index.push_back(bin_idx);
  }

  flat_hist[flatten_index(index)] += 1;
}

size_t Histogram::flatten_index(std::vector<int> index) {
  size_t idx;
  auto dims_bin_count = dims_bin_num();

  idx = index.front();
  for (size_t i = 1; i < dims_bin_count.size(); i++) {
    idx *= dims_bin_count[i];
    idx += index[i];
  }

  return idx;
}

std::vector<int> Histogram::get_hist() { return flat_hist; }
std::vector<std::pair<float, float>> Histogram::get_limits() { return limits; }
