#ifndef LIBDEEPCORE_WEAPONS_WEAPON_H_
#define LIBDEEPCORE_WEAPONS_WEAPON_H_

#include <array>
#include <cassert>
#include <stdexcept>
#include <string>
#include <variant>

namespace libdeepcore::weapons {

struct Mod {
  std::string name;
  std::string description;
};

class ModRow {
 public:
  using TwoModsRow = std::array<Mod, 2>;
  using ThreeModsRow = std::array<Mod, 3>;

  template <typename Row>
    requires(std::is_same_v<Row, TwoModsRow> ||
             std::is_same_v<Row, ThreeModsRow>)
  explicit ModRow(const Row& r) : row_{r} {};

  Mod operator[](char idx) const {
    return is_two_mod_row ? get_mod<TwoModsRow>(idx)
                          : get_mod<ThreeModsRow>(idx);
  }

  [[nodiscard]] auto begin() const {
    return is_two_mod_row ? std::get<TwoModsRow>(row_).begin()
                          : std::get<ThreeModsRow>(row_).begin();
  };
  [[nodiscard]] auto end() const {
    return is_two_mod_row ? std::get<TwoModsRow>(row_).end()
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
  bool is_two_mod_row = std::holds_alternative<TwoModsRow>(row_);
};

const size_t mod_tree_height{5};
class ModTree {
 public:
  explicit ModTree(const std::array<ModRow, mod_tree_height>& t) : tree{t} {};

  ModRow operator[](const size_t idx) const {
    assert(idx > 0 && idx <= mod_tree_height);
    return tree.at(idx - 1);
  }

  [[nodiscard]] auto begin() const { return tree.begin(); }
  [[nodiscard]] auto end() const { return tree.end(); }

 private:
  std::array<ModRow, mod_tree_height> tree;
};

enum class OverclockType { clean, balanced, unstable };

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

}  // namespace libdeepcore::weapons

#endif  // LIBDEEPCORE_WEAPONS_WEAPON_H_
