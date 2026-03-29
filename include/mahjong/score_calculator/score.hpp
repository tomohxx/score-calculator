#ifndef MAHJONG_SCORE_CALCULATOR_SCORE_HPP
#define MAHJONG_SCORE_CALCULATOR_SCORE_HPP

#include <mahjong/score_calculator/config.hpp>
#include <mahjong/score_calculator/result.hpp>
#include <memory>

namespace mahjong::score_calculator {
  // 点数の支払い
  struct Payment {
    // 和了者が受け取る点数を計算する
    virtual unsigned int calc_score(const Config&) const = 0;
  };

  // 自摸和了時の点数の支払い
  struct TsumoPayment : Payment {
    unsigned int payment1; // 子が支払う点数
    unsigned int payment2; // 親が支払う点数

    TsumoPayment(const unsigned int payment1, const unsigned int payment2)
        : payment1(payment1), payment2(payment2) {}

    unsigned int calc_score(const Config& config) const override
    {
      if (config.three_player) {
        return payment2 > 0 ? payment1 + payment2 : payment1 * 2;
      }
      else {
        return payment2 > 0 ? payment1 * 2 + payment2 : payment1 * 3;
      }
    }
  };

  // ロン和了時の点数の支払い
  struct RonPayment : Payment {
    unsigned int payment; // 放銃者が支払う点数

    explicit RonPayment(const unsigned int payment) : payment(payment) {}
    unsigned int calc_score(const Config&) const override { return payment; }
  };

  // 点数の支払いを生成するファクトリ関数
  std::unique_ptr<Payment> calc_payment(const Result& result, const Config& config);

  namespace detail {
    std::unique_ptr<TsumoPayment> calc_payment_tsumo(const unsigned int basic_score, bool is_dealer);
    std::unique_ptr<RonPayment> calc_payment_ron(const unsigned int basic_score, bool is_dealer);
  }
}

#endif
