#include "meld.hpp"
#include <stdexcept>

namespace score_calculator {
  bool is_pon(const Tiles& tiles)
  {
    return tiles.size() == 3u &&
           tiles[0].index == tiles[1].index &&
           tiles[0].index == tiles[2].index;
  }

  bool is_chi(const Tiles& tiles)
  {
    return tiles.size() == 3u &&
           tiles[0].index < 27 &&
           tiles[0].index % 9 < 7 &&
           tiles[0].index + 1 == tiles[1].index &&
           tiles[0].index + 2 == tiles[2].index;
  }

  bool is_kan(const Tiles& tiles)
  {
    return tiles.size() == 4u &&
           tiles[0].index == tiles[1].index &&
           tiles[0].index == tiles[2].index &&
           tiles[0].index == tiles[3].index;
  }

  Meld::operator bool() const
  {
    return (meld_type == MeldType::PON && is_pon(tiles)) ||
           (meld_type == MeldType::CHI && is_chi(tiles)) ||
           (meld_type == MeldType::MINKAN && is_kan(tiles)) ||
           (meld_type == MeldType::ANKAN && is_kan(tiles));
  }

  namespace internal {
    Meld make_pon_chi_minkan(const Tiles& tiles)
    {
      if (is_pon(tiles)) {
        return {MeldType::PON, tiles};
      }
      else if (is_chi(tiles)) {
        return {MeldType::CHI, tiles};
      }
      else if (is_kan(tiles)) {
        return {MeldType::MINKAN, tiles};
      }
      else {
        throw std::invalid_argument("Invalid tiles");
      }
    }

    Meld make_ankan(const Tiles& tiles)
    {
      if (is_kan(tiles)) {
        return {MeldType::ANKAN, tiles};
      }
      else {
        throw std::invalid_argument("Invalid tiles");
      }
    }
  }
}
