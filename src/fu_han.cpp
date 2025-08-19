#include "fu_han.hpp"
#include "winning_hand.hpp"
#include "yaku.hpp"
#include <cassert>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <utility>

namespace score_calculator {
  namespace internal {
    void validate(Hand& hand,
                  const Melds& melds,
                  const Tile& winning_tile,
                  const Config& config,
                  const bool check);

    namespace standard {
      Result calc_fu_han(const Blocks& closed_blocks,
                         const Blocks& open_blocks,
                         const Hand& whole_hand,
                         const Tile& winning_tile,
                         const Config& config,
                         bool is_open);
      std::pair<bool, Result> calc_fu_han(Hand& hand,
                                          const Blocks& open_blocks,
                                          const Hand& whole_hand,
                                          const Tile& winning_tile,
                                          const Config& config,
                                          bool is_open);
      std::pair<int, bool> calc_fu(Blocks& blocks, const Tile& winning_tile, const Config& config, bool is_open);
    }

    namespace seven_pairs {
      Result calc_fu_han(const Hand& hand, const Tile& winning_tile, const Config& config);
    }

    namespace thirteen_orphans {
      Result calc_fu_han(const Hand& hand, const Tile& winning_tile, const Config& config);
    }
  }

  using namespace internal;

  Result calc_fu_han(Hand& hand,
                     const Melds& melds,
                     const Tile& winning_tile,
                     const Config& config,
                     const int mode,
                     const bool check)
  {
    validate(hand, melds, winning_tile, config, check);

    // 副露フラグ
    const bool is_open = std::count_if(melds.begin(), melds.end(), [](const Meld& meld) {
      return meld.get_meld_type() != MeldType::ANKAN;
    });
    Blocks open_blocks{};
    Hand whole_hand{hand};

    for (const auto& meld : melds) {
      const auto min_index = meld.get_min_index();

      if (const auto meld_type = meld.get_meld_type();
          meld_type == MeldType::PON) {
        open_blocks[min_index].num_open_triplet = 1;
      }
      else if (meld_type == MeldType::CHI) {
        ++open_blocks[min_index].num_open_sequence;
      }
      else if (meld_type == MeldType::ANKAN) {
        open_blocks[min_index].num_closed_quad = 1;
      }
      else {
        open_blocks[min_index].num_open_quad = 1;
      }

      whole_hand.draw(meld.get_tiles());
    }

    if (check) {
      // 副露を含めた牌の枚数は0以上4以下でなければならない
      if (std::any_of(whole_hand.tiles.begin(),
                      whole_hand.tiles.end(),
                      [](const int x) { return x < 0 || x > 4; })) {
        throw std::invalid_argument("Invalid number of hand tiles");
      }
    }

    if (mode & 1) {
      return internal::standard::calc_fu_han(hand, open_blocks, whole_hand, winning_tile, config, is_open).second;
    }
    else if (mode & 2) {
      if (internal::seven_pairs::is_winning_hand(hand.tiles)) {
        return internal::seven_pairs::calc_fu_han(hand, winning_tile, config);
      }
    }
    else if (mode & 4) {
      if (internal::thirteen_orphans::is_winning_hand(hand.tiles)) {
        return internal::thirteen_orphans::calc_fu_han(hand, winning_tile, config);
      }
    }
    else {
      if (const auto [found, result] = internal::standard::calc_fu_han(hand, open_blocks, whole_hand, winning_tile, config, is_open); found) {
        return result;
      }
      else if (internal::seven_pairs::is_winning_hand(hand.tiles)) {
        return internal::seven_pairs::calc_fu_han(hand, winning_tile, config);
      }
      else if (internal::thirteen_orphans::is_winning_hand(hand.tiles)) {
        return internal::thirteen_orphans::calc_fu_han(hand, winning_tile, config);
      }

      throw std::invalid_argument("Not winnging hand");
    }

    std::unreachable();
  }

  namespace internal {
    void validate(Hand& hand,
                  const Melds& melds,
                  const Tile& winning_tile,
                  const Config& config,
                  const bool check)
    {
      // 手牌に和了牌が含まれていなければならない
      if (hand.tiles[winning_tile.index] <= 0) {
        throw std::invalid_argument("Winning tile is not in the hand");
      }

      // 副露数は4以下でなければならない
      if (melds.size() > 4u) {
        throw std::invalid_argument("Invalid number of called melds");
      }

      // ドラ表示牌の枚数は4以下でなければならない
      if (config.dora_indicators.size() > 4u) {
        throw std::invalid_argument("Invalid number of dora indicators");
      }

      // 裏ドラ表示牌の枚数は4以下でなければならない
      if (config.ura_dora_indicators.size() > 4u) {
        throw std::invalid_argument("Invalid number of ura-dora indicators");
      }

      // 抜きドラの枚数は0以上4以下でなければならない
      if (config.three_player && (config.num_nukidora < 0 || config.num_nukidora > 4)) {
        throw std::invalid_argument("Invalid number of nukidora");
      }

      if (check) {
        const auto num_melds = static_cast<int>(melds.size());

        // 純手牌の枚数は14 - 副露数 * 3でなければならない
        if (std::accumulate(hand.tiles.begin(), hand.tiles.end(), 0) != 14 - num_melds * 3) {
          throw std::invalid_argument("Invalid sum of hand tiles");
        }

        // 三人麻雀が有効のとき手牌に2mから8mが存在してはいけない
        if (config.three_player && std::accumulate(&hand.tiles[1], &hand.tiles[8], 0) != 0) {
          throw std::invalid_argument("Invalid tile");
        }

        // 副露タイプと牌構成に矛盾が存在してはいけない
        if (!std::all_of(melds.begin(), melds.end(), [](const Meld& meld) { return meld; })) {
          throw std::invalid_argument("Invalid meld");
        }
      }
    }

    Result standard::calc_fu_han(const Blocks& closed_blocks,
                                 const Blocks& open_blocks,
                                 const Hand& whole_hand,
                                 const Tile& winning_tile,
                                 const Config& config,
                                 const bool is_open)
    {
      Result result;

      Blocks all_blocks{closed_blocks};

      for (int tid = 0; tid < NUM_TIDS; ++tid) {
        *reinterpret_cast<unsigned int*>(&all_blocks[tid]) |= *reinterpret_cast<const unsigned int*>(&open_blocks[tid]);
      }

      const auto [num_fu, is_pinfu] = calc_fu(all_blocks, winning_tile, config, is_open);

      result.num_fu = num_fu;

      if (is_pinfu) {
        result.update_yaku(YakuId::PINFU, NUM_YAKU_PINFU);
      }

      calc_yaku(result, all_blocks, whole_hand, winning_tile, config, is_open);

      return result;
    }

    std::pair<bool, Result> standard::calc_fu_han(Hand& hand,
                                                  const Blocks& open_blocks,
                                                  const Hand& whole_hand,
                                                  const Tile& winning_tile,
                                                  const Config& config,
                                                  const bool is_open)
    {
      bool found = false;
      Result result;
      Blocks closed_blocks;

      find_winning_hand(hand.tiles, closed_blocks, [&]() {
        swap_blocks(closed_blocks, [&]() {
          const auto tmp = calc_fu_han(closed_blocks, open_blocks, whole_hand, winning_tile, config, is_open);

          result = std::max(std::move(result), std::move(tmp));
          found = true;
        });
      });

      return {found, result};
    }

    bool is_open_wait(const Blocks& blocks, const Tile& tile)
    {
      return tile < east && ((tile.index % 9 < 6 && blocks[tile.index].num_closed_sequence) ||
                             (tile.index % 9 > 2 && blocks[tile.index - 2].num_closed_sequence));
    }

    bool is_edge_wait(const Blocks& blocks, const Tile& tile)
    {
      return tile < east && ((tile.index % 9 == 6 && blocks[tile.index].num_closed_sequence) ||
                             (tile.index % 9 == 2 && blocks[tile.index - 2].num_closed_sequence));
    }

    bool is_closed_wait(const Blocks& blocks, const Tile& tile)
    {
      return tile < east && tile.index % 9 >= 1 && tile.index % 9 <= 7 && blocks[tile.index - 1].num_closed_sequence;
    }

    bool is_pair_wait(const Blocks& blocks, const Tile& tile)
    {
      return blocks[tile.index].num_pair;
    }

    bool is_dual_wait(const Blocks& blocks, const Tile& tile)
    {
      return blocks[tile.index].num_closed_triplet;
    }

    std::pair<int, bool> standard::calc_fu(Blocks& blocks, const Tile& winning_tile, const Config& config, const bool is_open)
    {
      int num_fu = 20; // 副底は20符

      // 面子の符を計算する
      for (int tid = 0; tid < NUM_TIDS; ++tid) {
        const int basic_fu = calc_basic_fu(blocks[tid]);

        num_fu += Tile{tid}.is_simple() ? basic_fu : basic_fu << 1;
      }

      // 雀頭の符を計算する(三元牌)
      if (exists_pair(blocks[white.index]) || exists_pair(blocks[green.index]) || exists_pair(blocks[red.index])) {
        num_fu += 2;
      }

      // 雀頭の符を計算する(風牌)
      if (config.is_2fu_double_wind) {
        num_fu += (exists_pair(blocks[static_cast<int>(config.seat_wind)]) || exists_pair(blocks[static_cast<int>(config.round_wind)]) ? 2 : 0);
      }
      else {
        num_fu += (exists_pair(blocks[static_cast<int>(config.seat_wind)]) ? 2 : 0);
        num_fu += (exists_pair(blocks[static_cast<int>(config.round_wind)]) ? 2 : 0);
      }

      // 両面待ちフラグ
      const bool is_open_wait_ = is_open_wait(blocks, winning_tile);
      // 平和フラグ
      const bool is_pinfu = (!is_open && num_fu == 20 && is_open_wait_);

      // 平和でないとき待ちの符を計算する
      if (!is_pinfu) {
        if (is_edge_wait(blocks, winning_tile) ||
            is_closed_wait(blocks, winning_tile) ||
            is_pair_wait(blocks, winning_tile)) {
          // 辺張待ち, 嵌張待ち, 単騎待ちは2符
          num_fu += 2;
        }
        else if (is_open_wait_) {
          // 両面待ちは0符
          // 両面待ちとシャンポン待ちを選択できるときは暗刻の符が付くため両面待ちを選択する方がよい
        }
        else {
          // シャンポン待ちは0符
          // ロン和了のとき暗刻を明刻にする
          if (!config.is_tsumo) {
            blocks[winning_tile.index].num_closed_triplet = 0;
            blocks[winning_tile.index].num_open_triplet = 1;
            num_fu -= (winning_tile.is_simple() ? 2 : 4);
          }
        }
      }

      // 自摸は2符(ただし平和を除く)
      if (config.is_tsumo && !is_pinfu) num_fu += 2;

      // 面前ロンは10符
      if (!is_open && !config.is_tsumo) num_fu += 10;

      // 食い平和ロンは10符
      if (is_open && !config.is_tsumo && num_fu == 20) num_fu += 10;

      // 符の一の位を切り上げる
      num_fu = (num_fu + 9) / 10 * 10;

      return {num_fu, is_pinfu};
    }

    Result seven_pairs::calc_fu_han(const Hand& hand, const Tile& winning_tile, const Config& config)
    {
      Result result;

      result.num_fu = NUM_FU_SEVEN_PAIRS;
      calc_yaku(result, hand, winning_tile, config);

      return result;
    }

    Result thirteen_orphans::calc_fu_han(const Hand& hand, const Tile& winning_tile, const Config& config)
    {
      Result result;

      result.num_fu = NUM_FU_THIRTEEN_ORPHANS;
      calc_yaku(result, hand, winning_tile, config);

      return result;
    }
  }
}
