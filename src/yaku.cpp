#include "yaku.hpp"
#include "tile.hpp"
#include "types.hpp"
#include <algorithm>
#include <numeric>
#define KUISAGARI(num_yaku) (is_open ? num_yaku - 1 : num_yaku)
#define UPDATE_YAKU(yaku_id) result.update_yaku(YakuId::yaku_id, NUM_YAKU_##yaku_id)
#define UPDATE_YAKU_KUISAGARI(yaku_id) result.update_yaku(YakuId::yaku_id, KUISAGARI(NUM_YAKU_##yaku_id))
#define UPDATE_SINGLE_YAKUMAN(yaku_id) result.update_yakuman(YakuId::yaku_id, SINGLE_YAKUMAN)
#define UPDATE_DOUBLE_YAKUMAN(yaku_id, condition) result.update_yakuman(YakuId::yaku_id, ((condition) ? DOUBLE_YAKUMAN : SINGLE_YAKUMAN))

namespace score_calculator::internal {
  constexpr std::array<int, 21u> simple_tiles{{m2, m3, m4, m5, m6, m7, m8, // 中張牌
                                               p2, p3, p4, p5, p6, p7, p8,
                                               s2, s3, s4, s5, s6, s7, s8}};
  constexpr std::array<int, 7u> honor_tiles{{z1, z2, z3, z4, z5, z6, z7}};                                      // 字牌
  constexpr std::array<int, 6u> terminal_tiles{{m1, m9, p1, p9, s1, s9}};                                       // 老頭牌
  constexpr std::array<int, 13u> terminal_or_honor_tiles{{m1, m9, p1, p9, s1, s9, z1, z2, z3, z4, z5, z6, z7}}; // 幺九牌

  void menzenchin_tsumohou(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool is_open)
  {
    if (!is_open && config.is_tsumo) {
      UPDATE_YAKU(MENZENCHIN_TSUMOHOU);
    }
  }

  void riichi(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.riichi_type == RiichiType::RIICHI) {
      UPDATE_YAKU(RIICHI);
    }
  }

  void ippatsu(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.riichi_option == RiichiOption::IPPATSU) {
      UPDATE_YAKU(IPPATSU);
    }
  }

  void chankan(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.winning_option == WinningOption::CHANKAN) {
      UPDATE_YAKU(CHANKAN);
    }
  }

  void rinshan_kaihou(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.winning_option == WinningOption::RINSHAN_KAIHOU) {
      UPDATE_YAKU(RINSHAN_KAIHOU);
    }
  }

  void haitei_raoyue(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.winning_option == WinningOption::HAITEI_RAOYUE) {
      UPDATE_YAKU(HAITEI_RAOYUE);
    }
  }

  void houtei_raoyui(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.winning_option == WinningOption::HOUTEI_RAOYUI) {
      UPDATE_YAKU(HOUTEI_RAOYUI);
    }
  }

  void tanyaochuu(Result& result, const Blocks&, const Hand& hand, const Tile&, const Config&, const bool)
  {
    for (const int& tid : terminal_or_honor_tiles) {
      if (hand.tiles[tid]) return;
    }

    UPDATE_YAKU(TANYAOCHUU);
  }

  void iipeikou__ryanpeikou(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool is_open)
  {
    if (is_open) return;

    int cnt = 0;

    for (int tid = 0; tid < east; ++tid) {
      if (blocks[tid].num_closed_sequence >= 2) ++cnt;
    }

    if (cnt == 1) {
      UPDATE_YAKU(IIPEIKOU);
    }
    else if (cnt == 2) {
      UPDATE_YAKU(RYANPEIKOU);
    }
  }

  void yakuhai_east_seat(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.seat_wind) == static_cast<int>(east) &&
        exists_triplet(blocks[static_cast<int>(config.seat_wind)])) {
      UPDATE_YAKU(YAKUHAI_EAST_SEAT);
    }
  }

  void yakuhai_south_seat(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.seat_wind) == static_cast<int>(south) &&
        exists_triplet(blocks[static_cast<int>(config.seat_wind)])) {
      UPDATE_YAKU(YAKUHAI_SOUTH_SEAT);
    }
  }

  void yakuhai_west_seat(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.seat_wind) == static_cast<int>(west) &&
        exists_triplet(blocks[static_cast<int>(config.seat_wind)])) {
      UPDATE_YAKU(YAKUHAI_WEST_SEAT);
    }
  }

  void yakuhai_north_seat(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.seat_wind) == static_cast<int>(north) &&
        exists_triplet(blocks[static_cast<int>(config.seat_wind)])) {
      UPDATE_YAKU(YAKUHAI_NORTH_SEAT);
    }
  }

  void yakuhai_east_round(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.round_wind) == static_cast<int>(east) &&
        exists_triplet(blocks[static_cast<int>(config.round_wind)])) {
      UPDATE_YAKU(YAKUHAI_EAST_ROUND);
    }
  }

  void yakuhai_south_round(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.round_wind) == static_cast<int>(south) &&
        exists_triplet(blocks[static_cast<int>(config.round_wind)])) {
      UPDATE_YAKU(YAKUHAI_SOUTH_ROUND);
    }
  }

  void yakuhai_west_round(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.round_wind) == static_cast<int>(west) &&
        exists_triplet(blocks[static_cast<int>(config.round_wind)])) {
      UPDATE_YAKU(YAKUHAI_WEST_ROUND);
    }
  }

  void yakuhai_north_round(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (static_cast<int>(config.round_wind) == static_cast<int>(north) &&
        exists_triplet(blocks[static_cast<int>(config.round_wind)])) {
      UPDATE_YAKU(YAKUHAI_NORTH_ROUND);
    }
  }

  void yakuhai_white(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    if (exists_triplet(blocks[white])) {
      UPDATE_YAKU(YAKUHAI_WHITE);
    }
  }

  void yakuhai_green(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    if (exists_triplet(blocks[green])) {
      UPDATE_YAKU(YAKUHAI_GREEN);
    }
  }

  void yakuhai_red(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    if (exists_triplet(blocks[red])) {
      UPDATE_YAKU(YAKUHAI_RED);
    }
  }

  void double_riichi(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.riichi_type == RiichiType::DOUBLE_RIICHI) {
      UPDATE_YAKU(DOUBLE_RIICHI);
    }
  }

  void chiitoitsu(Result& result, const Blocks&, const Hand&, const Tile&, const Config&, const bool)
  {
    UPDATE_YAKU(CHIITOITSU);
  }

  void honchantaiyaochuu__junchantaiyaochuu(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool is_open)
  {
    int cnt = 0;

    for (const auto& tile : {m1, m7, p1, p7, s1, s7}) {
      cnt += get_num_sequence(blocks[tile]);
    }

    if (cnt == 0) return;

    for (const int& tid : terminal_tiles) {
      if (exists_pair(blocks[tid]) || exists_triplet(blocks[tid])) ++cnt;
    }

    if (cnt == 5) {
      return UPDATE_YAKU_KUISAGARI(JUNCHANTAIYAOCHUU);
    }

    for (const int& tid : honor_tiles) {
      if (exists_pair(blocks[tid]) || exists_triplet(blocks[tid])) ++cnt;
    }

    if (cnt == 5) {
      UPDATE_YAKU_KUISAGARI(HONCHANTAIYAOCHUU);
    }
  }

  void ikkitsuukan(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool is_open)
  {
    for (int i = 0; i < 3; ++i) {
      if (get_num_sequence(blocks[9 * i]) &&
          get_num_sequence(blocks[9 * i + 3]) &&
          get_num_sequence(blocks[9 * i + 6])) {
        return UPDATE_YAKU_KUISAGARI(IKKITSUUKAN);
      }
    }
  }

  void sanshoku_doujun(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool is_open)
  {
    for (int i = 0; i < 7; ++i) {
      if (get_num_sequence(blocks[i]) &&
          get_num_sequence(blocks[i + 9]) &&
          get_num_sequence(blocks[i + 18])) {
        return UPDATE_YAKU_KUISAGARI(SANSHOKU_DOUJUN);
      }
    }
  }

  void sanshoku_doukou(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    for (int i = 0; i < 9; ++i) {
      if (exists_triplet(blocks[i]) &&
          exists_triplet(blocks[i + 9]) &&
          exists_triplet(blocks[i + 18])) {
        return UPDATE_YAKU(SANSHOKU_DOUKOU);
      }
    }
  }

  void sankantsu__suukantsu(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    if (int cnt = std::count_if(blocks.begin(), blocks.end(), [](const Block& block) { return exists_quad(block); }); cnt == 3) {
      UPDATE_YAKU(SANKANTSU);
    }
    else if (cnt == 4) {
      UPDATE_SINGLE_YAKUMAN(SUUKANTSU);
    }
  }

  void toitoihou(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    if (std::count_if(blocks.begin(), blocks.end(), [](const Block& block) { return exists_triplet(block); }) == 4) {
      UPDATE_YAKU(TOITOIHOU);
    }
  }

  void sanankou__suuankou(Result& result, const Blocks& blocks, const Hand&, const Tile& winning_tile, const Config& config, const bool)
  {
    if (int cnt = std::count_if(blocks.begin(), blocks.end(), [](const Block& block) { return exists_closed_triplet(block); }); cnt == 3) {
      UPDATE_YAKU(SANANKOU);
    }
    else if (cnt == 4) {
      if (exists_pair(blocks[winning_tile])) {
        UPDATE_DOUBLE_YAKUMAN(SUUANKOU_TANKI, config.enable_double_yakuman_suuankou);
      }
      else {
        UPDATE_SINGLE_YAKUMAN(SUUANKOU);
      }
    }
  }

  void shousangen__daisangen(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    int cnt = 0;

    for (const auto& tid : {z5, z6, z7}) {
      if (exists_triplet(blocks[tid])) ++cnt;
    }

    if (cnt == 3) {
      UPDATE_SINGLE_YAKUMAN(DAISANGEN);
    }
    else if (cnt == 2 && (exists_pair(blocks[z5]) || exists_pair(blocks[z6]) || exists_pair(blocks[z7]))) {
      UPDATE_YAKU(SHOUSANGEN);
    }
  }

  void honroutou__chinroutou(Result& result, const Blocks&, const Hand& hand, const Tile&, const Config&, const bool)
  {
    int cnt = 0;

    for (const int& tid : simple_tiles) {
      if (hand.tiles[tid] > 0) ++cnt;
    }

    if (cnt > 0) return;

    for (const int tid : honor_tiles) {
      if (hand.tiles[tid] > 0) ++cnt;
    }

    if (cnt > 0) {
      UPDATE_YAKU(HONROUTOU);
    }
    else {
      UPDATE_SINGLE_YAKUMAN(CHINROUTOU);
    }
  }

  void honiisou__chiniisou(Result& result, const Blocks&, const Hand& hand, const Tile&, const Config&, const bool is_open)
  {
    std::array<int, 4u> cnt{
        std::accumulate(&hand.tiles[0], &hand.tiles[9], 0),
        std::accumulate(&hand.tiles[9], &hand.tiles[18], 0),
        std::accumulate(&hand.tiles[18], &hand.tiles[27], 0),
        std::accumulate(&hand.tiles[27], &hand.tiles[NUM_TIDS], 0),
    };

    if (cnt[0] == 0 && cnt[1] == 0 && cnt[2] == 0) {
      UPDATE_SINGLE_YAKUMAN(TSUUIISOU);
    }
    else if ((cnt[0] == 0 && cnt[1] == 0) ||
             (cnt[0] == 0 && cnt[2] == 0) ||
             (cnt[1] == 0 && cnt[2] == 0)) {
      if (cnt[3] == 0) {
        UPDATE_YAKU_KUISAGARI(CHINIISOU);
      }
      else {
        UPDATE_YAKU_KUISAGARI(HONIISOU);
      }
    }
  }

  void tenhou(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.winning_option == WinningOption::TENHOU) {
      UPDATE_SINGLE_YAKUMAN(TENHOU);
    }
  }

  void chiihou(Result& result, const Blocks&, const Hand&, const Tile&, const Config& config, const bool)
  {
    if (config.winning_option == WinningOption::CHIIHOU) {
      UPDATE_SINGLE_YAKUMAN(CHIIHOU);
    }
  }

  void ryuuiisou(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config&, const bool)
  {
    int cnt = 0;

    for (const auto& tile : {s2, s3, s4, s6, s8, z6}) {
      if (exists_pair(blocks[tile]) || exists_triplet(blocks[tile])) ++cnt;
    }

    cnt += get_num_sequence(blocks[s2]);

    if (cnt == 5) {
      UPDATE_SINGLE_YAKUMAN(RYUUIISOU);
    }
  }

  void chuuren_poutou(Result& result, const Blocks&, const Hand& hand, const Tile& winning_tile, const Config& config, const bool is_open)
  {
    if (!is_open) {
      for (int i = 0; i < 3; ++i) {
        if (hand.tiles[9 * i] < 3 || hand.tiles[9 * i + 8] < 3) {
          continue;
        }

        if (std::any_of(&hand.tiles[9 * i + 1], &hand.tiles[9 * i + 8], [](const int x) { return x == 0; })) {
          continue;
        }

        if (std::accumulate(&hand.tiles[9 * i], &hand.tiles[9 * i + 9], 0) == 14) {
          if (hand.tiles[winning_tile] == 1 || hand.tiles[winning_tile] == 3) {
            return UPDATE_SINGLE_YAKUMAN(CHUUREN_POUTOU);
          }
          else {
            return UPDATE_DOUBLE_YAKUMAN(JUNSEI_CHUUREN_POUTOU, config.enable_double_yakuman_chuuren_poutou);
          }
        }
      }
    }
  }

  void kokushi_musou(Result& result, const Blocks&, const Hand& hand, const Tile& winning_tile, const Config& config, const bool)
  {
    if (hand.tiles[winning_tile] == 1) {
      UPDATE_SINGLE_YAKUMAN(KOKUSHI_MUSOU);
    }
    else {
      UPDATE_DOUBLE_YAKUMAN(KOKUSHI_MUSOU_13MENMACHI, config.enable_double_yakuman_kokushi_musou);
    }
  }

  void shousuushii__daisuushii(Result& result, const Blocks& blocks, const Hand&, const Tile&, const Config& config, const bool)
  {
    int cnt = 0;

    for (const auto& tile : {z1, z2, z3, z4}) {
      if (exists_triplet(blocks[tile])) ++cnt;
    }

    if (cnt == 4) {
      UPDATE_DOUBLE_YAKUMAN(DAISUUSHII, config.enable_double_yakuman_daisuushi);
    }
    else if (cnt == 3 && (exists_pair(blocks[z1]) || exists_pair(blocks[z2]) || exists_pair(blocks[z3]) || exists_pair(blocks[z4]))) {
      UPDATE_SINGLE_YAKUMAN(SHOUSUUSHII);
    }
  }

  constexpr Arr dora_tiles{{m2, m3, m4, m5, m6, m7, m8, m9, m1, // ドラ
                            p2, p3, p4, p5, p6, p7, p8, p9, p1,
                            s2, s3, s4, s5, s6, s7, s8, s9, s1,
                            z2, z3, z4, z1, z6, z7, z5}};

  void dora(Result& result, const Blocks&, const Hand& hand, const Tile&, const Config& config, const bool)
  {
    int cnt = 0;

    for (const auto& tile : config.dora_indicators) {
      cnt += hand.tiles[dora_tiles[tile]];
    }

    if (cnt > 0) {
      result.update_yaku(YakuId::DORA, cnt);
    }
  }

  void ura_dora(Result& result, const Blocks&, const Hand& hand, const Tile&, const Config& config, const bool)
  {
    int cnt = 0;

    for (const auto& tile : config.ura_dora_indicators) {
      cnt += hand.tiles[dora_tiles[tile]];
    }

    if (config.riichi_type != std::nullopt) {
      result.update_yaku(YakuId::URA_DORA, cnt);
    }
  }

  void aka_dora(Result& result, const Blocks&, const Hand& hand, const Tile&, const Config&, const bool)
  {
    int cnt = 0;

    for (int tid = 0; tid < NUM_TIDS; ++tid) {
      if (hand.red_dora[tid] > 0) ++cnt;
    }

    if (cnt > 0) {
      result.update_yaku(YakuId::AKA_DORA, cnt);
    }
  }

  void standard::calc_yaku(Result& result, const Blocks& blocks, const Hand& hand, const Tile& winning_tile, const Config& config, const bool is_open)
  {
    menzenchin_tsumohou(result, blocks, hand, winning_tile, config, is_open);
    riichi(result, blocks, hand, winning_tile, config, is_open);
    ippatsu(result, blocks, hand, winning_tile, config, is_open);
    chankan(result, blocks, hand, winning_tile, config, is_open);
    rinshan_kaihou(result, blocks, hand, winning_tile, config, is_open);
    haitei_raoyue(result, blocks, hand, winning_tile, config, is_open);
    houtei_raoyui(result, blocks, hand, winning_tile, config, is_open);
    // NOTE: 平和判定関数はない
    tanyaochuu(result, blocks, hand, winning_tile, config, is_open);
    iipeikou__ryanpeikou(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_east_seat(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_south_seat(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_west_seat(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_north_seat(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_east_round(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_south_round(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_west_round(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_north_round(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_white(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_green(result, blocks, hand, winning_tile, config, is_open);
    yakuhai_red(result, blocks, hand, winning_tile, config, is_open);
    double_riichi(result, blocks, hand, winning_tile, config, is_open);
    honchantaiyaochuu__junchantaiyaochuu(result, blocks, hand, winning_tile, config, is_open);
    ikkitsuukan(result, blocks, hand, winning_tile, config, is_open);
    sanshoku_doujun(result, blocks, hand, winning_tile, config, is_open);
    sanshoku_doukou(result, blocks, hand, winning_tile, config, is_open);
    sankantsu__suukantsu(result, blocks, hand, winning_tile, config, is_open);
    toitoihou(result, blocks, hand, winning_tile, config, is_open);
    sanankou__suuankou(result, blocks, hand, winning_tile, config, is_open);
    shousangen__daisangen(result, blocks, hand, winning_tile, config, is_open);
    honroutou__chinroutou(result, blocks, hand, winning_tile, config, is_open);
    honiisou__chiniisou(result, blocks, hand, winning_tile, config, is_open);
    tenhou(result, blocks, hand, winning_tile, config, is_open);
    chiihou(result, blocks, hand, winning_tile, config, is_open);
    ryuuiisou(result, blocks, hand, winning_tile, config, is_open);
    chuuren_poutou(result, blocks, hand, winning_tile, config, is_open);
    shousuushii__daisuushii(result, blocks, hand, winning_tile, config, is_open);

    if (result.num_han > 0) {
      dora(result, blocks, hand, winning_tile, config, is_open);
      ura_dora(result, blocks, hand, winning_tile, config, is_open);
      aka_dora(result, blocks, hand, winning_tile, config, is_open);
    }
  }

  void seven_pairs::calc_yaku(Result& result, const Hand& hand, const Tile& winning_tile, const Config& config)
  {
    menzenchin_tsumohou(result, {}, hand, winning_tile, config, false);
    riichi(result, {}, hand, winning_tile, config, false);
    ippatsu(result, {}, hand, winning_tile, config, false);
    chankan(result, {}, hand, winning_tile, config, false);
    rinshan_kaihou(result, {}, hand, winning_tile, config, false);
    haitei_raoyue(result, {}, hand, winning_tile, config, false);
    houtei_raoyui(result, {}, hand, winning_tile, config, false);
    tanyaochuu(result, {}, hand, winning_tile, config, false);
    double_riichi(result, {}, hand, winning_tile, config, false);
    chiitoitsu(result, {}, hand, winning_tile, config, false);
    honroutou__chinroutou(result, {}, hand, winning_tile, config, false);
    honiisou__chiniisou(result, {}, hand, winning_tile, config, false);
    dora(result, {}, hand, winning_tile, config, false);
    ura_dora(result, {}, hand, winning_tile, config, false);
    aka_dora(result, {}, hand, winning_tile, config, false);
  }

  void thirteen_orphans::calc_yaku(Result& result, const Hand& hand, const Tile& winning_tile, const Config& config)
  {
    kokushi_musou(result, {}, hand, winning_tile, config, false);
    tenhou(result, {}, hand, winning_tile, config, false);
    chiihou(result, {}, hand, winning_tile, config, false);
  }
}
