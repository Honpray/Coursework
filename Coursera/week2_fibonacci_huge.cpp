#include <iostream>
#include <vector>
long long get_fibonacci_huge_naive(long long n, long long m) {
  if (n <= 1) return n;

  long long previous = 0;
  long long current = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
  }

  return current % m;
}

int64_t get_fibonacci_huge_fast(int64_t n, int64_t m) {
  int size = 0;
  std::vector<int> v_r = {0, 1, 1}, v_fib = {0, 1, 1};

  while (!(v_r.end()[-2] == 0 && v_r.end()[-1] == 1)) {
    v_fib.emplace_back(v_r.end()[-2] + v_r.end()[-1]);
    v_r.emplace_back(v_fib.back() % m);
    size++;
  }
  return v_r[n % (size + 1)];  // don't forget the +1 since your way of initialization
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
  std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
