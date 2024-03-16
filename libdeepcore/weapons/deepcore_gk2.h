#ifndef LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
#define LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_

#include <string_view>

#include "weapon.h"

namespace libdeepcore::weapons {

class DeepcoreGK2 : public Weapon {
 public:
  static constexpr std::string_view name{"Deepcore GK2"};
  static constexpr int kDamage{16};
  static constexpr float kStunDuration{1.5};
  static constexpr int kMagSize{30};
  static constexpr int kMaxAmmo{360};
  static constexpr int kRateOfFire{8};
  static constexpr float kReloadTime{1.8};
  static constexpr float kStunChance{0.15};
  static constexpr float kBaseSpread{1.0};
  static constexpr float kArmorBreaking{1.0};

  [[nodiscard]] int magazine_damage() const override {
    return damage * magazine_size;
  }

  [[nodiscard]] float magazine_duration() const override {
    return float(magazine_size) / float(rate_of_fire);
  }

  [[nodiscard]] int total_damage() const override {
    return (magazine_size + max_ammo) * damage;
  }

  [[nodiscard]] float burst_dps() const override {
    return float(magazine_damage()) / magazine_duration();
  }

  [[nodiscard]] float sustained_dps() const override {
    return float(magazine_damage()) / (magazine_duration() + reload_time);
  }

  // static constexpr ModTree mod_tree_();

 private:
  int damage{kDamage};
  float weakpoint_stun_duration{kStunDuration};
  int magazine_size{kMagSize};
  int max_ammo{kMaxAmmo};
  int rate_of_fire{kRateOfFire};
  float reload_time{kReloadTime};
  float weakpoint_stun_chance{kStunChance};
  float base_spread{kBaseSpread};
  float armor_breaking{kArmorBreaking};
};

}  // namespace libdeepcore::weapons

#endif  // LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
