#ifndef LIBDEEPCORE_WEAPONS_WEAPON_H_
#define LIBDEEPCORE_WEAPONS_WEAPON_H_

#include <array>
#include <cassert>
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

  ModRow(const Mod& a, const Mod& b) : row_{TwoModsRow{a, b}} {};
  ModRow(const Mod& a, const Mod& b, const Mod& c)
      : row_{ThreeModsRow{a, b, c}} {};

  Mod operator[](char idx) const {
    return is_two_mods_row_ ? GetMod<TwoModsRow>(idx)
                            : GetMod<ThreeModsRow>(idx);
  };

  [[nodiscard]] auto begin() const {
    return is_two_mods_row_ ? std::get<TwoModsRow>(row_).begin()
                            : std::get<ThreeModsRow>(row_).begin();
  };
  [[nodiscard]] auto end() const {
    return is_two_mods_row_ ? std::get<TwoModsRow>(row_).end()
                            : std::get<ThreeModsRow>(row_).end();
  };

 private:
  template <typename Row>
  [[nodiscard]] Mod GetMod(char mod) const {
    Row r = std::get<Row>(row_);
    int i = mod - 'A';
    assert(i >= 0 && i < r.size());
    return r.at(i);
  }

  std::variant<TwoModsRow, ThreeModsRow> row_;
  // Used in expressions that check for the variant held data type.
  bool is_two_mods_row_ = std::holds_alternative<TwoModsRow>(row_);
};

class ModTree {
 public:
  static constexpr size_t kTreeHeight{5};

  ModTree(const ModRow& t1, const ModRow& t2, const ModRow& t3,
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
};

struct Build {
  using ModList = std::array<Mod, ModTree::kTreeHeight>;
  ModList mods;
  Overclock overclock;
};

struct BuildString {
  std::string mods;
  std::string overclock;
};

BuildString InputBuildParser(std::string_view build);

class Weapon {
 public:
  virtual ~Weapon() = default;

  virtual int MagazineDamage() const = 0;
  virtual float MagazineDuration() const = 0;
  virtual int TotalDamage() const = 0;
  virtual float BurstDps() const = 0;
  virtual float SustainedDps() const = 0;
  virtual ModTree tree() const = 0;
  virtual Build current_build() const = 0;
  virtual std::string current_build_str() const = 0;
};

}  // namespace libdeepcore

#endif  // LIBDEEPCORE_WEAPONS_WEAPON_H_
