#ifndef LIBDEEPCORE_DEEPCORE_GK2_H
#define LIBDEEPCORE_DEEPCORE_GK2_H

#include <string>

#include "weapon.h"

namespace libdeepcore::weapons {

const int kGK2Damage{16};
const float kGK2StunDuration{1.5};
const int kGK2MagSize{30};
const int kGK2MaxAmmo{360};
const int kGK2RateOfFire{8};
const float kGK2ReloadTime{1.8};
const float kGK2StunChance{0.15};
const float kGK2BaseSpread{1.0};
const float kGK2ArmorBreaking{1.0};

class DeepcoreGK2 : public Weapon {
 public:
  static constexpr std::string name_{"Deepcore GK2"};

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

 private:
  int damage_{kGK2Damage};
  float weakpoint_stun_duration_{kGK2StunDuration};
  int magazine_size_{kGK2MagSize};
  int max_ammo_{kGK2MaxAmmo};
  int rate_of_fire_{kGK2RateOfFire};
  float reload_time_{kGK2ReloadTime};
  float weakpoint_stun_chance_{kGK2StunChance};
  float base_spread_{kGK2BaseSpread};
  float armor_breaking_{kGK2ArmorBreaking};
};

}  // namespace libdeepcore::weapons

#endif  // LIBDEEPCORE_DEEPCORE_GK2_H
