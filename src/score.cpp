// https://ja.wikipedia.org/wiki/%E9%BA%BB%E9%9B%80%E3%81%AE%E5%BE%97%E7%82%B9%E8%A8%88%E7%AE%97
#include <mahjong/score_calculator/score.hpp>
#include <stdexcept>

namespace mahjong::score_calculator {
  constexpr unsigned int MAX_HAN_MANGAN = 5u;
  constexpr unsigned int MAX_HAN_HANEMAN = 7u;
  constexpr unsigned int MAX_HAN_BAIMAN = 10u;
  constexpr unsigned int MAX_HAN_SANBAIMAN = 12u;

  // 100点未満を切り上げる
  unsigned int ceil(const unsigned int n)
  {
    return (n + 99u) / 100u * 100u;
  }

  int calc_basic_score(const Result& result, const Config& config)
  {
    if (result.num_yakuman) {
      return config.enable_multiple_yakuman ? 8000u * result.num_yakuman : 8000u;
    }

    if (result.num_han <= MAX_HAN_MANGAN) {
      return std::min(result.num_fu * (1u << (result.num_han + 2u)), 2000u);
    }
    else if (result.num_han <= MAX_HAN_HANEMAN) {
      return 3000u;
    }
    else if (result.num_han <= MAX_HAN_BAIMAN) {
      return 4000u;
    }
    else if (result.num_han <= MAX_HAN_SANBAIMAN && config.enable_counted_yakuman) {
      return 6000u;
    }
    else {
      return 8000u;
    }
  }

  std::unique_ptr<Payment> calc_payment(const Result& result, const Config& config)
  {
    if (!result) {
      throw std::invalid_argument("Invalid num_fu, num_han or num_yakuman");
    }

    const bool is_dealer = (config.seat_wind == WindType::EAST);

    unsigned int basic_score = calc_basic_score(result, config);

    if (config.enable_rounded_up_mangan && basic_score == 1920u) {
      basic_score = 2000u;
    }

    if (config.is_tsumo) {
      return detail::calc_payment_tsumo(basic_score, is_dealer);
    }
    else {
      return detail::calc_payment_ron(basic_score, is_dealer);
    }
  }

  namespace detail {
    std::unique_ptr<TsumoPayment> calc_payment_tsumo(const unsigned int basic_score, const bool is_dealer)
    {
      if (is_dealer) {
        return std::make_unique<TsumoPayment>(ceil(basic_score * 2u), 0u);
      }
      else {
        return std::make_unique<TsumoPayment>(ceil(basic_score), ceil(basic_score * 2u));
      }
    }

    std::unique_ptr<RonPayment> calc_payment_ron(const unsigned int basic_score, const bool is_dealer)
    {
      if (is_dealer) {
        return std::make_unique<RonPayment>(ceil(basic_score * 6u));
      }
      else {
        return std::make_unique<RonPayment>(ceil(basic_score * 4u));
      }
    }
  }
}
