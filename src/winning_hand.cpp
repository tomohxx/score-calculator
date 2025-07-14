#include "winning_hand.hpp"
#include <cassert>
#include <numeric>

namespace score_calculator::internal {
  void standard::find_winning_hand(Arr& tiles, Blocks& blocks, std::function<void()> on_success)
  {
    int pos_pair = -1;

    for (int i = 0; i < 3; ++i) {
      if (const int r = std::accumulate(&tiles[9 * i], &tiles[9 * i + 9], 0) % 3; r == 1) {
        return;
      }
      else if (r == 2 && pos_pair == -1) {
        pos_pair = i;
      }
      else if (r == 2 && pos_pair != -1) {
        return;
      }
    }

    for (int i = 27; i < NUM_TIDS; ++i) {
      if (const int n = tiles[i]; n == 3) {
        blocks[i].num_closed_triplet = 1;
      }
      else if (n == 1 || n == 4) {
        return;
      }
      else if (n == 2 && pos_pair == -1) {
        pos_pair = i;
        blocks[i].num_pair = 1;
      }
      else if (n == 2 && pos_pair != -1) {
        return;
      }
    }

    for (int i = 0; i < 3; ++i) {
      if (i == pos_pair) continue;
      if (!detail::is_winning_hand(std::span(tiles).subspan(9 * i, 9),
                                   std::span(blocks).subspan(9 * i, 9))) return;
    }

    if (pos_pair < 27) {
      detail::find_winning_hand(std::span(tiles).subspan(9 * pos_pair, 9),
                                std::span(blocks).subspan(9 * pos_pair, 9), on_success);
    }
    else on_success();
  }

  void standard::swap_blocks(Blocks& blocks, std::function<void()> on_success)
  {
    on_success();

    for (int i = 0; i < 3; ++i) {
      for (int j = 9 * i; j < 9 * i + 7; ++j) {
        if (blocks[j].num_closed_triplet && blocks[j + 1].num_closed_triplet && blocks[j + 2].num_closed_triplet) {

          blocks[j].num_closed_triplet = 0;
          blocks[j + 1].num_closed_triplet = 0;
          blocks[j + 2].num_closed_triplet = 0;
          blocks[j].num_closed_sequence += 3;
          on_success();
          blocks[j].num_closed_triplet = 1;
          blocks[j + 1].num_closed_triplet = 1;
          blocks[j + 2].num_closed_triplet = 1;
          blocks[j].num_closed_sequence -= 3;
          break;
        }
      }
    }
  }

  bool seven_pairs::is_winning_hand(const Arr& tiles)
  {
    int num_pair = 0;

    for (int i = 0; i < NUM_TIDS; ++i) {
      if (tiles[i] == 2) ++num_pair;
    }

    return num_pair == 7;
  }

  bool thirteen_orphans::is_winning_hand(const Arr& tiles)
  {
    int num_pair = 0;
    int num_kind = 0;

    for (const int i : {0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33}) {
      if (tiles[i] > 0) {
        ++num_kind;
        if (tiles[i] >= 2) ++num_pair;
      }
    }

    return num_kind == 13 && num_pair == 1;
  }

  namespace standard::detail {
    bool is_winning_hand(std::span<int> tiles, std::span<Block> blocks)
    {
      assert(tiles.size() == 9u);
      assert(blocks.size() == 9u);

      int a = tiles[0], b = tiles[1];

      for (int i = 0; i < 7; ++i) {
        if (a >= 3) {
          a -= 3;
          blocks[i].num_closed_triplet = 1;
        }

        if (const int r = a; b >= r && tiles[i + 2] >= r) {
          a = b - r;
          b = tiles[i + 2] - r;
          blocks[i].num_closed_sequence += r;
        }
        else return false;
      }

      if (a == 3) {
        a = 0;
        blocks[7].num_closed_triplet = 1;
      }

      if (b == 3) {
        b = 0;
        blocks[8].num_closed_triplet = 1;
      }

      return a == 0 && b == 0;
    }

    void find_winning_hand(std::span<int> tiles, std::span<Block> blocks, std::function<void()> on_success)
    {
      assert(tiles.size() == 9u);
      assert(blocks.size() == 9u);

      int s = 0;

      for (int i = 0; i < 9; ++i) {
        s += i * tiles[i];
      }

      for (int p = s * 2 % 3; p < 9; p += 3) {
        if (tiles[p] >= 2) {
          tiles[p] -= 2;
          std::fill(blocks.begin(), blocks.end(), Block{});

          if (is_winning_hand(tiles, blocks)) {
            tiles[p] += 2;
            blocks[p].num_pair = 1;
            on_success();
          }
          else tiles[p] += 2;
        }
      }
    }
  }
}
