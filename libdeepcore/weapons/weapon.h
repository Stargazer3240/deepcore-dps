#ifndef LIBDEEPCORE_WEAPON_H
#define LIBDEEPCORE_WEAPON_H

#include <array>
#include <cassert>
#include <string>
#include <vector>

namespace libdeepcore::weapons {

struct Mod {
  std::string name;
  std::string description;
};

class ModRow {
 public:
  template <size_t n>
    requires(n == 2 || n == 3)
  explicit ModRow(const std::array<Mod, n>& r) : row{r.begin(), r.end()} {};

  Mod operator[](char idx) const;
  [[nodiscard]] auto begin() const { return row.begin(); }
  [[nodiscard]] auto end() const { return row.end(); }

 private:
  std::vector<Mod> row;
};

const size_t mod_tree_height{5};

class ModTree {
 public:
  explicit ModTree(const std::array<ModRow, mod_tree_height>& t) : tree{t} {};

  ModRow operator[](size_t idx) const {
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
  [[nodiscard]] virtual int magazine_damage() const = 0;

  [[nodiscard]] virtual float magazine_duration() const = 0;

  [[nodiscard]] virtual int total_damage() const = 0;

  [[nodiscard]] virtual float burst_dps() const = 0;

  [[nodiscard]] virtual float sustained_dps() const = 0;

  virtual ~Weapon() = default;
};

}  // namespace libdeepcore::weapons

#endif  // LIBDEEPCORE_WEAPON_H
