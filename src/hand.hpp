#ifndef SCORE_CALCULATOR_HAND_HPP
#define SCORE_CALCULATOR_HAND_HPP

#include "tile.hpp"
#include "types.hpp"
#include <algorithm>
#include <array>

namespace score_calculator {
  struct Hand {
    Arr tiles{};
    Arr red_dora{};

    Hand() : tiles{{}}, red_dora{{}} {}
    Hand(const Arr& tiles, const Arr& red_dora)
        : tiles{tiles}, red_dora{red_dora} {}
    explicit Hand(const Tiles& tiles) { draw(tiles); }
    explicit Hand(const std::vector<int>& tiles) { std::copy(tiles.begin(), tiles.end(), this->tiles.begin()); }

    Hand& draw(const Tile& tile);
    Hand& discard(const Tile& tile);
    Hand& draw(const Tiles& tiles);
    Hand& discard(const Tiles& tiles);

    bool operator==(const Hand& rhs) const { return tiles == rhs.tiles && red_dora == rhs.red_dora; }
  };
}

#endif
