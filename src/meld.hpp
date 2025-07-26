#ifndef SCORE_CALCULATOR_MELD_HPP
#define SCORE_CALCULATOR_MELD_HPP

#include "tile.hpp"
#include <vector>

namespace score_calculator {
  class Meld {
  private:
    MeldType meld_type;
    Tiles tiles;
    int min_index;

  public:
    Meld(const MeldType& meld_type, const Tiles& tiles) : meld_type(meld_type), tiles(tiles)
    {
      min_index = std::min_element(tiles.begin(), tiles.end())->index;
    }

    const MeldType& get_meld_type() const { return meld_type; }
    const Tiles& get_tiles() const { return tiles; }
    const int& get_min_index() const { return min_index; }

    bool operator==(const Meld& rhs) const { return meld_type == rhs.meld_type && tiles == rhs.tiles; }
  };

  using Melds = std::vector<Meld>;

  inline const Meld pon_m111{MeldType::PON, {m1, m1, m1}};
  inline const Meld pon_m222{MeldType::PON, {m2, m2, m2}};
  inline const Meld pon_m333{MeldType::PON, {m3, m3, m3}};
  inline const Meld pon_m444{MeldType::PON, {m4, m4, m4}};
  inline const Meld pon_m555{MeldType::PON, {m5, m5, m5}};
  inline const Meld pon_m666{MeldType::PON, {m6, m6, m6}};
  inline const Meld pon_m777{MeldType::PON, {m7, m7, m7}};
  inline const Meld pon_m888{MeldType::PON, {m8, m8, m8}};
  inline const Meld pon_m999{MeldType::PON, {m9, m9, m9}};
  inline const Meld pon_p111{MeldType::PON, {p1, p1, p1}};
  inline const Meld pon_p222{MeldType::PON, {p2, p2, p2}};
  inline const Meld pon_p333{MeldType::PON, {p3, p3, p3}};
  inline const Meld pon_p444{MeldType::PON, {p4, p4, p4}};
  inline const Meld pon_p555{MeldType::PON, {p5, p5, p5}};
  inline const Meld pon_p666{MeldType::PON, {p6, p6, p6}};
  inline const Meld pon_p777{MeldType::PON, {p7, p7, p7}};
  inline const Meld pon_p888{MeldType::PON, {p8, p8, p8}};
  inline const Meld pon_p999{MeldType::PON, {p9, p9, p9}};
  inline const Meld pon_s111{MeldType::PON, {s1, s1, s1}};
  inline const Meld pon_s222{MeldType::PON, {s2, s2, s2}};
  inline const Meld pon_s333{MeldType::PON, {s3, s3, s3}};
  inline const Meld pon_s444{MeldType::PON, {s4, s4, s4}};
  inline const Meld pon_s555{MeldType::PON, {s5, s5, s5}};
  inline const Meld pon_s666{MeldType::PON, {s6, s6, s6}};
  inline const Meld pon_s777{MeldType::PON, {s7, s7, s7}};
  inline const Meld pon_s888{MeldType::PON, {s8, s8, s8}};
  inline const Meld pon_s999{MeldType::PON, {s9, s9, s9}};
  inline const Meld pon_z111{MeldType::PON, {z1, z1, z1}};
  inline const Meld pon_z222{MeldType::PON, {z2, z2, z2}};
  inline const Meld pon_z333{MeldType::PON, {z3, z3, z3}};
  inline const Meld pon_z444{MeldType::PON, {z4, z4, z4}};
  inline const Meld pon_z555{MeldType::PON, {z5, z5, z5}};
  inline const Meld pon_z666{MeldType::PON, {z6, z6, z6}};
  inline const Meld pon_z777{MeldType::PON, {z7, z7, z7}};

  inline const Meld chi_m123{MeldType::CHI, {m1, m2, m3}};
  inline const Meld chi_m234{MeldType::CHI, {m2, m3, m4}};
  inline const Meld chi_m345{MeldType::CHI, {m3, m4, m5}};
  inline const Meld chi_m456{MeldType::CHI, {m4, m5, m6}};
  inline const Meld chi_m567{MeldType::CHI, {m5, m6, m7}};
  inline const Meld chi_m678{MeldType::CHI, {m6, m7, m8}};
  inline const Meld chi_m789{MeldType::CHI, {m7, m8, m9}};
  inline const Meld chi_p123{MeldType::CHI, {p1, p2, p3}};
  inline const Meld chi_p234{MeldType::CHI, {p2, p3, p4}};
  inline const Meld chi_p345{MeldType::CHI, {p3, p4, p5}};
  inline const Meld chi_p456{MeldType::CHI, {p4, p5, p6}};
  inline const Meld chi_p567{MeldType::CHI, {p5, p6, p7}};
  inline const Meld chi_p678{MeldType::CHI, {p6, p7, p8}};
  inline const Meld chi_p789{MeldType::CHI, {p7, p8, p9}};
  inline const Meld chi_s123{MeldType::CHI, {s1, s2, s3}};
  inline const Meld chi_s234{MeldType::CHI, {s2, s3, s4}};
  inline const Meld chi_s345{MeldType::CHI, {s3, s4, s5}};
  inline const Meld chi_s456{MeldType::CHI, {s4, s5, s6}};
  inline const Meld chi_s567{MeldType::CHI, {s5, s6, s7}};
  inline const Meld chi_s678{MeldType::CHI, {s6, s7, s8}};
  inline const Meld chi_s789{MeldType::CHI, {s7, s8, s9}};

  inline const Meld minkan_m1111{MeldType::MINKAN, {m1, m1, m1, m1}};
  inline const Meld minkan_m2222{MeldType::MINKAN, {m2, m2, m2, m2}};
  inline const Meld minkan_m3333{MeldType::MINKAN, {m3, m3, m3, m3}};
  inline const Meld minkan_m4444{MeldType::MINKAN, {m4, m4, m4, m4}};
  inline const Meld minkan_m5555{MeldType::MINKAN, {m5, m5, m5, m5}};
  inline const Meld minkan_m6666{MeldType::MINKAN, {m6, m6, m6, m6}};
  inline const Meld minkan_m7777{MeldType::MINKAN, {m7, m7, m7, m7}};
  inline const Meld minkan_m8888{MeldType::MINKAN, {m8, m8, m8, m8}};
  inline const Meld minkan_m9999{MeldType::MINKAN, {m9, m9, m9, m9}};
  inline const Meld minkan_p1111{MeldType::MINKAN, {p1, p1, p1, p1}};
  inline const Meld minkan_p2222{MeldType::MINKAN, {p2, p2, p2, p2}};
  inline const Meld minkan_p3333{MeldType::MINKAN, {p3, p3, p3, p3}};
  inline const Meld minkan_p4444{MeldType::MINKAN, {p4, p4, p4, p4}};
  inline const Meld minkan_p5555{MeldType::MINKAN, {p5, p5, p5, p5}};
  inline const Meld minkan_p6666{MeldType::MINKAN, {p6, p6, p6, p6}};
  inline const Meld minkan_p7777{MeldType::MINKAN, {p7, p7, p7, p7}};
  inline const Meld minkan_p8888{MeldType::MINKAN, {p8, p8, p8, p8}};
  inline const Meld minkan_p9999{MeldType::MINKAN, {p9, p9, p9, p9}};
  inline const Meld minkan_s1111{MeldType::MINKAN, {s1, s1, s1, s1}};
  inline const Meld minkan_s2222{MeldType::MINKAN, {s2, s2, s2, s2}};
  inline const Meld minkan_s3333{MeldType::MINKAN, {s3, s3, s3, s3}};
  inline const Meld minkan_s4444{MeldType::MINKAN, {s4, s4, s4, s4}};
  inline const Meld minkan_s5555{MeldType::MINKAN, {s5, s5, s5, s5}};
  inline const Meld minkan_s6666{MeldType::MINKAN, {s6, s6, s6, s6}};
  inline const Meld minkan_s7777{MeldType::MINKAN, {s7, s7, s7, s7}};
  inline const Meld minkan_s8888{MeldType::MINKAN, {s8, s8, s8, s8}};
  inline const Meld minkan_s9999{MeldType::MINKAN, {s9, s9, s9, s9}};
  inline const Meld minkan_z1111{MeldType::MINKAN, {z1, z1, z1, z1}};
  inline const Meld minkan_z2222{MeldType::MINKAN, {z2, z2, z2, z2}};
  inline const Meld minkan_z3333{MeldType::MINKAN, {z3, z3, z3, z3}};
  inline const Meld minkan_z4444{MeldType::MINKAN, {z4, z4, z4, z4}};
  inline const Meld minkan_z5555{MeldType::MINKAN, {z5, z5, z5, z5}};
  inline const Meld minkan_z6666{MeldType::MINKAN, {z6, z6, z6, z6}};
  inline const Meld minkan_z7777{MeldType::MINKAN, {z7, z7, z7, z7}};

  inline const Meld ankan_m1111{MeldType::ANKAN, {m1, m1, m1, m1}};
  inline const Meld ankan_m2222{MeldType::ANKAN, {m2, m2, m2, m2}};
  inline const Meld ankan_m3333{MeldType::ANKAN, {m3, m3, m3, m3}};
  inline const Meld ankan_m4444{MeldType::ANKAN, {m4, m4, m4, m4}};
  inline const Meld ankan_m5555{MeldType::ANKAN, {m5, m5, m5, m5}};
  inline const Meld ankan_m6666{MeldType::ANKAN, {m6, m6, m6, m6}};
  inline const Meld ankan_m7777{MeldType::ANKAN, {m7, m7, m7, m7}};
  inline const Meld ankan_m8888{MeldType::ANKAN, {m8, m8, m8, m8}};
  inline const Meld ankan_m9999{MeldType::ANKAN, {m9, m9, m9, m9}};
  inline const Meld ankan_p1111{MeldType::ANKAN, {p1, p1, p1, p1}};
  inline const Meld ankan_p2222{MeldType::ANKAN, {p2, p2, p2, p2}};
  inline const Meld ankan_p3333{MeldType::ANKAN, {p3, p3, p3, p3}};
  inline const Meld ankan_p4444{MeldType::ANKAN, {p4, p4, p4, p4}};
  inline const Meld ankan_p5555{MeldType::ANKAN, {p5, p5, p5, p5}};
  inline const Meld ankan_p6666{MeldType::ANKAN, {p6, p6, p6, p6}};
  inline const Meld ankan_p7777{MeldType::ANKAN, {p7, p7, p7, p7}};
  inline const Meld ankan_p8888{MeldType::ANKAN, {p8, p8, p8, p8}};
  inline const Meld ankan_p9999{MeldType::ANKAN, {p9, p9, p9, p9}};
  inline const Meld ankan_s1111{MeldType::ANKAN, {s1, s1, s1, s1}};
  inline const Meld ankan_s2222{MeldType::ANKAN, {s2, s2, s2, s2}};
  inline const Meld ankan_s3333{MeldType::ANKAN, {s3, s3, s3, s3}};
  inline const Meld ankan_s4444{MeldType::ANKAN, {s4, s4, s4, s4}};
  inline const Meld ankan_s5555{MeldType::ANKAN, {s5, s5, s5, s5}};
  inline const Meld ankan_s6666{MeldType::ANKAN, {s6, s6, s6, s6}};
  inline const Meld ankan_s7777{MeldType::ANKAN, {s7, s7, s7, s7}};
  inline const Meld ankan_s8888{MeldType::ANKAN, {s8, s8, s8, s8}};
  inline const Meld ankan_s9999{MeldType::ANKAN, {s9, s9, s9, s9}};
  inline const Meld ankan_z1111{MeldType::ANKAN, {z1, z1, z1, z1}};
  inline const Meld ankan_z2222{MeldType::ANKAN, {z2, z2, z2, z2}};
  inline const Meld ankan_z3333{MeldType::ANKAN, {z3, z3, z3, z3}};
  inline const Meld ankan_z4444{MeldType::ANKAN, {z4, z4, z4, z4}};
  inline const Meld ankan_z5555{MeldType::ANKAN, {z5, z5, z5, z5}};
  inline const Meld ankan_z6666{MeldType::ANKAN, {z6, z6, z6, z6}};
  inline const Meld ankan_z7777{MeldType::ANKAN, {z7, z7, z7, z7}};
}

#endif
