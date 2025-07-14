#ifndef SCORE_CALCULATOR_MELD_HPP
#define SCORE_CALCULATOR_MELD_HPP

#include "tile.hpp"
#include <vector>

namespace score_calculator {
  class Meld {
  private:
    MeldType meld_type;
    Tiles tiles;
    int min_index;

  public:
    Meld(const MeldType& meld_type, const Tiles& tiles) : meld_type(meld_type), tiles(tiles)
    {
      min_index = std::min_element(tiles.begin(), tiles.end())->index;
    }

    const MeldType& get_meld_type() const { return meld_type; }
    const Tiles& get_tiles() const { return tiles; }
    const int& get_min_index() const { return min_index; }

    bool operator==(const Meld& rhs) const { return meld_type == rhs.meld_type && tiles == rhs.tiles; }
  };

  using Melds = std::vector<Meld>;
}

#endif
