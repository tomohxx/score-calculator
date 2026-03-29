#ifndef SCORE_CALCURATOR_RESULT_HPP
#define SCORE_CALCURATOR_RESULT_HPP

#include <mahjong/score_calculator/types.hpp>
#include <unordered_map>

namespace mahjong::score_calculator {
  struct Result {
    unsigned int num_fu = 0u;
    unsigned int num_han = 0u;
    unsigned int num_yakuman = 0u;
    std::unordered_map<YakuId, unsigned int> reasons_yaku;
    std::unordered_map<YakuId, unsigned int> reasons_yakuman;

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

#endif
