#ifndef MAHJONG_SCORE_CALCULATOR_PARSER_HPP
#define MAHJONG_SCORE_CALCULATOR_PARSER_HPP

#include <mahjong/score_calculator/hand.hpp>
#include <mahjong/score_calculator/meld.hpp>
#include <mahjong/score_calculator/tile.hpp>
#include <string>

namespace mahjong::score_calculator {
  namespace parser {
    namespace regular {
      Tiles from_mpsz(const std::string&);
      void from_mpsz(const std::string&, Hand&, Melds&);
      std::string to_mpsz(const Hand&, const Melds& = {});
    }

    namespace tenhou {
      Tiles from_mpsz(const std::string&);
      void from_mpsz(const std::string&, Hand&, Melds&);
      std::string to_mpsz(const Hand&, const Melds& = {});
    }
  }

  using parser::regular::from_mpsz;
  using parser::regular::to_mpsz;
}

#endif
