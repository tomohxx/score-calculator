#ifndef MAHJONG_SCORE_CALCULATOR_HAND_HPP
#define MAHJONG_SCORE_CALCULATOR_HAND_HPP

#include <algorithm>
#include <cassert>
#include <mahjong/score_calculator/meld.hpp>
#include <mahjong/score_calculator/tile.hpp>
#include <mahjong/score_calculator/types.hpp>
#include <numeric>
#include <string>
#include <utility>

namespace mahjong::score_calculator {
  struct Hand {
    Arr tiles{};
    Arr red_dora{};

    Hand() : tiles{{}}, red_dora{{}} {}
    Hand(const Arr& tiles, const Arr& red_dora)
        : tiles{tiles}, red_dora{red_dora} {}
    explicit Hand(const std::vector<int>& tiles) { std::copy(tiles.begin(), tiles.end(), this->tiles.begin()); }
    explicit operator std::vector<int>() const { return std::vector<int>(tiles.begin(), tiles.end()); }
    bool operator==(const Hand& rhs) const { return tiles == rhs.tiles && red_dora == rhs.red_dora; }
    const std::array<int, NUM_TIDS>& as_array() const { return tiles; }

    auto draw(this auto&& self, const Tile& tile) -> decltype(auto)
    {
      assert(self.tiles[tile.index] < 4);

      ++self.tiles[tile.index];
      if (tile.is_red) ++self.red_dora[tile.index];

      return std::forward<decltype(self)>(self);
    }

    auto discard(this auto&& self, const Tile& tile) -> decltype(auto)
    {
      assert(self.tiles[tile.index] > 0);

      --self.tiles[tile.index];
      if (tile.is_red) --self.red_dora[tile.index];

      return std::forward<decltype(self)>(self);
    }

    auto draw(this auto&& self, const Tiles& tiles) -> decltype(auto)
    {
      std::for_each(tiles.cbegin(), tiles.cend(), [&self](const Tile& tile) { self.draw(tile); });

      return std::forward<decltype(self)>(self);
    }

    auto discard(this auto&& self, const Tiles& tiles) -> decltype(auto)
    {
      std::for_each(tiles.cbegin(), tiles.cend(), [&self](const Tile& tile) { self.discard(tile); });

      return std::forward<decltype(self)>(self);
    }

    auto draw(this auto&& self, const Tile& tile, const std::size_t n) -> decltype(auto)
    {
      for (std::size_t i = 0u; i < n; ++i) {
        self.draw(tile);
      }

      return std::forward<decltype(self)>(self);
    }

    auto discard(this auto&& self, const Tile& tile, const std::size_t n) -> decltype(auto)
    {
      for (std::size_t i = 0u; i < n; ++i) {
        self.discard(tile);
      }

      return std::forward<decltype(self)>(self);
    }

    auto draw(this auto&& self, const Hand& hand) -> decltype(auto)
    {
      for (int tid = 0; tid < NUM_TIDS; ++tid) {
        self.tiles[tid] += hand.tiles[tid];
        self.red_dora[tid] += hand.red_dora[tid];
      }

      return std::forward<decltype(self)>(self);
    }

    auto discard(this auto&& self, const Hand& hand) -> decltype(auto)
    {
      for (int tid = 0; tid < NUM_TIDS; ++tid) {
        self.tiles[tid] -= hand.tiles[tid];
        self.red_dora[tid] -= hand.red_dora[tid];
      }

      return std::forward<decltype(self)>(self);
    }

    auto draw(this auto&& self, const Melds& melds) -> decltype(auto)
    {
      for (const auto& meld : melds) {
        self.draw(meld.get_tiles());
      }

      return std::forward<decltype(self)>(self);
    }

    auto discard(this auto&& self, const Melds& melds) -> decltype(auto)
    {
      for (const auto& meld : melds) {
        self.discard(meld.get_tiles());
      }

      return std::forward<decltype(self)>(self);
    }

    bool has_tile(const int index) const { return tiles[index] > red_dora[index]; }
    bool has_red_dora(const int index) const { return red_dora[index] > 0; }
    bool has_tile(const Tile& tile) const { return tile.is_red ? has_red_dora(tile.index) : has_tile(tile.index); }
    int get_num_tile(const int index) const { return tiles[index] - red_dora[index]; }
    int get_num_red_dora(const int index) const { return red_dora[index]; }
    int get_num_tile(const Tile& tile) const { return tile.is_red ? get_num_red_dora(tile.index) : get_num_tile(tile.index); }
    int calc_sum() const { return std::accumulate(tiles.begin(), tiles.end(), 0); }

    explicit Hand(const Tiles& tiles) { draw(tiles); }
    explicit operator std::string() const;
  };
}

#endif
