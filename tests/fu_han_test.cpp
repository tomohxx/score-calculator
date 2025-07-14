#include "core.hpp"
#include "score.hpp"
#include <gtest/gtest.h>
using namespace score_calculator;

// 不正な和了牌
TEST(FuHan, TestInvalidWinningTile)
{
  Hand hand;

  Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  EXPECT_THROW(calc_fu_han(hand, {}, m1, config, 0), std::invalid_argument);
}

// 平和ツモ
TEST(FuHan, TestPinfuTsumo)
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, z4, z4}};

  Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = true,
  };

  const auto result = calc_fu_han(hand, {}, m1, config);

  EXPECT_EQ(result.num_fu, 20);
  EXPECT_EQ(result.num_han, 2);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::PINFU), 1);
}

// 平和ロン
TEST(FuHan, TestPinfuRon)
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, z4, z4}};

  Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, {}, m1, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::PINFU), 1);
}

// 食い平和ツモ
TEST(FuHan, TestOpenTanyaoTsumo)
{
  Hand hand{{m6, m7, m8, s5, s6, s7, s8, s8}};
  Melds melds{{MeldType::CHI, {m2, m3, m4}}, {MeldType::CHI, {p2, p3, p4}}};

  Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = true,
  };

  const auto result = calc_fu_han(hand, melds, m8, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::TANYAOCHUU), 1);
}

// 食い平和ロン
TEST(FuHan, TestOpenTanyaoRon)
{
  Hand hand{{m6, m7, m8, s5, s6, s7, s8, s8}};
  Melds melds{{MeldType::CHI, {m2, m3, m4}}, {MeldType::CHI, {p2, p3, p4}}};

  Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, melds, m8, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::TANYAOCHUU), 1);
}

// 七対子
TEST(FuHan, TestChiitoitsu)
{
  Hand hand{{m1, m1, m3, m3, m5, m5, m7, m7, m9, m9, p1, p1, p3, p3}};

  Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, {}, m1, config);

  EXPECT_EQ(result.num_fu, 25);
  EXPECT_EQ(result.num_han, 2);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::CHIITOITSU), 2);
}

TEST(FuHan, TestYakuhaiRed)
{
  Hand hand{{m3, m4, m5, p5, p6, p7, s5, s5, s5, s9, s9, z7, z7, z7}};

  Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::WEST,
      .is_tsumo = true,
  };

  const auto result = calc_fu_han(hand, {}, z7, config);

  EXPECT_EQ(result.num_fu, 40);
  EXPECT_EQ(result.num_han, 2);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::MENZENCHIN_TSUMOHOU), 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::YAKUHAI_RED), 1);
}

TEST(FuHan, TestYakuhaiRedPon)
{
  Hand hand{{m5, m6, m7, p2, p3, p4, p8, p8, s5, s6, s7}};
  Melds melds{{MeldType::PON, {z7, z7, z7}}};

  Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::EAST,
      .is_tsumo = true,
  };

  const auto result = calc_fu_han(hand, melds, p3, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::YAKUHAI_RED), 1);
}

// 平和(単騎待ちではない)
TEST(FuHan, TestPinfuNotPairWait)
{
  Hand hand{{m5, m6, m7, p3, p4, p5, p7, p8, p9, s6, s6, s6, s7, s8}};

  Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, {}, s6, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::PINFU), 1);
}

// 平和(嵌張待ちではない)
TEST(FuHan, TestPinfuNotClosedWait)
{
  Hand hand{{m1, m1, m2, m2, m3, m3, m4, m4, p3, p4, p5, s6, s7, s8}};

  Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, {}, m2, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 2);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::PINFU), 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::IIPEIKOU), 1);
}

// 平和(辺張待ちではない)
TEST(FuHan, TestPinfuNotEdgeWait)
{
  Hand hand{{m1, m2, m3, m3, m4, m5, p3, p4, p5, s6, s7, s8, z2, z2}};

  Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, {}, m3, config);

  EXPECT_EQ(result.num_fu, 30);
  EXPECT_EQ(result.num_han, 1);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::PINFU), 1);
}

// 混一色(食い下がり)
TEST(FuHan, TestHoniisouKuisagari)
{
  Hand hand{{p4, p5, p6, z1, z1}};
  Melds melds{{MeldType::PON, {p8, p8, p8}}, {MeldType::PON, {z7, z7, z7}}, {MeldType::PON, {p6, p6, p6}}};

  Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  const auto result = calc_fu_han(hand, melds, p4, config);

  EXPECT_EQ(result.num_fu, 40);
  EXPECT_EQ(result.num_han, 3);
  EXPECT_EQ(result.reasons_yaku.at(YakuId::HONIISOU), 2);
}
