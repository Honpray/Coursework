#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

int binary_search_recursive(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size();
  // write your code here
  if (right >= 1) {  // Error point SIGSEGV
    int mid = (left + right) / 2;
    if (a[mid] == x) return mid;
    if (x < a[mid]) {
      std::vector<int> half(a.begin(), a.begin() + mid);
      return binary_search_recursive(half, x);
    }
    if (x > a[mid]) {
      std::vector<int> half(a.begin() + mid + 1, a.end());
      // mid + 1
      // SIGSEGV while right = 0 to build a vector of no element
      // also element in range of [first, last) are copied
      return binary_search_recursive(half, x);
    }
  }
  return -1;
}

int binary_search_iterative(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size();
  // write your code here
  while (left <= right) {
    int mid = (left + right) / 2;
    if (a[mid] == x)
      return mid;
    else if (a[mid] < x)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    // std::cout << linear_search(a, b[i]) << ' ';
    std::cout << binary_search_recursive(a, b[i]) << ' ';
    std::cout << binary_search_iterative(a, b[i]) << ' ';
    // 2 2 0 0 -1 -1 0 0 -1 -1
  }
}
