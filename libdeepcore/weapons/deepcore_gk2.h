#ifndef LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
#define LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_

#include <string_view>

#include "weapon.h"

namespace libdeepcore {

class DeepcoreGK2 : public Weapon {
 public:
  static constexpr std::string_view kName{"Deepcore GK2"};
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
    return damage_ * magazine_size_;
  }

  [[nodiscard]] float magazine_duration() const override {
    return float(magazine_size_) / float(rate_of_fire_);
  }

  [[nodiscard]] int total_damage() const override {
    return (magazine_size_ + max_ammo_) * damage_;
  }

  [[nodiscard]] float burst_dps() const override {
    return float(magazine_damage()) / magazine_duration();
  }

  [[nodiscard]] float sustained_dps() const override {
    return float(magazine_damage()) / (magazine_duration() + reload_time_);
  }

  // static constexpr ModTree mod_tree_();

 private:
  int damage_{kDamage};
  float weakpoint_stun_duration_{kStunDuration};
  int magazine_size_{kMagSize};
  int max_ammo_{kMaxAmmo};
  int rate_of_fire_{kRateOfFire};
  float reload_time_{kReloadTime};
  float weakpoint_stun_chance_{kStunChance};
  float base_spread_{kBaseSpread};
  float armor_breaking_{kArmorBreaking};
};

}  // namespace libdeepcore

#endif  // LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
