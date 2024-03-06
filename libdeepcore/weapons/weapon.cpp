#include "weapon.h"

#include <stdexcept>

namespace libdeepcore::weapons {

Mod ModRow::operator[](char idx) const {
  switch (idx) {
    case 'A':
      return row[0];
    case 'B':
      return row[1];
    case 'C':
      if (row.size() != 3) {
        throw std::out_of_range("This mod row has only A and B mods!");
      }
      return row[2];
    default:
      throw std::out_of_range("Not a valid mod slot [A-C]!");
  }
}

}  // namespace libdeepcore::weapons
