#include <iostream>

#include "weapons/deepcore_gk2.h"
#include "weapons/weapon.h"

int main() {
  using namespace libdeepcore;

  DeepcoreGK2 gk2;
  gk2.set_current_build("CBABC7");
  Build b = gk2.current_build();
  for (const Mod& m : b.mods) {
    std::cout << m.name << " | " << m.description << '\n';
  }
  std::cout << b.overclock.name << " | " << b.overclock.description;

  return 0;
}
