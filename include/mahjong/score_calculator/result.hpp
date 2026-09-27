#ifndef SCORE_CALCURATOR_RESULT_HPP
#define SCORE_CALCURATOR_RESULT_HPP

#include <mahjong/score_calculator/types.hpp>
#include <unordered_map>

namespace mahjong::score_calculator {
  namespace detail {
    struct Result {
      unsigned int num_fu = 0u;
      unsigned int num_han = 0u;
      unsigned int num_yakuman = 0u;
      std::unordered_map<YakuId, unsigned int> reasons_yaku;
      std::unordered_map<YakuId, unsigned int> reasons_yakuman;

      Result() = default;

      Result(unsigned int num_fu, unsigned int num_han)
          : num_fu(num_fu), num_han(num_han) {}

      Result(unsigned int num_fu, unsigned int num_han, unsigned int num_yakuman)
          : num_fu(num_fu), num_han(num_han), num_yakuman(num_yakuman) {}

      void update_yaku(const YakuId yaku_id, const unsigned int num_han)
      {
        this->num_han += num_han;
        reasons_yaku.insert({yaku_id, num_han});
      }

      void update_yakuman(const YakuId yaku_id, const unsigned int num_yakuman)
      {
        this->num_yakuman += num_yakuman;
        reasons_yakuman.insert({yaku_id, num_yakuman});
      }

      explicit operator bool() const { return (num_fu && num_han) || num_yakuman; }
    };
  }

  struct WaitType {
    bool is_open_wait = false;
    bool is_edge_wait = false;
    bool is_closed_wait = false;
    bool is_pair_wait = false;
    bool is_dual_wait = false;

    void merge(const WaitType& wait_type)
    {
      is_open_wait = is_open_wait || wait_type.is_open_wait;
      is_edge_wait = is_edge_wait || wait_type.is_edge_wait;
      is_closed_wait = is_closed_wait || wait_type.is_closed_wait;
      is_pair_wait = is_pair_wait || wait_type.is_pair_wait;
      is_dual_wait = is_dual_wait || wait_type.is_dual_wait;
    }
  };

  struct Result : detail::Result {
    using detail::Result::Result;

    WaitType wait_type;

    Result(const detail::Result& result)
        : detail::Result(result), wait_type() {}

    Result(const detail::Result& result, const WaitType& wait_type)
        : detail::Result(result), wait_type(wait_type) {}
  };
}

#endif
