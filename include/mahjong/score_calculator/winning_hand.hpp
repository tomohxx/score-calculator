#ifndef MAHJONG_SCORE_CALCULATOR_DECOMPOSE_HPP
#define MAHJONG_SCORE_CALCULATOR_DECOMPOSE_HPP

#include <functional>
#include <mahjong/score_calculator/types.hpp>
#include <span>

namespace mahjong::score_calculator::internal {
  namespace standard {
    namespace detail {
      bool is_winning_hand(std::span<int> tiles, std::span<Block> blocks);
      void find_winning_hand(std::span<int> tiles, std::span<Block> blocks, std::function<void()> on_success);
    }

    void find_winning_hand(Arr& tiles, Blocks& blocks, std::function<void()> on_success);
    void swap_blocks(Blocks& blocks, std::function<void()> on_success);
  }

  namespace seven_pairs {
    bool is_winning_hand(const Arr& tiles);
  }

  namespace thirteen_orphans {
    bool is_winning_hand(const Arr& tiles);
  }
}

#endif
