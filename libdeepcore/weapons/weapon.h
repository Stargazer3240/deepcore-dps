#ifndef LIBDEEPCORE_WEAPONS_WEAPON_H_
#define LIBDEEPCORE_WEAPONS_WEAPON_H_

#include <array>
#include <cassert>
#include <stdexcept>
#include <string>
#include <variant>

namespace libdeepcore {

struct Mod {
  std::string name;
  std::string description;
};

class ModRow {
 public:
  using TwoModsRow = std::array<Mod, 2>;
  using ThreeModsRow = std::array<Mod, 3>;

  template <typename T>
    requires(std::is_same_v<T, TwoModsRow> || std::is_same_v<T, ThreeModsRow>)
  explicit ModRow(const T& r) : row_{r} {};

  Mod operator[](char idx) const {
    return is_two_mod_row_ ? get_mod<TwoModsRow>(idx)
                           : get_mod<ThreeModsRow>(idx);
  }

  [[nodiscard]] auto begin() const {
    return is_two_mod_row_ ? std::get<TwoModsRow>(row_).begin()
                           : std::get<ThreeModsRow>(row_).begin();
  };
  [[nodiscard]] auto end() const {
    return is_two_mod_row_ ? std::get<TwoModsRow>(row_).end()
                           : std::get<ThreeModsRow>(row_).end();
  };

 private:
  template <typename Row>
  [[nodiscard]] Mod get_mod(char idx) const {
    Row r = std::get<Row>(row_);
    switch (idx) {
      case 'A':
        return r.at(0);
      case 'B':
        return r.at(1);
      case 'C':
        if (std::is_same_v<Row, ThreeModsRow>) {
          return r.at(2);
        }
      default:
        std::string mod_range =
            std::is_same_v<Row, TwoModsRow> ? "[A-B]" : "[A-C]";
        throw std::out_of_range("Not a valid mod slot " + mod_range + "!");
    }
  }

  std::variant<TwoModsRow, ThreeModsRow> row_;
  // To be used with common variant tests for the row data member.
  bool is_two_mod_row_ = std::holds_alternative<TwoModsRow>(row_);
};

class ModTree {
 public:
  static constexpr size_t kTreeHeight{5};

  explicit ModTree(const std::array<ModRow, kTreeHeight>& t) : tree_{t} {};

  ModRow operator[](const size_t idx) const {
    assert(idx > 0 && idx <= kTreeHeight);
    return tree_.at(idx - 1);
  }

  [[nodiscard]] auto begin() const { return tree_.begin(); }
  [[nodiscard]] auto end() const { return tree_.end(); }

 private:
  std::array<ModRow, kTreeHeight> tree_;
};

enum class OverclockType { kClean, kBalanced, kUnstable };

struct Overclock {
  std::string name;
  std::string description;
  OverclockType type;
};

class Weapon {
 public:
  Weapon() = default;
  virtual ~Weapon() = default;

  [[nodiscard]] virtual int magazine_damage() const = 0;
  [[nodiscard]] virtual float magazine_duration() const = 0;
  [[nodiscard]] virtual int total_damage() const = 0;
  [[nodiscard]] virtual float burst_dps() const = 0;
  [[nodiscard]] virtual float sustained_dps() const = 0;
};

}  // namespace libdeepcore

#endif  // LIBDEEPCORE_WEAPONS_WEAPON_H_
