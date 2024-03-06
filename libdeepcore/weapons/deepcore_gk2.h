#ifndef LIBDEEPCORE_DEEPCORE_GK2_H
#define LIBDEEPCORE_DEEPCORE_GK2_H

#include <string>

#include "weapon.h"

namespace libdeepcore::weapons {

const int gk2_damage{16};
const float gk2_stun_duration{1.5};
const int gk2_mag_size{30};
const int gk2_max_ammo{360};
const int gk2_rate_of_fire{8};
const float gk2_reload_time{1.8};
const float gk2_stun_chance{0.15};
const float gk2_base_spread{1.0};
const float gk2_armor_breaking{1.0};

class DeepcoreGK2 : public Weapon {
 public:
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

  static constexpr std::string kName{"Deepcore GK2"};
  // static constexpr ModTree mod_tree_();

 private:
  int damage{gk2_damage};
  float weakpoint_stun_duration{gk2_stun_duration};
  int magazine_size{gk2_mag_size};
  int max_ammo{gk2_max_ammo};
  int rate_of_fire{gk2_rate_of_fire};
  float reload_time{gk2_reload_time};
  float weakpoint_stun_chance{gk2_stun_chance};
  float base_spread{gk2_base_spread};
  float armor_breaking{gk2_armor_breaking};
};

}  // namespace libdeepcore::weapons

#endif  // LIBDEEPCORE_DEEPCORE_GK2_H
