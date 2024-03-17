#ifndef LIBDEEPCORE_WEAPONS_WEAPON_H_
#define LIBDEEPCORE_WEAPONS_WEAPON_H_

#include <array>
#include <cassert>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>

namespace libdeepcore {

struct Mod {
  std::string name;
  std::string description;

  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
  Mod(std::string_view name, std::string_view desc)
      : name(name), description(desc){};
};

class ModRow {
 public:
  using TwoModsRow = std::array<Mod, 2>;
  using ThreeModsRow = std::array<Mod, 3>;

  ModRow(const Mod& a, const Mod& b) : row_{TwoModsRow{a, b}} {};
  ModRow(const Mod& a, const Mod& b, const Mod& c)
      : row_{ThreeModsRow{a, b, c}} {};

  Mod operator[](char idx) const {
    return is_two_mod_row_ ? get_mod<TwoModsRow>(idx)
                           : get_mod<ThreeModsRow>(idx);
  };

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

  explicit ModTree(const ModRow& t1, const ModRow& t2, const ModRow& t3,
                   const ModRow& t4, const ModRow& t5)
      : tree_{t1, t2, t3, t4, t5} {};

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

  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
  Overclock(std::string_view name, std::string_view desc, OverclockType type)
      : name{name}, description{desc}, type{type} {};
};

class Weapon {
 public:
  virtual ~Weapon() = default;

  [[nodiscard]] virtual int magazine_damage() const = 0;
  [[nodiscard]] virtual float magazine_duration() const = 0;
  [[nodiscard]] virtual int total_damage() const = 0;
  [[nodiscard]] virtual float burst_dps() const = 0;
  [[nodiscard]] virtual float sustained_dps() const = 0;
  [[nodiscard]] virtual ModTree tree() const = 0;
};

}  // namespace libdeepcore

#endif  // LIBDEEPCORE_WEAPONS_WEAPON_H_
