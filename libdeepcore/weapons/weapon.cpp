#include "weapon.h"

namespace libdeepcore {

BuildString InputBuildParser(std::string_view build) {
  std::string s{build};
  return {s.substr(0, ModTree::kTreeHeight), s.substr(ModTree::kTreeHeight)};
}

}  // namespace libdeepcore
