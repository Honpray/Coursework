#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights,
                         vector<int> values) {
  double value = 0.0;
  // write your code here
  int n = weights.size();
  double ratio[n];
  for (int i = 0; i < n; i++) {
    ratio[i] = values[i] / (double)weights[i];
  }
  while (capacity > 0) {
    int max_idx = std::distance(ratio, std::max_element(ratio, ratio + n));
    value += std::min(weights[max_idx], capacity) * ratio[max_idx];
    capacity -= std::min(weights[max_idx], capacity);
    ratio[max_idx] = 0;
  }
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);
  std::cout.setf(std::ios::fixed);
  std::cout.setf(std::ios::showpoint);
  std::cout.precision(4);
  std::cout << optimal_value << std::endl;
  return 0;
}
