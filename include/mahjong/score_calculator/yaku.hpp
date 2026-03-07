#ifndef MAHJONG_SCORE_CALCULATOR_YAKU_HPP
#define MAHJONG_SCORE_CALCULATOR_YAKU_HPP

#include <mahjong/score_calculator/config.hpp>
#include <mahjong/score_calculator/hand.hpp>
#include <mahjong/score_calculator/result.hpp>
#include <mahjong/score_calculator/types.hpp>

namespace mahjong::score_calculator::internal {
  namespace standard {
    void calc_yaku(Result& result, const Blocks& blocks, const Hand& hand, const Tile& winning_tile, const Config& config, bool is_open);
  }

  namespace seven_pairs {
    void calc_yaku(Result& result, const Hand& hand, const Tile& winning_tile, const Config& config);
  }

  namespace thirteen_orphans {
    void calc_yaku(Result& result, const Hand& hand, const Tile& winning_tile, const Config& config);
  }
}

#endif
