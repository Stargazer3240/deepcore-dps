#include "weapon.h"

#include "utils.h"

namespace libdeepcore {

std::string Mod::AssembleDescription() const {
  std::string s;
  bool is_additive{true};
  for (const ModChange& c : changes) {
    is_additive = true;
    if (c.type == ChangeType::kMultiplicative) {
      s.append("x");
      is_additive = false;
    }
    s.append(ModChangeValueToString(c.value, is_additive));
    s.append(" ");
    s.append(c.text);
    if (c != changes.back()) {
      s.append(", ");
    }
  }
  return s;
}

std::string ModChangeValueToString(const std::variant<int, float>& value,
                                   bool is_additive) {
  std::string s;
  if (std::holds_alternative<int>(value)) {
    s.append(ToStringWithPrecision(std::get<int>(value), is_additive));
  } else {
    s.append(ToStringWithPrecision(std::get<float>(value), is_additive));
  }
  return s;
}

WeaponBuildString InputBuildParser(std::string_view build) {
  std::string s{build};
  return {s.substr(0, ModTree::kTreeHeight), s.substr(ModTree::kTreeHeight)};
}

}  // namespace libdeepcore
