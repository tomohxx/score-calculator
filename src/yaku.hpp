#ifndef SCORE_CALCULATOR_YAKU_HPP
#define SCORE_CALCULATOR_YAKU_HPP

#include "config.hpp"
#include "hand.hpp"
#include "result.hpp"
#include "types.hpp"

namespace score_calculator::internal {
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
