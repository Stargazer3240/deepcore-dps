#include "weapon.h"

namespace deepcore_dps {

inline Mod::Mod(std::string_view name, const Effect& e) : name_{name} {
  effect_list_.push_back(e);
}

inline Mod::Mod(std::string_view name, const std::vector<Effect>& v)
    : name_{name}, effect_list_{v} {}

bool operator==(const Mod& l, const Mod& r) {
  return l.name_ == r.name_ && l.description_ == r.description_;
}

inline bool operator==(const Mod::Effect& l, const Mod::Effect& r) {
  return l.is_additive == r.is_additive && l.value == r.value &&
         l.text == r.text;
}

inline ModTier::ModTier(const Mod& a, const Mod& b)
    : tier_{TwoModsTier{a, b}} {}
inline ModTier::ModTier(const Mod& a, const Mod& b, const Mod& c)
    : tier_{ThreeModsTier{a, b, c}} {}

Mod ModTier::operator[](char idx) const {
  return std::holds_alternative<TwoModsTier>(tier_)
             ? GetMod<TwoModsTier>(idx)
             : GetMod<ThreeModsTier>(idx);
}
auto ModTier::begin() const {
  return std::holds_alternative<TwoModsTier>(tier_)
             ? std::get<TwoModsTier>(tier_).begin()
             : std::get<ThreeModsTier>(tier_).begin();
}
auto ModTier::end() const {
  return std::holds_alternative<TwoModsTier>(tier_)
             ? std::get<TwoModsTier>(tier_).end()
             : std::get<ThreeModsTier>(tier_).end();
}

inline ModTree::ModTree(const std::array<ModTier, kTreeHeight>& tree)
    : tree_{tree} {}

inline ModTier ModTree::operator[](const size_t idx) const {
  assert(idx > 0 && idx <= kTreeHeight);
  return tree_.at(idx - 1);
}

inline auto ModTree::begin() const { return tree_.begin(); }
inline auto ModTree::end() const { return tree_.end(); }

WeaponBuildString InputBuildParser(std::string_view build) {
  std::string s{build};
  return {s.substr(0, ModTree::kTreeHeight), s.substr(ModTree::kTreeHeight)};
}

}  // namespace deepcore_dps
