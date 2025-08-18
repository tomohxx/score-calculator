#include "parser.hpp"
#include <gtest/gtest.h>
using namespace score_calculator;

TEST(Parser, TestFromMPSZ)
{
  Hand hand1;
  Melds melds1;

  const Hand hand2{{m1, m2, m3, m4, m0, m5, m6, m7, m8, m9, p1, p2, p3, s1, s2, s3}};
  const Melds melds2{
      {MeldType::PON, {m1, m1, m1}},
      {MeldType::CHI, {m4, m5, m6}},
      {MeldType::MINKAN, {s9, s9, s9, s9}},
      {MeldType::ANKAN, {z1, z1, z1, z1}},
  };

  from_mpsz("1234056789m123p123s[111m][456m][9999s][[1111z]]", hand1, melds1);

  EXPECT_EQ(hand1, hand2);
  EXPECT_EQ(melds1, melds2);
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

  const auto str_mpsz = to_mpsz(hand, melds);

  EXPECT_EQ(str_mpsz, "1234056789m123p123s[111m][456m][9999s][[1111z]]");
}
