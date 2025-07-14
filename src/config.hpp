#ifndef SCORE_CALCURATOR_CONFIG_HPP
#define SCORE_CALCURATOR_CONFIG_HPP

#include "tile.hpp"
#include "types.hpp"
#include <optional>

namespace score_calculator {
  struct Config {
    WindType seat_wind;                                // 自風
    WindType round_wind;                               // 場風
    Tiles dora_indicators;                             // ドラ表示牌
    Tiles ura_dora_indicators;                         // 裏ドラ表示牌
    bool is_tsumo = false;                             // 自摸フラグ
    bool is_2fu_double_wind = false;                   // 連風牌を2符とするか
    bool enable_double_yakuman_suuankou = false;       // 四暗刻単騎のダブル役満を有効にするか
    bool enable_double_yakuman_chuuren_poutou = false; // 純正九蓮宝燈のダブル役満を有効にするか
    bool enable_double_yakuman_kokushi_musou = false;  // 国士無双13面待ちのダブル役満を有効にするか
    bool enable_double_yakuman_daisuushi = false;      // 大四喜のダブル役満を有効にするか
    bool enable_rounded_up_managan = false;            // 切り上げ満貫を有効にするか
    bool enable_counted_yakuman = true;                // 数え役満を有効にするか
    bool enable_multiple_yakuman = true;               // 複合役満を有効にするか
    std::optional<RiichiType> riichi_type;             // 立直タイプ(立直/両立直)
    std::optional<RiichiOption> riichi_option;         // 立直オプション(一発)
    std::optional<WinningOption> winning_option;       // 和了オプション(搶槓/嶺上開花/海底撈月/河底撈魚/天和/地和)
  };
}

#endif
