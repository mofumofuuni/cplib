# fastIO
```cpp
class Cinstream
class Coutstream
```
入出力高速化のためのクラス. `(unsigned)int, (unsigned)long, (unsigned)long long, std::string, char, double, long double`に加え，各自クラス内で定義すれば自作クラスの入出力も可能.
また，`std::pair, std::vector`の入出力にも対応している.
- 浮動小数点数は小数点以下12桁
- `std::pair，std::vector`は空白区切りで出力
