#include "deepcore_gk2.h"

namespace libdeepcore {

void DeepcoreGK2::set_current_build(std::string_view input_build) {
  current_build_ = AssembleBuild(input_build);
  current_build_str_ = input_build;
}

WeaponBuild DeepcoreGK2::AssembleBuild(std::string_view input_build) const {
  auto [mods, oc] = InputBuildParser(input_build);
  WeaponBuild b;
  b.mods = AssembleMods(mods);
  b.overclock = AssembleOverclock(oc[0]);
  return b;
}

WeaponBuild::ModList DeepcoreGK2::AssembleMods(std::string_view mods) const {
  WeaponBuild::ModList m;
  for (int i{0}; char c : mods) {
    if (c != '-') {
      // Tree "[]" operator is one-based indexed.
      m[i] = tree_[i + 1][c];
    } else {
      m[i] = Mod();
    }
    ++i;
  }
  return m;
}

Overclock DeepcoreGK2::AssembleOverclock(char c) const {
  if (c != '-') {
    // Input build is one-based indexed.
    int oc_idx = c - '1';
    assert(oc_idx >= 0 && oc_idx < overclock_list_.size());
    return overclock_list_[oc_idx];
  }
  return Overclock();
}

void DeepcoreGK2::UpdateWeaponStats() {
  // UpdateDamage();
  // UpdateStunDuration();
  // UpdateMagSize();
  // UpdateMaxAmmo();
  // UpdateRateOfFire();
  // UpdateReloadTime();
  // UpdateStunChance();
  // UpdateBaseSpread();
  // UpdateArmorBreaking();
}

}  // namespace libdeepcore
