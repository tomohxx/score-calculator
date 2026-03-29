#include <mahjong/score_calculator/tile.hpp>
#include <unordered_map>

namespace mahjong::score_calculator {
  const std::unordered_map<std::string, Tile> tile_from_string = {
      {"1m", m1},
      {"2m", m2},
      {"3m", m3},
      {"4m", m4},
      {"5m", m5},
      {"6m", m6},
      {"7m", m7},
      {"8m", m8},
      {"9m", m9},
      {"1p", p1},
      {"2p", p2},
      {"3p", p3},
      {"4p", p4},
      {"5p", p5},
      {"6p", p6},
      {"7p", p7},
      {"8p", p8},
      {"9p", p9},
      {"1s", s1},
      {"2s", s2},
      {"3s", s3},
      {"4s", s4},
      {"5s", s5},
      {"6s", s6},
      {"7s", s7},
      {"8s", s8},
      {"9s", s9},
      {"1z", z1},
      {"2z", z2},
      {"3z", z3},
      {"4z", z4},
      {"5z", z5},
      {"6z", z6},
      {"7z", z7},
      {"r5m", m5r},
      {"r5p", p5r},
      {"r5s", s5r},
  };

  Tile Tile::make_tile(const std::string& mpsz)
  {
    return tile_from_string.at(mpsz);
  }
}
