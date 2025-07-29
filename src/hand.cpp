#include "hand.hpp"
#include <cassert>

namespace score_calculator {
  Hand& Hand::draw(const Tile& tile)
  {
    assert(tiles[tile.index] < 4);

    ++tiles[tile.index];
    if (tile.is_red) ++red_dora[tile.index];

    return *this;
  }

  Hand& Hand::discard(const Tile& tile)
  {
    assert(tiles[tile.index] > 0);

    --tiles[tile.index];
    if (tile.is_red) --red_dora[tile.index];

    return *this;
  }

  Hand& Hand::draw(const Tiles& tiles)
  {
    std::for_each(tiles.begin(), tiles.end(), [this](const Tile& tile) { draw(tile); });

    return *this;
  }

  Hand& Hand::discard(const Tiles& tiles)
  {
    std::for_each(tiles.begin(), tiles.end(), [this](const Tile& tile) { discard(tile); });

    return *this;
  }
}
