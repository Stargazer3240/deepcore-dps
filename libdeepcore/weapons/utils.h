#include <ios>
#include <sstream>
#include <string>

namespace libdeepcore {

template <typename T>
std::string ToStringWithPrecision(T value, bool is_additive) {
  std::ostringstream out;
  out.precision(2);
  out << std::fixed;
  if (is_additive) {
    out << std::showpos;
  }
  out << value;
  return out.str();
}

}  // namespace libdeepcore
