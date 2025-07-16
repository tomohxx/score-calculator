#ifndef SCORE_CALCULATOR_SCORE_HPP
#define SCORE_CALCULATOR_SCORE_HPP

#include "config.hpp"
#include "result.hpp"
#include <memory>

namespace score_calculator {
  // 点数の支払い
  struct Payment {
    // 和了者が受け取る点数を計算する
    virtual int calc_score(const Config&) const = 0;
  };

  // 自摸和了時の点数の支払い
  struct TsumoPayment : Payment {
    int payment1; // 子が支払う点数
    int payment2; // 親が支払う点数

    TsumoPayment(const int payment1, const int payment2)
        : payment1(payment1), payment2(payment2) {}

    int calc_score(const Config& config) const override
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
    int payment; // 放銃者が支払う点数

    explicit RonPayment(const int payment) : payment(payment) {}
    int calc_score(const Config&) const override { return payment; }
  };

  // 点数の支払いを生成するファクトリ関数
  std::unique_ptr<Payment> calc_payment(const Result& result, const Config& config);

  namespace internal {
    std::unique_ptr<TsumoPayment> calc_payment_tsumo(const int basic_score, bool is_dealer);
    std::unique_ptr<RonPayment> calc_payment_ron(const int basic_score, bool is_dealer);
  }
}

#endif
