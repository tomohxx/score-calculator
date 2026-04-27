#include <gtest/gtest.h>
#include <mahjong/score_calculator.hpp>
using namespace mahjong::score_calculator;

TEST(Parser, TestFromMPSZ1)
{
  const auto [hand1, melds1] = from_mpsz("1234r556789m123p123s[111m][456m][9999s][[1111z]]");
  const Hand hand2{{m1, m2, m3, m4, m0, m5, m6, m7, m8, m9, p1, p2, p3, s1, s2, s3}};
  const Melds melds2{
      {MeldType::PON, {m1, m1, m1}},
      {MeldType::CHI, {m4, m5, m6}},
      {MeldType::MINKAN, {s9, s9, s9, s9}},
      {MeldType::ANKAN, {z1, z1, z1, z1}},
  };

  EXPECT_EQ(hand1, hand2);
  EXPECT_EQ(melds1, melds2);
}

TEST(Parser, TestFromMPSZ2)
{
  EXPECT_THROW(from_mpsz("1234r556789m123p123s[[111m][456m][9999s][[1111z]]"), std::invalid_argument);
}

TEST(Parser, TestFromMPSZ3)
{
  EXPECT_THROW(from_mpsz("1234r556789m123p123s[111m[456m][9999s][[1111z]]"), std::invalid_argument);
}

TEST(Parser, TestFromMPSZ4)
{
  EXPECT_THROW(from_mpsz("1234r556789m123p123sX[111m]X[456m]X[9999s]X[[1111z]]"), std::invalid_argument);
}

TEST(Parser, TestToMPSZ)
{
  const Hand hand{{m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, p1, p2, p3, s1, s2, s3}};
  const Melds melds{
      {MeldType::PON, {m1, m1, m1}},
      {MeldType::CHI, {m4, m5, m6}},
      {MeldType::MINKAN, {s9, s9, s9, s9}},
      {MeldType::ANKAN, {z1, z1, z1, z1}},
  };

  const auto mpsz_regular = parser::regular::to_mpsz(hand, melds);
  const auto mpsz_tenhou = parser::tenhou::to_mpsz(hand, melds);

  EXPECT_EQ(mpsz_regular, "1234r556789m123p123s[111m][456m][9999s][[1111z]]");
  EXPECT_EQ(mpsz_tenhou, "1234056789m123p123s[111m][456m][9999s][[1111z]]");
}
