#ifndef SCORE_CALCULATOR_HAND_HPP
#define SCORE_CALCULATOR_HAND_HPP

#include "tile.hpp"
#include "types.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <utility>

namespace score_calculator {
  struct Hand {
    Arr tiles{};
    Arr red_dora{};

    Hand() : tiles{{}}, red_dora{{}} {}
    Hand(const Arr& tiles, const Arr& red_dora)
        : tiles{tiles}, red_dora{red_dora} {}
    explicit Hand(const std::vector<int>& tiles) { std::copy(tiles.begin(), tiles.end(), this->tiles.begin()); }
    explicit operator std::vector<int>() { return std::vector<int>(tiles.begin(), tiles.end()); }
    bool operator==(const Hand& rhs) const { return tiles == rhs.tiles && red_dora == rhs.red_dora; }

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

    explicit Hand(const Tiles& tiles) { draw(tiles); }
  };
}

#endif
