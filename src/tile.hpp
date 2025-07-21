#ifndef SCORE_CALCULATOR_TILE_HPP
#define SCORE_CALCULATOR_TILE_HPP

#include <utility>
#include <vector>

namespace score_calculator {
  struct Tile {
    int index{};
    bool is_red{};

    constexpr Tile(const int index) : index(index), is_red(false) {}
    constexpr Tile(const int index, const bool is_red) : index(index), is_red(is_red) {}
    constexpr Tile(const std::pair<int, bool>& tile) : index(tile.first), is_red(tile.second) {}

    bool operator==(const Tile& tile) const { return index == tile.index; }
    bool operator<(const Tile& tile) const { return index < tile.index; }
    bool operator>(const Tile& tile) const { return index > tile.index; }

    constexpr operator int() const { return index; }

    bool is_suits() const { return index < 27; }
    bool is_simple() const { return index < 27 && index % 9 % 8 != 0; }
    bool is_terminal() const { return index < 27 && index % 9 % 8 == 0; }
    bool is_honor() const { return !is_suits(); }
    bool is_terminal_or_honor() const { return !is_simple(); }
  };

  using Tiles = std::vector<Tile>;

  inline constexpr Tile m1{0};
  inline constexpr Tile m2{1};
  inline constexpr Tile m3{2};
  inline constexpr Tile m4{3};
  inline constexpr Tile m5{4};
  inline constexpr Tile m6{5};
  inline constexpr Tile m7{6};
  inline constexpr Tile m8{7};
  inline constexpr Tile m9{8};
  inline constexpr Tile p1{9};
  inline constexpr Tile p2{10};
  inline constexpr Tile p3{11};
  inline constexpr Tile p4{12};
  inline constexpr Tile p5{13};
  inline constexpr Tile p6{14};
  inline constexpr Tile p7{15};
  inline constexpr Tile p8{16};
  inline constexpr Tile p9{17};
  inline constexpr Tile s1{18};
  inline constexpr Tile s2{19};
  inline constexpr Tile s3{20};
  inline constexpr Tile s4{21};
  inline constexpr Tile s5{22};
  inline constexpr Tile s6{23};
  inline constexpr Tile s7{24};
  inline constexpr Tile s8{25};
  inline constexpr Tile s9{26};
  inline constexpr Tile z1{27};
  inline constexpr Tile z2{28};
  inline constexpr Tile z3{29};
  inline constexpr Tile z4{30};
  inline constexpr Tile z5{31};
  inline constexpr Tile z6{32};
  inline constexpr Tile z7{33};
  inline constexpr Tile m5r{4, true};
  inline constexpr Tile p5r{13, true};
  inline constexpr Tile s5r{22, true};
  inline constexpr Tile m0{m5r};
  inline constexpr Tile p0{p5r};
  inline constexpr Tile s0{s5r};
  inline constexpr Tile east{z1};
  inline constexpr Tile south{z2};
  inline constexpr Tile west{z3};
  inline constexpr Tile north{z4};
  inline constexpr Tile white{z5};
  inline constexpr Tile green{z6};
  inline constexpr Tile red{z7};

  namespace literals {
    inline Tile operator"" _m(unsigned long long index)
    {
      return index == 0 ? m5r : Tile{static_cast<int>(index) - 1};
    }

    inline Tile operator"" _p(unsigned long long index)
    {
      return index == 0 ? p5r : Tile{static_cast<int>(index) - 1 + 9};
    }

    inline Tile operator"" _s(unsigned long long index)
    {
      return index == 0 ? s5r : Tile{static_cast<int>(index) - 1 + 18};
    }

    inline Tile operator"" _z(unsigned long long index)
    {
      return index - 1 + 27;
    }

    inline Tile operator"" _mr(unsigned long long index)
    {
      return {static_cast<int>(index) - 1, true};
    }

    inline Tile operator"" _pr(unsigned long long index)
    {
      return {static_cast<int>(index) - 1 + 9, true};
    }

    inline Tile operator"" _sr(unsigned long long index)
    {
      return {static_cast<int>(index) - 1 + 18, true};
    }
  }
}

#endif
