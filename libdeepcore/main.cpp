#include <iostream>

#include "weapons/deepcore_gk2.h"

int main() {
  using GK2 = libdeepcore::weapons::DeepcoreGK2;
  GK2 gk2;
  std::cout << gk2.magazine_damage() << '\n';

  return 0;
}
