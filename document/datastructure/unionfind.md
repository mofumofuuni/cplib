# unionfind
```cpp
class unionfind
```
頂点間の辺の追加，連結判定が高速に行えるデータ構造. 以下頂点数を $N$ とする.
# method
## root
```cpp
int root(int x)
```
頂点 $x$ が属する連結成分の代表の頂点番号を返す.
- $\mathrm{amortized} O(\alpha(N))$ time
## merge
```cpp
bool merge(int u, int v)
```
頂点 $u, v$ 間に辺を追加する(連結成分の併合). 既に同じ連結成分にあれば`false`を返し，そうでなければ`true`を返す.
- $\mathrm{amortized} O(\alpha(N))$ time
## same
```cpp
bool same(int u, int v)
```
頂点 $u, v$ が同じ連結成分に属するならば`true`，そうでなければ`false`を返す.
- $\mathrm{amortized} O(\alpha(N))$ time
## size
```cpp
int size(int x)
```
頂点 $x$ が属する連結成分の大きさを返す.
- $\mathrm{amortized} O(\alpha(N))$ time
## groups
```cpp
std::vector<std::vector<int>> groups()
```
連結成分ごとに`vector`にまとめた`vector`を返す.
- $\mathrm{amortized} O(N\alpha(N))$ time
