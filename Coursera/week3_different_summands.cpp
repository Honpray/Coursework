#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  // write your code here
  if (n <= 3) {
    summands.emplace_back(n);
  } else if (n > 3 && n < 6) {
    summands.emplace_back(1);
    summands.emplace_back(n - 1);
  } else {
    summands.emplace_back(1);
    summands.emplace_back(2);
    summands.emplace_back(n - 3);
  }
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
