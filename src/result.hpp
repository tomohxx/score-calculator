#ifndef SCORE_CALCURATOR_RESULT_HPP
#define SCORE_CALCURATOR_RESULT_HPP

#include "types.hpp"
#include <unordered_map>

namespace score_calculator {
  struct Result {
    int num_fu = 0;
    int num_han = 0;
    int num_yakuman = 0;
    std::unordered_map<YakuId, int> reasons_yaku;
    std::unordered_map<YakuId, int> reasons_yakuman;

    void update_yaku(const YakuId yaku_id, const int num_han)
    {
      this->num_han += num_han;
      reasons_yaku.insert({yaku_id, num_han});
    }

    void update_yakuman(const YakuId yaku_id, const int num_yakuman)
    {
      this->num_yakuman += num_yakuman;
      reasons_yakuman.insert({yaku_id, num_yakuman});
    }

    explicit operator bool() const { return (num_fu > 0 && num_han > 0) || num_yakuman > 0; }
    bool operator<(const Result& rhs) const { return num_han < rhs.num_han || (num_han == rhs.num_han && num_fu < rhs.num_fu); }
    bool operator>(const Result& rhs) const { return num_han > rhs.num_han || (num_han == rhs.num_han && num_fu > rhs.num_fu); }
  };
}

#endif
