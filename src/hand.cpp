#include "hand.hpp"
#include <cassert>

namespace score_calculator {
  Hand& Hand::draw(const Tile& tile)
  {
    assert(tiles[tile] < 4);

    ++tiles[tile];
    if (tile.is_red) ++red_dora[tile];

    return *this;
  }

  Hand& Hand::discard(const Tile& tile)
  {
    assert(tiles[tile] > 0);

    --tiles[tile];
    if (tile.is_red) --red_dora[tile];

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
