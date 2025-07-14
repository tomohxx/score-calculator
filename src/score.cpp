// https://ja.wikipedia.org/wiki/%E9%BA%BB%E9%9B%80%E3%81%AE%E5%BE%97%E7%82%B9%E8%A8%88%E7%AE%97
#include "score.hpp"
#include <stdexcept>

namespace score_calculator {
  constexpr int MAX_HAN_MANGAN = 5;
  constexpr int MAX_HAN_HANEMAN = 7;
  constexpr int MAX_HAN_BAIMAN = 10;
  constexpr int MAX_HAN_SANBAIMAN = 12;

  // 100点未満を切り上げる
  int ceil(const int n)
  {
    return (n + 99) / 100 * 100;
  }

  int calc_basic_score(const Result& result, const Config& config)
  {
    if (result.num_yakuman) {
      return config.enable_multiple_yakuman ? 8000 * result.num_yakuman : 8000;
    }

    if (result.num_han <= MAX_HAN_MANGAN) {
      return std::min(result.num_fu * (1 << (result.num_han + 2)), 2000);
    }
    else if (result.num_han <= MAX_HAN_HANEMAN) {
      return 3000;
    }
    else if (result.num_han <= MAX_HAN_BAIMAN) {
      return 4000;
    }
    else if (result.num_han <= MAX_HAN_SANBAIMAN && config.enable_counted_yakuman) {
      return 6000;
    }
    else {
      return 8000;
    }
  }

  std::unique_ptr<Payment> calc_payment(const Result& result, const Config& config)
  {
    if (!result) {
      throw std::invalid_argument("Invalid num_fu, num_han or num_yakuman");
    }

    const bool is_dealer = (config.seat_wind == WindType::EAST);

    int basic_score = calc_basic_score(result, config);

    if (config.enable_rounded_up_managan && basic_score == 1920) {
      basic_score = 2000;
    }

    if (config.is_tsumo) {
      return internal::calc_payment_tsumo(basic_score, is_dealer);
    }
    else {
      return internal::calc_payment_ron(basic_score, is_dealer);
    }
  }

  namespace internal {
    std::unique_ptr<TsumoPayment> calc_payment_tsumo(const int basic_score, const bool is_dealer)
    {
      if (is_dealer) {
        return std::make_unique<TsumoPayment>(ceil(basic_score * 2), 0);
      }
      else {
        return std::make_unique<TsumoPayment>(ceil(basic_score), ceil(basic_score * 2));
      }
    }

    std::unique_ptr<RonPayment> calc_payment_ron(const int basic_score, const bool is_dealer)
    {
      if (is_dealer) {
        return std::make_unique<RonPayment>(ceil(basic_score * 6));
      }
      else {
        return std::make_unique<RonPayment>(ceil(basic_score * 4));
      }
    }
  }
}
