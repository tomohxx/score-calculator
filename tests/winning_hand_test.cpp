#include "hand.hpp"
#include "winning_hand.hpp"
#include <gtest/gtest.h>
using namespace score_calculator;
using internal::Blocks;

// 3N和了判定
TEST(WinningHand, TestDetailIsWinningHand)
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, s9, s9}};
  Blocks blocks;

  EXPECT_TRUE(internal::standard::detail::is_winning_hand(std::span(hand.tiles).subspan(0, 9), std::span(blocks).subspan(0, 9)));
  EXPECT_TRUE(internal::standard::detail::is_winning_hand(std::span(hand.tiles).subspan(9, 9), std::span(blocks).subspan(9, 9)));
}

// 3N+2和了判定
TEST(WinningHand, TestDetailFindWinningHand)
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, s9, s9}};
  Blocks blocks;
  bool found = false;

  internal::standard::detail::find_winning_hand(std::span(hand.tiles).subspan(18, 9),
                                                std::span(blocks).subspan(18, 9),
                                                [&found]() { found = true; });

  EXPECT_TRUE(found);
}

// 和了判定(数牌雀頭)
TEST(WinningHand, TestWinningHandWithSuitsPair)
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, s9, s9}};
  Blocks blocks{};
  bool found = false;

  internal::standard::find_winning_hand(hand.tiles, blocks, [&found]() { found = true; });

  EXPECT_TRUE(found);
}

// 和了判定(字牌雀頭)
TEST(WinningHand, TestWinningHandWithHonorTilePair)
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, z4, z4}};
  Blocks blocks{};
  bool found = false;

  internal::standard::find_winning_hand(hand.tiles, blocks, [&found]() { found = true; });

  EXPECT_TRUE(found);
}

// 和了判定(雀頭不定)
TEST(WinningHand, TestCannotDeterminatePair)
{
  Hand hand{{m1, m1, m2, m2, m3, m3, m4, m4, m7, m8, m9, p2, p3, p4}};
  Blocks blocks{};
  int cnt = 0;

  internal::standard::find_winning_hand(hand.tiles, blocks, [&cnt]() { ++cnt; });

  EXPECT_EQ(cnt, 2);
}

// 和了判定(面子不定)
TEST(WinningHand, TestCannotDeterminateMeld)
{
  Hand hand{{m1, m1, m1, m2, m2, m2, m3, m3, m3, p2, p3, p4, z4, z4}};
  Blocks blocks{};
  int cnt = 0;

  internal::standard::find_winning_hand(hand.tiles, blocks, [&cnt, &blocks]() {
    internal::standard::swap_blocks(blocks, [&cnt]() { ++cnt; });
  });

  EXPECT_EQ(cnt, 2);
}
