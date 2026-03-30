#include <mahjong/score_calculator/hand.hpp>

namespace mahjong::score_calculator {
  Hand::operator std::string() const
  {
    std::string s;

    for (int i = 0; i < 4; ++i) {
      std::string t;

      for (int j = 0; j < (i == 3 ? 7 : 9); ++j) {
        for (int k = 0; k < get_num_red_dora(9 * i + j); ++k) {
          (t += 'r') += j + '1';
        }

        for (int k = 0; k < get_num_tile(9 * i + j); ++k) {
          t += j + '1';
        }
      }

      if (!t.empty()) {
        s += t += detail::suffix[i];
      }
    }

    return s;
  }
}
