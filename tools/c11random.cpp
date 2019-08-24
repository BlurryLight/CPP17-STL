#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

int main() {
  std::random_device sed;
  std::default_random_engine rd(sed());
  //正态分布
  std::normal_distribution<> normal_dist(10, 2); //μ and \theta

  std::map<int, int> index_dist;
  for (int n = 0; n < 100000; ++n) {
    index_dist[std::round(normal_dist(rd))]++;
  }

  for (auto p : index_dist) {
    std::cout << std::fixed << std::setprecision(1) << std::setw(2) << p.first
              << ' ' << std::string(p.second / 200, '*') << '\n';
  }
  return 0;
}
