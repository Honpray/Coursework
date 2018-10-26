#include <iostream>

int gcd_fast(int a, int b) {
  int r = b % a;
  while (r != 0) {
    b = a;
    a = r;
    r = b % a;
  }
  if (r == 0)
    return a;
  else
    return 1;
}

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int64_t lcm_fast(int a, int b){
  return a/gcd_fast(a,b)*b; // the order matters here
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
