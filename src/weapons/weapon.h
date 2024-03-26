#ifndef DEEPCORE_DPS_WEAPONS_WEAPON_H_
#define DEEPCORE_DPS_WEAPONS_WEAPON_H_

#include <array>
#include <cassert>
#include <string>
#include <variant>
#include <vector>

namespace deepcore_dps {

class Mod {
 public:
  struct Effect {
    bool is_additive;
    std::variant<int, float> value;
    std::string text;
  };

  Mod() = default;
  Mod(std::string_view name, const Effect& e);
  Mod(std::string_view name, const std::vector<Effect>& v);

 private:
  friend bool operator==(const Mod& l, const Mod& r);

  std::string name_;
  std::vector<Effect> effect_list_;
  std::string_view description_;
};

class ModTier {
 public:
  using TwoModsTier = std::array<Mod, 2>;
  using ThreeModsTier = std::array<Mod, 3>;

  ModTier(const Mod& a, const Mod& b);
  ModTier(const Mod& a, const Mod& b, const Mod& c);

  Mod operator[](char idx) const;
  [[nodiscard]] auto begin() const;
  [[nodiscard]] auto end() const;

 private:
  template <typename Row>
  [[nodiscard]] Mod GetMod(char mod) const {
    Row r = std::get<Row>(tier_);
    int i = mod - 'A';
    assert(i >= 0 && i < r.size());
    return r.at(i);
  }

  std::variant<TwoModsTier, ThreeModsTier> tier_;
};

class ModTree {
 public:
  static constexpr std::size_t kTreeHeight{5};

  explicit ModTree(const std::array<ModTier, kTreeHeight>& tree);

  ModTier operator[](size_t idx) const;
  [[nodiscard]] auto begin() const;
  [[nodiscard]] auto end() const;

 private:
  std::array<ModTier, kTreeHeight> tree_;
};

enum class OverclockType { kClean, kBalanced, kUnstable };

struct Overclock {
  std::string name;
  std::string description;
  OverclockType type;
};

struct WeaponBuildString {
  std::string mods;
  std::string overclock;
};

WeaponBuildString InputBuildParser(std::string_view build);

class Weapon {
 public:
  struct Build {
    using ModList = std::array<Mod, ModTree::kTreeHeight>;
    ModList mods;
    Overclock overclock;
  };

  virtual ~Weapon() = default;

  [[nodiscard]] virtual float MagazineDamage() const = 0;
  [[nodiscard]] virtual float MagazineDuration() const = 0;
  [[nodiscard]] virtual float TotalDamage() const = 0;
  [[nodiscard]] virtual float BurstDps() const = 0;
  [[nodiscard]] virtual float SustainedDps() const = 0;

 private:
  virtual void UpdateWeaponStats() = 0;
};

}  // namespace deepcore_dps

#endif  // DEEPCORE_DPS_WEAPONS_WEAPON_H_
