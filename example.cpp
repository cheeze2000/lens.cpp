#include <iostream>
#include <utility>
#include "lens.hpp"

// we have:
// xs = ((1, 2), (3, 4))
//
// we want:
// ys = ((1, 2), (30, 4))
int main() {
  std::pair<int, int> p0(1, 2);
  std::pair<int, int> p1(3, 4);
  std::pair<std::pair<int, int>, std::pair<int, int>> xs(p0, p1), ys;

  // _1 is a lens that focuses on the first element of a pair
  auto v = [](auto p) { return p.first; };
  auto o = [](auto f, auto p) {
    return std::make_pair(f(p.first), p.second);
  };
  Lens _1(&v, &o);

  // _2 is a lens that focuses on the second element of a pair
  auto v_ = [](auto p) { return p.second; };
  auto o_ = [](auto f, auto p) {
    return std::make_pair(p.first, f(p.second));
  };
  Lens _2(&v_, &o_);

  // compose both lenses
  // focus on the second element ((3, 4)), then the first element (3)
  ys = over(_2 + _1)([](int a) {
    return a * 10;
  }, xs);

  std::pair<int, int> y0 = ys.first, y1 = ys.second;
  printf("((%d, %d), (%d, %d))\n", y0.first, y0.second, y1.first, y1.second);
}
