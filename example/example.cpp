#include "caster.hpp"

#include <iostream>

struct CInt {
  int a;
};

struct MyInt {
  int x;
};

auto c_function(CInt z) {
  return z;
}

auto c_function2(int z) {
  return z + 3;
}

auto c_function3(int z, int zz) {
  return z + 3 + zz;
}

auto c_function4(CInt z, CInt zz) {
  z.a += zz.a + 100;
  return z;
}

auto c_function6(CInt z, CInt* zz) {
  z.a += zz->a + 100;
  return z;
}

auto c_function7(CInt z, const CInt* zz) {
  z.a += zz->a + 100;
  return z;
}

const CInt* c_function8(CInt z, const CInt* zz) {
  z.a += zz->a + 100;
  return zz;
}
namespace caster {
template<>
struct casted_type<MyInt> { using type = CInt; };

template<>
struct casted_type<CInt> { using type = MyInt; };

static_assert(is_castable_v<MyInt>);
}

void f(int x);

int main() {
  MyInt a, b;
  a.x = 3;
  b.x = 1;
  std::cout << caster::invoke(c_function, a).x << std::endl;
  std::cout << caster::invoke(c_function2, 3) << std::endl;
  std::cout << caster::invoke(c_function3, 3, 5) << std::endl;
  std::cout << caster::invoke(c_function4, a, b).x << std::endl;
  std::cout << caster::invoke(c_function6, a, &b).x << std::endl;
  std::cout << caster::invoke(c_function7, a, &b).x << std::endl;
  std::cout << caster::invoke(c_function8, a, &b)->x << std::endl;
  return 0;
}
