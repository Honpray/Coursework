#include <iostream>

int fibonacci_sum_naive(long long n) {
  if (n <= 1) return n;

  long long previous = 0;
  long long current = 1;
  long long sum = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
    sum += current;
  }

  return sum % 10;
}

int fibonacci_sum_fast(int64_t n) {
  if (n <= 1) return n;
  int sum_last_digt = 1, prev = 0, curr = 1;
  for (int i = 0; i < n - 1; i++) {
    int temp = curr % 10;
    curr = prev % 10 + curr % 10;
    prev = temp;
    sum_last_digt += curr % 10;
  }
  return sum_last_digt % 10;
}

int main() {
  long long n = 0;
  std::cin >> n;
  // std::cout << fibonacci_sum_naive(n);
  std::cout << fibonacci_sum_fast(n);
}
