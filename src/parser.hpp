#ifndef SCORE_CALCULATOR_PARSER_HPP
#define SCORE_CALCULATOR_PARSER_HPP

#include "hand.hpp"
#include "meld.hpp"
#include "tile.hpp"
#include <string>

namespace score_calculator {
  Tiles from_mpsz(const std::string&);
  void from_mpsz(const std::string&, Hand&, Melds&);
  std::string to_mpsz(const Hand&, const Melds& = {});
}

#endif
