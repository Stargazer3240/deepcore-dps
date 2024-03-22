#include "deepcore_gk2.h"

namespace deepcore_dps {

inline int DeepcoreGK2::MagazineDamage() const {
  return damage_ * magazine_size_;
}

inline float DeepcoreGK2::MagazineDuration() const {
  return float(magazine_size_) / float(rate_of_fire_);
}

inline int DeepcoreGK2::TotalDamage() const {
  return (magazine_size_ + max_ammo_) * damage_;
}

inline float DeepcoreGK2::BurstDps() const {
  return float(MagazineDamage()) / MagazineDuration();
}

inline float DeepcoreGK2::SustainedDps() const {
  return float(MagazineDamage()) / (MagazineDuration() + reload_time_);
}

}  // namespace deepcore_dps
