#ifndef MAHJONG_SCORE_CALCULATOR_UTILS_HPP
#define MAHJONG_SCORE_CALCULATOR_UTILS_HPP

#include <iostream>
#include <mahjong/score_calculator/types.hpp>

namespace mahjong::score_calculator {
  std::ostream& operator<<(std::ostream& os, const YakuId yaku_id);
}

#endif
