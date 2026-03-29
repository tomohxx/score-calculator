#ifndef MAHJONG_SCORE_CALCULATOR_TYPES_HPP
#define MAHJONG_SCORE_CALCULATOR_TYPES_HPP

#include <array>

namespace mahjong::score_calculator {
  constexpr int NUM_TIDS = 34;

  using Arr = std::array<int, NUM_TIDS>;

  // 面子
  enum class MeldType {
    PON,    // ポン
    CHI,    // チー
    MINKAN, // 明槓
    ANKAN,  // 暗槓
  };

  namespace detail {
    constexpr std::array<char, 4> suffix = {'m', 'p', 's', 'z'};
    // ブロック
    struct Block {
      unsigned int num_pair : 1 = 0;            // 雀頭の数
      unsigned int num_open_triplet : 1 = 0;    // 刻子の数
      unsigned int num_closed_triplet : 1 = 0;  // 刻子の数
      unsigned int num_open_quad : 1 = 0;       // 槓子の数
      unsigned int num_closed_quad : 1 = 0;     // 槓子の数
      unsigned int num_closed_sequence : 3 = 0; // 順子の数
      unsigned int num_open_sequence : 3 = 0;   // 順子の数
    };

    using Blocks = std::array<Block, NUM_TIDS>;

    // 雀頭が存在するか
    inline bool exists_pair(const Block& block)
    {
      return block.num_pair;
    }

    // 暗刻が存在するか
    inline bool exists_closed_triplet(const Block& block)
    {
      return block.num_closed_triplet | block.num_closed_quad;
    }

    // 刻子または槓子が存在するか
    inline bool exists_triplet(const Block& block)
    {
      return block.num_closed_triplet | block.num_open_triplet | block.num_closed_quad | block.num_open_quad;
    }

    // 槓子が存在するか
    inline bool exists_quad(const Block& block)
    {
      return block.num_closed_quad | block.num_open_quad;
    }

    // 順子の数を取得する
    inline unsigned int get_num_sequence(const Block& block)
    {
      return block.num_closed_sequence + block.num_open_sequence;
    }

    // 基本符を計算する
    inline unsigned int calc_basic_fu(const Block& block)
    {
      return *reinterpret_cast<const unsigned int*>(&block) & 0b11110;
    }
  }

  // 風
  enum class WindType {
    EAST,  // 東
    SOUTH, // 南
    WEST,  // 西
    NORTH, // 北
  };

  // 牌種
  enum class Suits {
    MANZU, // 萬子
    PINZU, // 筒子
    SOUZU, // 索子
    JIHAI, // 字牌
  };

  // 役ID
  enum class YakuId {
    MENZENCHIN_TSUMOHOU,      // 面前清自摸和
    RIICHI,                   // 立直
    IPPATSU,                  // 一発
    CHANKAN,                  // 搶槓
    RINSHAN_KAIHOU,           // 嶺上開花
    HAITEI_RAOYUE,            // 海底撈月
    HOUTEI_RAOYUI,            // 河底撈魚
    PINFU,                    // 平和
    TANYAOCHUU,               // 断幺九
    IIPEIKOU,                 // 一盃口
    YAKUHAI_EAST_SEAT,        // 役牌(自風 東)
    YAKUHAI_SOUTH_SEAT,       // 役牌(自風 南)
    YAKUHAI_WEST_SEAT,        // 役牌(自風 西)
    YAKUHAI_NORTH_SEAT,       // 役牌(自風 西)
    YAKUHAI_EAST_ROUND,       // 役牌(場風 東)
    YAKUHAI_SOUTH_ROUND,      // 役牌(場風 南)
    YAKUHAI_WEST_ROUND,       // 役牌(場風 西)
    YAKUHAI_NORTH_ROUND,      // 役牌(場風 北)
    YAKUHAI_WHITE,            // 役牌(白)
    YAKUHAI_GREEN,            // 役牌(発)
    YAKUHAI_RED,              // 役牌(中)
    DOUBLE_RIICHI,            // 両立直
    CHIITOITSU,               // 七対子
    HONCHANTAIYAOCHUU,        // 混全帯幺九
    IKKITSUUKAN,              // 一気通貫
    SANSHOKU_DOUJUN,          // 三色同順
    SANSHOKU_DOUKOU,          // 三色同刻
    SANKANTSU,                // 三槓子
    TOITOIHOU,                // 対々和
    SANANKOU,                 // 三暗刻
    SHOUSANGEN,               // 小三元
    HONROUTOU,                // 混老頭
    RYANPEIKOU,               // 二盃口
    JUNCHANTAIYAOCHUU,        // 純全帯幺九
    HONIISOU,                 // 混一色
    CHINIISOU,                // 清一色
    UNUSED,                   // NOTE: 未使用
    TENHOU,                   // 天和
    CHIIHOU,                  // 地和
    DAISANGEN,                // 大三元
    SUUANKOU,                 // 四暗刻
    SUUANKOU_TANKI,           // 四暗刻単騎
    TSUUIISOU,                // 字一色
    RYUUIISOU,                // 緑一色
    CHINROUTOU,               // 清老頭
    CHUUREN_POUTOU,           // 九蓮宝燈
    JUNSEI_CHUUREN_POUTOU,    // 純正九蓮宝燈
    KOKUSHI_MUSOU,            // 国士無双
    KOKUSHI_MUSOU_13MENMACHI, // 国士無双13面待ち
    DAISUUSHII,               // 大四喜
    SHOUSUUSHII,              // 小四喜
    SUUKANTSU,                // 四槓子
    DORA,                     // ドラ
    URA_DORA,                 // 裏ドラ
    AKA_DORA,                 // 赤ドラ
  };

  enum class RiichiType {
    RIICHI = static_cast<int>(YakuId::RIICHI),               // 立直
    DOUBLE_RIICHI = static_cast<int>(YakuId::DOUBLE_RIICHI), // 両立直
  };

  enum class RiichiOption {
    IPPATSU = static_cast<int>(YakuId::IPPATSU), // 一発
  };

  enum class WinningOption {
    CHANKAN = static_cast<int>(YakuId::CHANKAN),               // 搶槓
    RINSHAN_KAIHOU = static_cast<int>(YakuId::RINSHAN_KAIHOU), // 嶺上開花
    HAITEI_RAOYUE = static_cast<int>(YakuId::HAITEI_RAOYUE),   // 海底撈月
    HOUTEI_RAOYUI = static_cast<int>(YakuId::HOUTEI_RAOYUI),   // 河底撈魚
    TENHOU = static_cast<int>(YakuId::TENHOU),                 // 天和
    CHIIHOU = static_cast<int>(YakuId::CHIIHOU),               // 地和
  };

  namespace detail {
    // 1翻役

    constexpr unsigned int NUM_YAKU_MENZENCHIN_TSUMOHOU = 1u; // 面前清自摸和
    constexpr unsigned int NUM_YAKU_RIICHI = 1u;              // 立直
    constexpr unsigned int NUM_YAKU_IPPATSU = 1u;             // 一発
    constexpr unsigned int NUM_YAKU_CHANKAN = 1u;             // 搶槓
    constexpr unsigned int NUM_YAKU_RINSHAN_KAIHOU = 1u;      // 嶺上開花
    constexpr unsigned int NUM_YAKU_HAITEI_RAOYUE = 1u;       // 海底撈月
    constexpr unsigned int NUM_YAKU_HOUTEI_RAOYUI = 1u;       // 河底撈魚
    constexpr unsigned int NUM_YAKU_PINFU = 1u;               // 平和
    constexpr unsigned int NUM_YAKU_TANYAOCHUU = 1u;          // 断幺九
    constexpr unsigned int NUM_YAKU_IIPEIKOU = 1u;            // 一盃口
    constexpr unsigned int NUM_YAKU_YAKUHAI_EAST_SEAT = 1u;   // 役牌(自風 東)
    constexpr unsigned int NUM_YAKU_YAKUHAI_SOUTH_SEAT = 1u;  // 役牌(自風 南)
    constexpr unsigned int NUM_YAKU_YAKUHAI_WEST_SEAT = 1u;   // 役牌(自風 西)
    constexpr unsigned int NUM_YAKU_YAKUHAI_NORTH_SEAT = 1u;  // 役牌(自風 西)
    constexpr unsigned int NUM_YAKU_YAKUHAI_EAST_ROUND = 1u;  // 役牌(場風 東)
    constexpr unsigned int NUM_YAKU_YAKUHAI_SOUTH_ROUND = 1u; // 役牌(場風 南)
    constexpr unsigned int NUM_YAKU_YAKUHAI_WEST_ROUND = 1u;  // 役牌(場風 西)
    constexpr unsigned int NUM_YAKU_YAKUHAI_NORTH_ROUND = 1u; // 役牌(場風 北)
    constexpr unsigned int NUM_YAKU_YAKUHAI_WHITE = 1u;       // 役牌(白)
    constexpr unsigned int NUM_YAKU_YAKUHAI_GREEN = 1u;       // 役牌(発)
    constexpr unsigned int NUM_YAKU_YAKUHAI_RED = 1u;         // 役牌(中)

    // 2翻役

    constexpr unsigned int NUM_YAKU_DOUBLE_RIICHI = 2u;     // 両立直
    constexpr unsigned int NUM_YAKU_CHIITOITSU = 2u;        // 七対子
    constexpr unsigned int NUM_YAKU_HONCHANTAIYAOCHUU = 2u; // 混全帯幺九
    constexpr unsigned int NUM_YAKU_IKKITSUUKAN = 2u;       // 一気通貫
    constexpr unsigned int NUM_YAKU_SANSHOKU_DOUJUN = 2u;   // 三色同順
    constexpr unsigned int NUM_YAKU_SANSHOKU_DOUKOU = 2u;   // 三色同刻
    constexpr unsigned int NUM_YAKU_SANKANTSU = 2u;         // 三槓子
    constexpr unsigned int NUM_YAKU_TOITOIHOU = 2u;         // 対々和
    constexpr unsigned int NUM_YAKU_SANANKOU = 2u;          // 三暗刻
    constexpr unsigned int NUM_YAKU_SHOUSANGEN = 2u;        // 小三元
    constexpr unsigned int NUM_YAKU_HONROUTOU = 2u;         // 混老頭

    // 3翻役

    constexpr int NUM_YAKU_RYANPEIKOU = 3u;        // 二盃口
    constexpr int NUM_YAKU_JUNCHANTAIYAOCHUU = 3u; // 純全帯幺九
    constexpr int NUM_YAKU_HONIISOU = 3u;          // 混一色

    // 6翻役

    constexpr int NUM_YAKU_CHINIISOU = 6u; // 清一色

    // 役満

    constexpr int SINGLE_YAKUMAN = 1u;
    constexpr int DOUBLE_YAKUMAN = 2u;

    constexpr int NUM_FU_SEVEN_PAIRS = 25u;     // 七対子の符
    constexpr int NUM_FU_THIRTEEN_ORPHANS = 0u; // 国士無双の符
  }
}

#endif
