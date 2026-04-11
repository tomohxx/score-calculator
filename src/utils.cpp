#include <mahjong/score_calculator/utils.hpp>
#include <utility>

namespace mahjong::score_calculator {
  std::ostream& operator<<(std::ostream& os, const YakuId yaku_id)
  {
    switch (yaku_id) {
    case YakuId::MENZENCHIN_TSUMOHOU:
      return os << "Menzenchin Tsumohou";
    case YakuId::RIICHI:
      return os << "Riichi";
    case YakuId::IPPATSU:
      return os << "Ippatsu";
    case YakuId::CHANKAN:
      return os << "Chankan";
    case YakuId::RINSHAN_KAIHOU:
      return os << "Rinshan Kaihou";
    case YakuId::HAITEI_RAOYUE:
      return os << "Haitei Raoyue";
    case YakuId::HOUTEI_RAOYUI:
      return os << "Houtei Raoyui";
    case YakuId::PINFU:
      return os << "Pinfu";
    case YakuId::TANYAOCHUU:
      return os << "Tanyaochuu";
    case YakuId::IIPEIKOU:
      return os << "Iipeikou";
    case YakuId::YAKUHAI_EAST_SEAT:
      return os << "Yakuhai East Seat";
    case YakuId::YAKUHAI_SOUTH_SEAT:
      return os << "Yakuhai South Seat";
    case YakuId::YAKUHAI_WEST_SEAT:
      return os << "Yakuhai West Seat";
    case YakuId::YAKUHAI_NORTH_SEAT:
      return os << "Yakuhai North Seat";
    case YakuId::YAKUHAI_EAST_ROUND:
      return os << "Yakuhai East Round";
    case YakuId::YAKUHAI_SOUTH_ROUND:
      return os << "Yakuhai South Round";
    case YakuId::YAKUHAI_WEST_ROUND:
      return os << "Yakuhai West Round";
    case YakuId::YAKUHAI_NORTH_ROUND:
      return os << "Yakuhai North Round";
    case YakuId::YAKUHAI_WHITE:
      return os << "Yakuhai White";
    case YakuId::YAKUHAI_GREEN:
      return os << "Yakuhai Green";
    case YakuId::YAKUHAI_RED:
      return os << "Yakuhai Red";
    case YakuId::DOUBLE_RIICHI:
      return os << "Double Riichi";
    case YakuId::CHIITOITSU:
      return os << "Chiitoitsu";
    case YakuId::HONCHANTAIYAOCHUU:
      return os << "Honchantaiyaochuu";
    case YakuId::IKKITSUUKAN:
      return os << "Ikkitsuukan";
    case YakuId::SANSHOKU_DOUJUN:
      return os << "Sanshoku Doujun";
    case YakuId::SANSHOKU_DOUKOU:
      return os << "Sanshoku Doukou";
    case YakuId::SANKANTSU:
      return os << "Sankantsu";
    case YakuId::TOITOIHOU:
      return os << "Toitoihou";
    case YakuId::SANANKOU:
      return os << "Sanankou";
    case YakuId::SHOUSANGEN:
      return os << "Shousangen";
    case YakuId::HONROUTOU:
      return os << "Honroutou";
    case YakuId::RYANPEIKOU:
      return os << "Ryanpeikou";
    case YakuId::JUNCHANTAIYAOCHUU:
      return os << "Junchantaiyaochuu";
    case YakuId::HONIISOU:
      return os << "Honiisou";
    case YakuId::CHINIISOU:
      return os << "Chiniisou";
    case YakuId::UNUSED:
      return os << "Unused";
    case YakuId::TENHOU:
      return os << "Tenhou";
    case YakuId::CHIIHOU:
      return os << "Chiihou";
    case YakuId::DAISANGEN:
      return os << "Daisangen";
    case YakuId::SUUANKOU:
      return os << "Suuankou";
    case YakuId::SUUANKOU_TANKI:
      return os << "Suuankou Tanki";
    case YakuId::TSUUIISOU:
      return os << "Tsuuiisou";
    case YakuId::RYUUIISOU:
      return os << "Ryuuiisou";
    case YakuId::CHINROUTOU:
      return os << "Chinroutou";
    case YakuId::CHUUREN_POUTOU:
      return os << "Chuuren Poutou";
    case YakuId::JUNSEI_CHUUREN_POUTOU:
      return os << "Junsei Chuuren Poutou";
    case YakuId::KOKUSHI_MUSOU:
      return os << "Kokushi Musou";
    case YakuId::KOKUSHI_MUSOU_13MENMACHI:
      return os << "Kokushi Musou 13menmachi";
    case YakuId::DAISUUSHII:
      return os << "Daisuushii";
    case YakuId::SHOUSUUSHII:
      return os << "Shousuushii";
    case YakuId::SUUKANTSU:
      return os << "Suukantsu";
    case YakuId::DORA:
      return os << "Dora";
    case YakuId::URA_DORA:
      return os << "Ura Dora";
    case YakuId::AKA_DORA:
      return os << "Aka Dora";
    default:
      std::unreachable();
    }
  }
}
