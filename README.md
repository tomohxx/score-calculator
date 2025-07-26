# Score Calculator

A tool for calculating score in Japanese mahjong.

## Build

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=</path/to/install>
make
make install
```

## Usage

1. Define the hand.
1. Calculate *fu* and *han*.
1. Calculate each player's payments(as needed).
1. Calculate score(as needed).

## Examples

### Closed hand

```cpp
#include <cassert>
#include <score_calculator/core.hpp>
using namespace score_calculator;

int main()
{
  Hand hand{{m1, m2, m3, m7, m8, m9, p2, p3, p4, s5, s6, s7, z4, z4}};

  const Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = true,
  };

  const auto result = calc_fu_han(hand, {}, m1, config);

  assert(result.num_fu == 20);
  assert(result.num_han == 2);
  assert(result.reasons_yaku.at(YakuId::MENZENCHIN_TSUMOHOU) == 1);
  assert(result.reasons_yaku.at(YakuId::PINFU) == 1);

  const auto payment = static_cast<TsumoPayment&&>(*calc_payment(result, config));

  assert(payment.payment1 == 400);
  assert(payment.payment2 == 700);
  assert(payment.calc_score(config) == 1500);

  return EXIT_SUCCESS;
}
```

### Open hand

```cpp
#include <cassert>
#include <score_calculator/core.hpp>
using namespace score_calculator;

int main()
{
  Hand hand{{m1, m1, m1, m9, m9}};

  const Config config{
      .seat_wind = WindType::EAST,
      .round_wind = WindType::EAST,
      .is_tsumo = false,
  };

  Melds melds{{MeldType::PON, {m2, m2, m2}},
              {MeldType::PON, {s5, s5, s5}},
              {MeldType::PON, {z1, z1, z1}}};

  const auto result = calc_fu_han(hand, melds, m1, config);

  assert(result.num_fu == 40);
  assert(result.num_han == 4);
  assert(result.reasons_yaku.at(YakuId::YAKUHAI_EAST_SEAT) == 1);
  assert(result.reasons_yaku.at(YakuId::YAKUHAI_EAST_ROUND) == 1);
  assert(result.reasons_yaku.at(YakuId::TOITOIHOU) == 2);

  const auto payment = static_cast<RonPayment&&>(*calc_payment(result, config));

  assert(payment.payment == 12000);
  assert(payment.calc_score(config) == 12000);

  return EXIT_SUCCESS;
}
```

### Yakuman

```cpp
#include <cassert>
#include <score_calculator/core.hpp>
using namespace score_calculator;

int main()
{
  Hand hand{{m1, m9, p1, p9, s1, s9, z1, z2, z3, z4, z5, z6, z7, z7}};

  const Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = true,
  };

  const auto result = calc_fu_han(hand, {}, z1, config);

  assert(result.num_yakuman == 1);
  assert(result.reasons_yakuman.at(YakuId::KOKUSHI_MUSOU) == 1);

  const auto payment = static_cast<TsumoPayment&&>(*calc_payment(result, config));

  assert(payment.payment1 == 8000);
  assert(payment.payment2 == 16000);
  assert(payment.calc_score(config) == 32000);

  return EXIT_SUCCESS;
}
```

### Double Yakuman

```cpp
#include <cassert>
#include <score_calculator/core.hpp>
using namespace score_calculator;

int main()
{
  Hand hand{{m1, m9, p1, p9, s1, s9, z1, z2, z3, z4, z5, z6, z7, z7}};

  const Config config{
      .seat_wind = WindType::SOUTH,
      .round_wind = WindType::EAST,
      .is_tsumo = true,
      .enable_double_yakuman_kokushi_musou = true,
  };

  const auto result = calc_fu_han(hand, {}, z7, config);

  assert(result.num_yakuman == 2);
  assert(result.reasons_yakuman.at(YakuId::KOKUSHI_MUSOU_13MENMACHI) == 2);

  const auto payment = static_cast<TsumoPayment&&>(*calc_payment(result, config));

  assert(payment.payment1 == 16000);
  assert(payment.payment2 == 32000);
  assert(payment.calc_score(config) == 64000);

  return EXIT_SUCCESS;
}
```

## Tile expressions

### Number tiles

|         | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| *manzu* | `m1` | `m2` | `m3` | `m4` | `m5` | `m6` | `m7` | `m8` | `m9` |
| *pinzu* | `p1` | `p2` | `p3` | `p4` | `p5` | `p6` | `p7` | `p8` | `p9` |
| *souzu* | `s1` | `s2` | `s3` | `s4` | `s5` | `s6` | `s7` | `s8` | `s9` |

### Honor tiles

- `z1`, `z2`, `z3`, `z4`, `z5`, `z6`, `z7`

Following expressions also avaliable.

- `east`, `south`, `west`, `north`, `white`, `green`, `red`

### Red fives

- `m5r`, `p5r`, `s5r`

Following expressions also avaliable.

- `m0`, `p0`, `s0`

### User-defined literals

```cpp
#include <cassert>
#include <score_calculator/core.hpp>
using namespace score_calculator;
using namespace score_calculator::literals;

int main()
{
  const Hand hand1{{m1, m2, m3, m4, m5, m0, p7, s8, z1}};
  const Hand hand2{{1_m, 2_m, 3_m, 4_m, 5_m, 0_m, 7_p, 8_s, 1_z}};

  assert(hand1 == hand2);

  return EXIT_SUCCESS;
}
```

## Hand tiles manipulation

You can manipulate hand tiles with method chains as follows.

```cpp
#include <score_calculator/calc_score.hpp>
using namespace score_calculator;

int main()
{
  Hand hand{{m1, m2, m3, m4, m5}};

  // draw single tile
  hand.draw(p1).draw(p2).draw(p3);
  // discard single tile
  hand.discard(p1).discard(p2).discard(p3);
  // draw multple tiles
  hand.draw({p1, p2, p3});
  // discard multiple tiles
  hand.discard({p1, p2, p3});

  return EXIT_SUCCESS;
}
```

## Configulations

General rules(including three-player mahjong) are supported. See [config.hpp](src/config.hpp) for details.

## References

Mahjong terms in English taken from [Riichi.Wiki](https://riichi.wiki/Main_Page).

## License

MIT Licence.
