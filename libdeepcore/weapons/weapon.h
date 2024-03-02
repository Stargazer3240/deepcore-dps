#ifndef LIBDEEPCORE_WEAPON_H
#define LIBDEEPCORE_WEAPON_H

#include <optional>
#include <string>

namespace libdeepcore::weapons {

struct Mod {
  std::string name_;
  std::string description_;
};

enum class OverclockType { kClean, kBalanced, kUnstable };

struct ModRow {
  Mod A_;
  Mod B_;
  std::optional<Mod> C_;
};

struct ModTree {
  ModRow T1_;
  ModRow T2_;
  ModRow T3_;
  ModRow T4_;
  ModRow T5_;
};

struct Overclock {
  std::string name_;
  std::string description_;
  OverclockType type_;
};

class Weapon {
 public:
  [[nodiscard]] virtual int magazine_damage() const = 0;

  [[nodiscard]] virtual float magazine_duration() const = 0;

  [[nodiscard]] virtual int total_damage() const = 0;

  [[nodiscard]] virtual float burst_dps() const = 0;

  [[nodiscard]] virtual float sustained_dps() const = 0;

  virtual ~Weapon() = default;
};

}  // namespace libdeepcore::weapons

#endif  // LIBDEEPCORE_WEAPON_H
