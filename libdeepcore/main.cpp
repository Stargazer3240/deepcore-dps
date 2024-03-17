#include <iostream>

#include "weapons/deepcore_gk2.h"
#include "weapons/weapon.h"

int main() {
  using namespace libdeepcore;

  DeepcoreGK2 gk2;
  std::cout << DeepcoreGK2::kName << '\n';
  std::cout << gk2.tree()[5]['A'].name << '\n';

  return 0;
}
