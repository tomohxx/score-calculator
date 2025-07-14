#include "core.hpp"
#include <gtest/gtest.h>
using namespace score_calculator;

struct TestRonParam {
  int num_hu;
  int num_han;
  int correct_payment;
};

struct TestTsumoParam {
  int num_hu;
  int num_han;
  int correct_payment1;
  int correct_payment2;
};

class TestNonDealerRon : public ::testing::TestWithParam<TestRonParam> {};
class TestDealerRon : public ::testing::TestWithParam<TestRonParam> {};
class TestNonDealerTsumo : public ::testing::TestWithParam<TestTsumoParam> {};
class TestDealerTsumo : public ::testing::TestWithParam<TestTsumoParam> {};

TEST_P(TestNonDealerRon, Test)
{
  const auto [num_hu, num_han, correct_payment] = GetParam();
  const Result result{.num_fu = num_hu, .num_han = num_han};
  const Config config{.seat_wind = WindType::SOUTH, .round_wind = WindType::EAST, .is_tsumo = false};

  const auto payment = static_cast<const RonPayment&&>(*calc_payment(result, config));

  EXPECT_EQ(payment.payment, correct_payment);
}

TEST_P(TestDealerRon, Test)
{
  const auto [num_hu, num_han, correct_payment] = GetParam();
  const Result result{.num_fu = num_hu, .num_han = num_han};
  const Config config{.seat_wind = WindType::EAST, .round_wind = WindType::EAST, .is_tsumo = false};

  const auto payment = static_cast<const RonPayment&&>(*calc_payment(result, config));

  EXPECT_EQ(payment.payment, correct_payment);
}

TEST_P(TestNonDealerTsumo, Test)
{
  const auto [num_hu, num_han, correct_payment1, correct_payment2] = GetParam();
  const Result result{.num_fu = num_hu, .num_han = num_han};
  const Config config{.seat_wind = WindType::SOUTH, .round_wind = WindType::EAST, .is_tsumo = true};

  const auto payment = static_cast<const TsumoPayment&&>(*calc_payment(result, config));

  EXPECT_EQ(payment.payment1, correct_payment1);
  EXPECT_EQ(payment.payment2, correct_payment2);
}

TEST_P(TestDealerTsumo, Test)
{
  const auto [num_hu, num_han, correct_payment1, correct_payment2] = GetParam();
  const Result result{.num_fu = num_hu, .num_han = num_han};
  const Config config{.seat_wind = WindType::EAST, .round_wind = WindType::EAST, .is_tsumo = true};

  const auto payment = static_cast<const TsumoPayment&&>(*calc_payment(result, config));

  EXPECT_EQ(payment.payment1, correct_payment1);
  EXPECT_EQ(payment.payment2, correct_payment2);
}

// 子のロン和了のテスト
INSTANTIATE_TEST_SUITE_P(
    Score, TestNonDealerRon,
    testing::Values(
        TestRonParam(30, 1, 1000),
        TestRonParam(40, 1, 1300),
        TestRonParam(50, 1, 1600),
        TestRonParam(60, 1, 2000),
        TestRonParam(70, 1, 2300),
        TestRonParam(80, 1, 2600),
        TestRonParam(90, 1, 2900),
        TestRonParam(100, 1, 3200),
        TestRonParam(110, 1, 3600),
        TestRonParam(25, 2, 1600),
        TestRonParam(30, 2, 2000),
        TestRonParam(40, 2, 2600),
        TestRonParam(50, 2, 3200),
        TestRonParam(60, 2, 3900),
        TestRonParam(70, 2, 4500),
        TestRonParam(80, 2, 5200),
        TestRonParam(90, 2, 5800),
        TestRonParam(100, 2, 6400),
        TestRonParam(110, 2, 7100),
        TestRonParam(25, 3, 3200),
        TestRonParam(30, 3, 3900),
        TestRonParam(40, 3, 5200),
        TestRonParam(50, 3, 6400),
        TestRonParam(60, 3, 7700),
        TestRonParam(70, 3, 8000),
        TestRonParam(80, 3, 8000),
        TestRonParam(90, 3, 8000),
        TestRonParam(100, 3, 8000),
        TestRonParam(110, 3, 8000),
        TestRonParam(25, 4, 6400),
        TestRonParam(30, 4, 7700),
        TestRonParam(40, 4, 8000),
        TestRonParam(50, 4, 8000),
        TestRonParam(60, 4, 8000),
        TestRonParam(70, 4, 8000),
        TestRonParam(80, 4, 8000),
        TestRonParam(90, 4, 8000),
        TestRonParam(100, 4, 8000),
        TestRonParam(110, 4, 8000)),
    [](const ::testing::TestParamInfo<TestRonParam>& param_info) -> std::string {
      return "Han" + std::to_string(param_info.param.num_han) + "Fu" + std::to_string(param_info.param.num_hu);
    });

// 親のロン和了のテスト
INSTANTIATE_TEST_SUITE_P(
    Score, TestDealerRon,
    testing::Values(
        TestRonParam(30, 1, 1500),
        TestRonParam(40, 1, 2000),
        TestRonParam(50, 1, 2400),
        TestRonParam(60, 1, 2900),
        TestRonParam(70, 1, 3400),
        TestRonParam(80, 1, 3900),
        TestRonParam(90, 1, 4400),
        TestRonParam(100, 1, 4800),
        TestRonParam(110, 1, 5300),
        TestRonParam(25, 2, 2400),
        TestRonParam(30, 2, 2900),
        TestRonParam(40, 2, 3900),
        TestRonParam(50, 2, 4800),
        TestRonParam(60, 2, 5800),
        TestRonParam(70, 2, 6800),
        TestRonParam(80, 2, 7700),
        TestRonParam(90, 2, 8700),
        TestRonParam(100, 2, 9600),
        TestRonParam(110, 2, 10600),
        TestRonParam(25, 3, 4800),
        TestRonParam(30, 3, 5800),
        TestRonParam(40, 3, 7700),
        TestRonParam(50, 3, 9600),
        TestRonParam(60, 3, 11600),
        TestRonParam(70, 3, 12000),
        TestRonParam(80, 3, 12000),
        TestRonParam(90, 3, 12000),
        TestRonParam(100, 3, 12000),
        TestRonParam(110, 3, 12000),
        TestRonParam(25, 4, 9600),
        TestRonParam(30, 4, 11600),
        TestRonParam(40, 4, 12000),
        TestRonParam(50, 4, 12000),
        TestRonParam(60, 4, 12000),
        TestRonParam(70, 4, 12000),
        TestRonParam(80, 4, 12000),
        TestRonParam(90, 4, 12000),
        TestRonParam(100, 4, 12000),
        TestRonParam(110, 4, 12000)),
    [](const ::testing::TestParamInfo<TestRonParam>& param_info) -> std::string {
      return "Han" + std::to_string(param_info.param.num_han) + "Fu" + std::to_string(param_info.param.num_hu);
    });

// 子のツモ和了のテスト
INSTANTIATE_TEST_SUITE_P(
    Score, TestNonDealerTsumo,
    testing::Values(
        TestTsumoParam(30, 1, 300, 500),
        TestTsumoParam(40, 1, 400, 700),
        TestTsumoParam(50, 1, 400, 800),
        TestTsumoParam(60, 1, 500, 1000),
        TestTsumoParam(70, 1, 600, 1200),
        TestTsumoParam(80, 1, 700, 1300),
        TestTsumoParam(90, 1, 800, 1500),
        TestTsumoParam(100, 1, 800, 1600),
        TestTsumoParam(110, 1, 900, 1800),
        TestTsumoParam(30, 2, 500, 1000),
        TestTsumoParam(40, 2, 700, 1300),
        TestTsumoParam(50, 2, 800, 1600),
        TestTsumoParam(60, 2, 1000, 2000),
        TestTsumoParam(70, 2, 1200, 2300),
        TestTsumoParam(80, 2, 1300, 2600),
        TestTsumoParam(90, 2, 1500, 2900),
        TestTsumoParam(100, 2, 1600, 3200),
        TestTsumoParam(110, 2, 1800, 3600),
        TestTsumoParam(25, 3, 800, 1600),
        TestTsumoParam(30, 3, 1000, 2000),
        TestTsumoParam(40, 3, 1300, 2600),
        TestTsumoParam(50, 3, 1600, 3200),
        TestTsumoParam(60, 3, 2000, 3900),
        TestTsumoParam(70, 3, 2000, 4000),
        TestTsumoParam(80, 3, 2000, 4000),
        TestTsumoParam(90, 3, 2000, 4000),
        TestTsumoParam(100, 3, 2000, 4000),
        TestTsumoParam(110, 3, 2000, 4000),
        TestTsumoParam(25, 4, 1600, 3200),
        TestTsumoParam(30, 4, 2000, 3900),
        TestTsumoParam(40, 4, 2000, 4000),
        TestTsumoParam(50, 4, 2000, 4000),
        TestTsumoParam(60, 4, 2000, 4000),
        TestTsumoParam(70, 4, 2000, 4000),
        TestTsumoParam(80, 4, 2000, 4000),
        TestTsumoParam(90, 4, 2000, 4000),
        TestTsumoParam(100, 4, 2000, 4000),
        TestTsumoParam(110, 4, 2000, 4000)),
    [](const ::testing::TestParamInfo<TestTsumoParam>& param_info) -> std::string {
      return "Han" + std::to_string(param_info.param.num_han) + "Fu" + std::to_string(param_info.param.num_hu);
    });

// 親のツモ和了のテスト
INSTANTIATE_TEST_SUITE_P(
    Score, TestDealerTsumo,
    testing::Values(
        TestTsumoParam(30, 1, 500, 0),
        TestTsumoParam(40, 1, 700, 0),
        TestTsumoParam(50, 1, 800, 0),
        TestTsumoParam(60, 1, 1000, 0),
        TestTsumoParam(70, 1, 1200, 0),
        TestTsumoParam(80, 1, 1300, 0),
        TestTsumoParam(90, 1, 1500, 0),
        TestTsumoParam(100, 1, 1600, 0),
        TestTsumoParam(110, 1, 1800, 0),
        TestTsumoParam(20, 2, 700, 0),
        TestTsumoParam(30, 2, 1000, 0),
        TestTsumoParam(40, 2, 1300, 0),
        TestTsumoParam(50, 2, 1600, 0),
        TestTsumoParam(60, 2, 2000, 0),
        TestTsumoParam(70, 2, 2300, 0),
        TestTsumoParam(80, 2, 2600, 0),
        TestTsumoParam(90, 2, 2900, 0),
        TestTsumoParam(100, 2, 3200, 0),
        TestTsumoParam(110, 2, 3600, 0),
        TestTsumoParam(20, 3, 1300, 0),
        TestTsumoParam(25, 3, 1600, 0),
        TestTsumoParam(30, 3, 2000, 0),
        TestTsumoParam(40, 3, 2600, 0),
        TestTsumoParam(50, 3, 3200, 0),
        TestTsumoParam(60, 3, 3900, 0),
        TestTsumoParam(70, 3, 4000, 0),
        TestTsumoParam(80, 3, 4000, 0),
        TestTsumoParam(90, 3, 4000, 0),
        TestTsumoParam(100, 3, 4000, 0),
        TestTsumoParam(110, 3, 4000, 0),
        TestTsumoParam(20, 4, 2600, 0),
        TestTsumoParam(25, 4, 3200, 0),
        TestTsumoParam(30, 4, 3900, 0),
        TestTsumoParam(40, 4, 4000, 0),
        TestTsumoParam(50, 4, 4000, 0),
        TestTsumoParam(60, 4, 4000, 0),
        TestTsumoParam(70, 4, 4000, 0),
        TestTsumoParam(80, 4, 4000, 0),
        TestTsumoParam(90, 4, 4000, 0),
        TestTsumoParam(100, 4, 4000, 0),
        TestTsumoParam(110, 4, 4000, 0)),
    [](const ::testing::TestParamInfo<TestTsumoParam>& param_info) -> std::string {
      return "Han" + std::to_string(param_info.param.num_han) + "Fu" + std::to_string(param_info.param.num_hu);
    });
