#include <iostream>

#include "weapons/deepcore_gk2.h"

int main() {
  using GK2 = libdeepcore::weapons::DeepcoreGK2;
  std::cout << GK2::name_ << '\n';

  return 0;
}
