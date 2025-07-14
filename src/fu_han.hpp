#ifndef SCORE_CALCULATOR_FU_HAN_HPP
#define SCORE_CALCULATOR_FU_HAN_HPP

#include "config.hpp"
#include "hand.hpp"
#include "meld.hpp"
#include "result.hpp"
#include "types.hpp"

namespace score_calculator {
  Result calc_fu_han(Hand& hand, const Melds& melds, const Tile& winning_tile, const Config& config, int mode = 0);
}

#endif
