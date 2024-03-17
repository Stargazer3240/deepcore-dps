#ifndef LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_
#define LIBDEEPCORE_WEAPONS_DEEPCORE_GK2_H_

#include <string>
#include <string_view>

#include "utils.h"
#include "weapon.h"

namespace libdeepcore {

class DeepcoreGK2 : public Weapon {
 public:
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
  [[nodiscard]] WeaponBuild current_build() const override {
    return current_build_;
  };
  [[nodiscard]] std::string current_build_str() const override {
    return current_build_str_;
  };

  void set_current_build(std::string_view build);

  Mod banana() { return t1_a(); };

 private:
  static constexpr int kOverclockAmount{7};
  using OverclockList = std::array<Overclock, kOverclockAmount>;

  static constexpr std::string_view kName{"Deepcore GK2"};
  static constexpr float kDamage{16};
  static constexpr int kMagSize{30};
  static constexpr int kMaxAmmo{360};
  static constexpr int kRateOfFire{8};
  static constexpr float kReloadTime{1.8};
  static constexpr float kStunDuration{1.5};
  static constexpr float kStunChance{0.15};
  static constexpr float kBaseSpread{1.0};
  static constexpr float kArmorBreaking{1.0};

  static constexpr std::string_view kT1_A_Name{"Gyro Stabilisation"};
  static constexpr int kT1_A_SpreadChange{0};
  static constexpr std::string_view kT1_A_SpreadChangeText{
      "Base Spread (First Shot)"};
  static constexpr std::string_view kT1_B_Name{"Supercharged Feed Mechanism"};
  static constexpr std::string_view kT1_C_Name{"Quickfire Ejector"};
  static constexpr std::string_view kT2_A_Name{"Increased Caliber Rounds"};
  static constexpr std::string_view kT2_B_Name{"Expanded Ammo Bags"};
  static constexpr std::string_view kT3_A_Name{"Floating Barrel"};
  static constexpr std::string_view kT3_B_Name{"High Capacity Magazine"};
  static constexpr std::string_view kT4_A_Name{"Hollow-Point Bullets"};
  static constexpr std::string_view kT4_B_Name{"Hardened Rounds"};
  static constexpr std::string_view kT5_A_Name{"Battle Frenzy"};
  static constexpr std::string_view kT5_B_Name{"Improved Gas System"};
  static constexpr std::string_view kT5_C_Name{"Stun"};

  static constexpr int kT1_B_RateOfFireChange{1};
  static constexpr float kT1_C_ReloadTimeChange{0.73};
  static constexpr float kT2_A_DamageChange{3};
  static constexpr int kT2_B_AmmoChange{120};
  static constexpr float kT3_A_RecoilChange{0.5};
  static constexpr float kT3_A_SpreadChange{-0.65};
  static constexpr int kT3_B_MagChange{10};
  static constexpr float kT4_A_WeakpointBonusChange{0.2};
  static constexpr float kT4_B_ArmorBreakingChange{5};
  static constexpr int kT5_B_RateOfFireChange{2};
  static constexpr float kT5_C_StunChanceChange{0.35};

  WeaponBuild AssembleBuild(std::string_view input_build) const;
  WeaponBuild::ModList AssembleMods(std::string_view mods) const;
  Overclock AssembleOverclock(char c) const;
  void UpdateWeaponStats() override;
  // void UpdateDamage();
  // void UpdateStunDuration();
  // void UpdateMagSize();
  // void UpdateMaxAmmo();
  // void UpdateRateOfFire();
  // void UpdateReloadTime();
  // void UpdateStunChance();
  // void UpdateBaseSpread();
  // void UpdateArmorBreaking();

  Mod t1_a() const { return Mod(t1_a_name(), t1_a_changes()); }
  std::string t1_a_name() const { return std::string(kT1_A_Name); }
  std::vector<ModChange> t1_a_changes() const {
    return {ModChange(ChangeType::kMultiplicative, kT1_A_SpreadChange,
                      std::string(kT1_A_SpreadChangeText))};
  };

  Mod t1_b() const { return Mod(t1_b_name()); };
  std::string t1_b_name() const { return std::string(kT1_B_Name); };
  std::string t1_b_description() const { return ""; };

  Mod t1_c() const { return Mod(t1_c_name()); };
  std::string t1_c_name() const { return std::string(kT1_C_Name); };
  std::string t1_c_description() const { return ""; };

  Mod t2_a() const { return Mod(t2_a_name()); };
  std::string t2_a_name() const { return std::string(kT2_A_Name); };
  std::string t2_a_description() const { return ""; };

  Mod t2_b() const { return Mod(t2_b_name()); };
  std::string t2_b_name() const { return std::string(kT2_B_Name); };
  std::string t2_b_description() const { return ""; };

  Mod t3_a() const { return Mod(t3_a_name()); };
  std::string t3_a_name() const { return std::string(kT3_A_Name); };
  std::string t3_a_description() const { return ""; };

  Mod t3_b() const { return Mod(t3_b_name()); };
  std::string t3_b_name() const { return std::string(kT3_B_Name); };
  std::string t3_b_description() const { return ""; };

  Mod t4_a() const { return Mod(t4_a_name()); };
  std::string t4_a_name() const { return std::string(kT4_A_Name); };
  std::string t4_a_description() const { return ""; };

  Mod t4_b() const { return Mod(t4_b_name()); };
  std::string t4_b_name() const { return std::string(kT4_B_Name); };
  std::string t4_b_description() const { return ""; };

  Mod t5_a() const { return Mod(t5_a_name()); };
  std::string t5_a_name() const { return std::string(kT5_A_Name); };
  std::string t5_a_description() const { return ""; };

  Mod t5_b() const { return Mod(t5_b_name()); };
  std::string t5_b_name() const { return std::string(kT5_B_Name); };
  std::string t5_b_description() const { return ""; };

  Mod t5_c() const { return Mod(t5_c_name()); };
  std::string t5_c_name() const { return std::string(kT5_C_Name); };
  std::string t5_c_description() const { return ""; };

  float damage_{kDamage};
  int magazine_size_{kMagSize};
  int max_ammo_{kMaxAmmo};
  int rate_of_fire_{kRateOfFire};
  float reload_time_{kReloadTime};
  float weakpoint_stun_duration_{kStunDuration};
  float weakpoint_stun_chance_{kStunChance};
  float base_spread_{kBaseSpread};
  float armor_breaking_{kArmorBreaking};

  WeaponBuild current_build_;
  std::string current_build_str_{"------"};

  Mod t2_a_{"Increased Caliber Rounds"};
  Mod t2_b_{"Expanded Ammo Bags"};
  Mod t3_a_{"Floating Barrel"};
  Mod t3_b_{"High Capacity Magazine"};
  Mod t4_a_{"Hollow-Point Bullets"};
  Mod t4_b_{"Hollow-Point Bullets"};
  Mod t5_a_{"Battle Frenzy"};
  Mod t5_b_{"Improved Gas System"};
  Mod t5_c_{"Stun"};
  ModTree tree_{ModRow{t1_a(), t1_b(), t1_c()}, ModRow{t2_a(), t2_b()},
                ModRow{t3_a(), t3_b()}, ModRow{t4_a(), t4_b()},
                ModRow{t5_a(), t5_b(), t5_c()}};

  Overclock oc1_{"Compact Ammo", "+5 Magazine Size, x0.7 Recoil",
                 OverclockType::kClean};
  Overclock oc2_{"Gas Rerouting", "+1 Rate of Fire, x0.84 Reload Time",
                 OverclockType::kClean};
  Overclock oc3_{"Homebrew Powder",
                 "Anywhere from x0.8 - x1.4 damage per shot, averaged to x1.1",
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
