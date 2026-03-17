#ifndef MAHJONG_SCORE_CALCULATOR_FU_HAN_HPP
#define MAHJONG_SCORE_CALCULATOR_FU_HAN_HPP

#include <mahjong/score_calculator/config.hpp>
#include <mahjong/score_calculator/hand.hpp>
#include <mahjong/score_calculator/meld.hpp>
#include <mahjong/score_calculator/result.hpp>
#include <mahjong/score_calculator/types.hpp>

namespace mahjong::score_calculator {
  Result calc_fu_han(Hand& hand,
                     const Melds& melds,
                     const Tile& winning_tile,
                     const Config& config,
                     unsigned int mode = 0u,
                     bool check = false);
}

#endif
