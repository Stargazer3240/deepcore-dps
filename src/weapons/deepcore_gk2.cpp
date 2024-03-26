#include "deepcore_gk2.h"

namespace deepcore_dps {

float DeepcoreGK2::MagazineDamage() const {
  return damage_ * static_cast<float>(magazine_size_);
}

float DeepcoreGK2::MagazineDuration() const {
  return float(magazine_size_) / float(rate_of_fire_);
}

float DeepcoreGK2::TotalDamage() const {
  return static_cast<float>(magazine_size_ + max_ammo_) * damage_;
}

float DeepcoreGK2::BurstDps() const {
  return float(MagazineDamage()) / MagazineDuration();
}

float DeepcoreGK2::SustainedDps() const {
  return float(MagazineDamage()) / (MagazineDuration() + reload_time_);
}

}  // namespace deepcore_dps
