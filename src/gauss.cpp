#include <gauss.hpp>
#include <iostream>
#include <random>

// Basic tests

std::vector<std::vector<float>>
gaussian_distribution_2d(float mean, float std_deviat, size_t N) {
  std::random_device rd;
  std::mt19937 gen(rd());

  int i;
  std::vector<std::vector<float>> samples;
  samples.reserve(N);
  for (i = 0; i < N; ++i) {
    std::normal_distribution<float> d(mean, std_deviat);

    std::vector<float> sample{d(gen), d(gen)};
    samples.push_back(sample);
  }

  // for (const auto &sample : samples)
  // {
  //   std::cout << sample[0] << " | " << sample[1] << "\n";
  // }

  return samples;
}