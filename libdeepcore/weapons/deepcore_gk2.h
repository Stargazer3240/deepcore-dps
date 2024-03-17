#ifndef LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
#define LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_

#include <string>
#include <string_view>

#include "weapon.h"

namespace libdeepcore {

class DeepcoreGK2 : public Weapon {
 public:
  static constexpr int kOverclockAmount{7};
  using OverclockList = std::array<Overclock, kOverclockAmount>;

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

  [[nodiscard]] int MagazineDamage() const override {
    return damage_ * magazine_size_;
  }
  [[nodiscard]] float MagazineDuration() const override {
    return float(magazine_size_) / float(rate_of_fire_);
  }
  [[nodiscard]] int TotalDamage() const override {
    return (magazine_size_ + max_ammo_) * damage_;
  }
  [[nodiscard]] float BurstDps() const override {
    return float(MagazineDamage()) / MagazineDuration();
  }
  [[nodiscard]] float SustainedDps() const override {
    return float(MagazineDamage()) / (MagazineDuration() + reload_time_);
  }

  [[nodiscard]] ModTree tree() const override { return tree_; };
  [[nodiscard]] Build current_build() const override { return current_build_; };
  [[nodiscard]] std::string current_build_str() const override {
    return current_build_str_;
  };

  void set_current_build(std::string_view build);

 private:
  Build AssembleBuild(std::string_view input_build) const;
  Build::ModList AssembleMods(std::string_view mods) const;
  Overclock AssembleOverclock(char c) const;

  int damage_{kDamage};
  float weakpoint_stun_duration_{kStunDuration};
  int magazine_size_{kMagSize};
  int max_ammo_{kMaxAmmo};
  int rate_of_fire_{kRateOfFire};
  float reload_time_{kReloadTime};
  float weakpoint_stun_chance_{kStunChance};
  float base_spread_{kBaseSpread};
  float armor_breaking_{kArmorBreaking};
  Build current_build_;
  std::string current_build_str_{"------"};

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

  Overclock oc1_{"Compact Ammo", "+5 Magazine Size, x0.7 Recoil",
                 OverclockType::kClean};
  Overclock oc2_{"Gas Rerouting", "+1 Rate of Fire, x0.84 Reload Time",
                 OverclockType::kClean};
  Overclock oc3_{"Homebrew Powder", "+Randomized Damage",
                 OverclockType::kClean};
  Overclock oc4_{"Overclocked Firing Mechanism", "+3 Rate of Fire, x2 Recoil",
                 OverclockType::kBalanced};
  Overclock oc5_{
      "Bullets of Mercy",
      "+50% Bonus Damage to Afflicted Targets (On "
      "Fire/Stun/Electrocution/Frozen/Neurotoxin), x0.6 Magazine Size",
      OverclockType::kBalanced};
  Overclock oc6_{"AI Stability Engine",
                 "x0 Recoil, x9 Spread Recovery Speed, +50% Weakpoint Damage "
                 "Bonus, -1 Damage, -2 Rate of Fire",
                 OverclockType::kUnstable};
  Overclock oc7_{
      "Electrifying Reload",
      "+Electric Reload (100% chance), -60 Max Ammo, -10 Magazine Size",
      OverclockType::kUnstable};

  OverclockList overclock_list_{oc1_, oc2_, oc3_, oc4_, oc5_, oc6_, oc7_};
};

}  // namespace libdeepcore

#endif  // LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
