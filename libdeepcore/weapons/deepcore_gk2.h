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

  [[nodiscard]] ModTree tree() const override { return tree_; };

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

  Mod t1_a_{"Gyro Stabilisation", "x0 Base Spread (First Shot)"};
  Mod t1_b_{"Supercharged Feed Mechanism", "+1 Rate of Fire"};
  Mod t1_c_{"Quickfire Ejector", "x0.73 Reload Time"};
  Mod t2_a_{"Increased Caliber Rounds", "+3 Damage"};
  Mod t2_b_{"Expanded Ammo Bags", "+120 Max Ammo"};
  Mod t3_a_{"Floating Barrel", "x0.5 Recoil, -0.65 Max Spread"};
  Mod t3_b_{"High Capacity Magazine", "+10 Magazine Size"};
  Mod t4_a_{"Hollow-Point Bullets", "+20% Weakspot Damage Bonus"};
  Mod t4_b_{"Hollow-Point Bullets", "Hardened Rounds"};
  Mod t5_a_{"Battle Frenzy", "+Battle Cool, +Battle Frenzy"};
  Mod t5_b_{"Improved Gas System", "+2 Rate of Fire"};
  Mod t5_c_{"Stun", "+35% Stun Chance"};
  ModRow t1_{t1_a_, t1_b_, t1_c_};
  ModRow t2_{t2_a_, t2_b_};
  ModRow t3_{t3_a_, t3_b_};
  ModRow t4_{t4_a_, t4_b_};
  ModRow t5_{t5_a_, t5_b_, t5_c_};
  ModTree tree_{t1_, t2_, t3_, t4_, t5_};
};

}  // namespace libdeepcore

#endif  // LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
