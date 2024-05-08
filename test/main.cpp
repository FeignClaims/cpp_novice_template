#include "std_lib_facilities.h"

int x;

int main() {
  int x{};
  std::cout << std::boolalpha << (std::compare_strong_order_fallback(1, 2) < 0) << '\n';
}