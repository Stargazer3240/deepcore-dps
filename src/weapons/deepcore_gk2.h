#ifndef DEEPCORE_DPS_WEAPONS_DEEPCORE_GK2_H_
#define DEEPCORE_DPS_WEAPONS_DEEPCORE_GK2_H_

#include <string_view>

#include "weapon.h"

namespace deepcore_dps {

class DeepcoreGK2 : public Weapon {
 public:
  [[nodiscard]] float MagazineDamage() const override;
  [[nodiscard]] float MagazineDuration() const override;
  [[nodiscard]] float TotalDamage() const override;
  [[nodiscard]] float BurstDps() const override;
  [[nodiscard]] float SustainedDps() const override;

 private:
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

  static constexpr int kOverclockAmount{7};

  float damage_{kDamage};
  int magazine_size_{kMagSize};
  int max_ammo_{kMaxAmmo};
  int rate_of_fire_{kRateOfFire};
  float reload_time_{kReloadTime};
  float weakpoint_stun_duration_{kStunDuration};
  float weakpoint_stun_chance_{kStunChance};
  float base_spread_{kBaseSpread};
  float armor_breaking_{kArmorBreaking};
};

}  // namespace deepcore_dps

#endif  // DEEPCORE_DPS_WEAPONS_DEEPCORE_GK2_H_
