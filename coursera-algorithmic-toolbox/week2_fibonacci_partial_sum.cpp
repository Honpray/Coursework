#include <iostream>
#include <vector>
using std::vector;

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

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

// To get last digit, we compute Fn mod 10 and we know for any integer 𝑚 ≥ 2, the sequence is periodical
int get_fibonacci_partial_sum_fast(int from, int to){
    int sum = 0;
    for (int i=from; i< to+1; i++)
        sum += get_fibonacci_huge_fast(i, 10);
    return sum % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    // std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
