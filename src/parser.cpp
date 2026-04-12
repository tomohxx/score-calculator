#include <cassert>
#include <mahjong/score_calculator/parser.hpp>
#include <regex>
#include <span>
#include <stdexcept>

namespace {
  using mahjong::score_calculator::Tiles;

  Tiles from_mpsz(const std::string& mpsz)
  {
    Tiles tiles;
    int base = 0;

    for (auto it = mpsz.crbegin(); it != mpsz.crend(); ++it) {
      if (*it >= '1' && *it <= '9') {
        tiles.emplace_back(*it - '1' + base, false);
      }
      else if (*it == 'r' && !tiles.empty()) {
        tiles.back().is_red = true;
      }
      else if (*it == 'm') base = 0;
      else if (*it == 'p') base = 9;
      else if (*it == 's') base = 18;
      else if (*it == 'z') base = 27;
    }

    std::reverse(tiles.begin(), tiles.end());

    return tiles;
  }
}

namespace mahjong::score_calculator::parser {
  namespace regular {
    std::tuple<Hand, Melds> from_mpsz(const std::string& mpsz)
    {
      static const std::regex re("\\[{0,2}(?:(?:[1-9]|r5)+[mps]|[1-7]+z)+\\]{0,2}");
      Hand hand;
      Melds melds;

      for (std::sregex_iterator it(std::begin(mpsz), std::end(mpsz), re), end; it != end; ++it) {
        const auto s = it->str();
        const auto tiles = ::from_mpsz(s);
        // 暗槓
        if (s.starts_with("[[") && s.ends_with("]]")) {
          melds.push_back(Meld::make_ankan(tiles));
        }
        else if (s.starts_with("[[") || s.ends_with("]]")) {
          throw std::invalid_argument("Invalid mpsz string");
        }
        // ポン, チー, 明槓
        else if (s.starts_with("[") && s.ends_with("]")) {
          melds.push_back(Meld::make_pon_chi_minkan(tiles));
        }
        else if (s.starts_with("[") || s.ends_with("]")) {
          throw std::invalid_argument("Invalid mpsz string");
        }
        // 手牌
        else {
          hand.draw(tiles);
        }
      }

      return {hand, melds};
    }

    std::string to_mpsz(const Hand& hand, const Melds& melds)
    {
      std::string mpsz = static_cast<std::string>(hand);

      for (const auto& meld : melds) {
        mpsz += static_cast<std::string>(meld);
      }

      return mpsz;
    }
  }

  namespace tenhou {
    std::tuple<Hand, Melds> from_mpsz(const std::string& mpsz)
    {
      const auto tmp = std::regex_replace(mpsz, std::regex("0"), "r5");

      return regular::from_mpsz(tmp);
    }

    std::string to_mpsz(const Hand& hand, const Melds& melds)
    {
      const auto tmp = regular::to_mpsz(hand, melds);

      return std::regex_replace(tmp, std::regex("r5"), "0");
    }
  }
}
