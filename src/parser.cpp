#include "parser.hpp"
#include <cassert>
#include <regex>
#include <span>
#include <stdexcept>

namespace score_calculator {
  namespace internal {
    Tiles from_mpsz(const std::string& str_mpsz)
    {
      Tiles tiles;
      int offset = 0;

      for (auto it = str_mpsz.crbegin(); it != str_mpsz.crend(); ++it) {
        if (*it == '0') {
          tiles.emplace_back(4 + offset, true);
        }
        else if (*it >= '1' && *it <= '9') {
          tiles.emplace_back(*it - '1' + offset, false);
        }
        else if (*it == 'm') offset = 0;
        else if (*it == 'p') offset = 9;
        else if (*it == 's') offset = 18;
        else if (*it == 'z') offset = 27;
      }

      std::reverse(tiles.begin(), tiles.end());

      return tiles;
    }
  }

  void from_mpsz(const std::string& str_mpsz, Hand& hand, Melds& melds)
  {
    static const std::regex re("\\[*(?:[0-9]+[mps]|[1-7]+z)+\\]*");

    for (std::sregex_iterator it(std::begin(str_mpsz), std::end(str_mpsz), re), end; it != end; ++it) {
      const auto str = it->str();
      const auto tiles = internal::from_mpsz(str);
      // 暗槓
      if (str.starts_with("[[") && str.ends_with("]]")) {
        melds.push_back(internal::make_ankan(tiles));
      }
      // ポン, チー, 明槓
      else if (str.starts_with("[") && str.ends_with("]")) {
        melds.push_back(internal::make_pon_chi_minkan(tiles));
      }
      // 手牌
      else {
        hand.draw(tiles);
      }
    }
  }

  namespace internal {
    std::string to_mpsz(const std::span<const int>& tiles,
                        const std::span<const int>& red_dora,
                        const char delimiter)
    {
      assert(tiles.size() == red_dora.size());

      std::string str_mpsz;

      for (std::size_t i = 0u; i < tiles.size(); ++i) {
        for (int j = 0; j < red_dora[i]; ++j) {
          str_mpsz += '0';
        }

        for (int j = 0; j < tiles[i] - red_dora[i]; ++j) {
          str_mpsz += i + '1';
        }
      }

      if (str_mpsz.empty()) return {};
      else return str_mpsz += delimiter;
    }

    std::string to_mpsz(const Hand& hand)
    {
      std::string str_mpsz;

      str_mpsz += to_mpsz(std::span(hand.tiles).subspan(0, 9), std::span(hand.red_dora).subspan(0, 9), 'm');
      str_mpsz += to_mpsz(std::span(hand.tiles).subspan(9, 9), std::span(hand.red_dora).subspan(9, 9), 'p');
      str_mpsz += to_mpsz(std::span(hand.tiles).subspan(18, 9), std::span(hand.red_dora).subspan(18, 9), 's');
      str_mpsz += to_mpsz(std::span(hand.tiles).subspan(27, 7), std::span(hand.red_dora).subspan(27, 7), 'z');

      return str_mpsz;
    }

    std::string to_mpsz(const Meld& meld)
    {
      assert(meld);

      std::string str_mpsz;

      for (const auto& tile : meld.get_tiles()) {
        str_mpsz += tile.index % 9 + '1';
      }

      switch (meld.get_suit()) {
      case Suits::MANZU: str_mpsz += 'm'; break;
      case Suits::PINZU: str_mpsz += 'p'; break;
      case Suits::SOUZU: str_mpsz += 's'; break;
      case Suits::ZIHAI: str_mpsz += 'z'; break;
      default: std::unreachable();
      }

      if (meld.get_meld_type() == MeldType::ANKAN) {
        str_mpsz = "[[" + str_mpsz + "]]";
      }
      else {
        str_mpsz = "[" + str_mpsz + "]";
      }

      return str_mpsz;
    }
  }

  std::string to_mpsz(const Hand& hand, const Melds& melds)
  {
    std::string str_mpsz = internal::to_mpsz(hand);

    for (const auto& meld : melds) {
      str_mpsz += internal::to_mpsz(meld);
    }

    return str_mpsz;
  }
}
