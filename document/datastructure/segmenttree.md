# segmenttree
```cpp
template <typename S, auto op, auto e>
class segmenttree
```
単一要素の更新，区間での演算結果の取得が高速に行えるデータ構造. 以下列の長さを $N$ とする.
# method
## set
```cpp
void set(int pos, S x)
```
$pos$ 番目の要素を $x$ に変更する.
- $O(\log N)$ time
## add
```cpp
void add(int pos, S x)
```
$pos$ 番目の要素に $x$ を加算する. `S`に`operator+=()`が定義されている必要がある.
- $O(\log N)$ time
## apply
```cpp
void apply(int pos, S x, const std::function<S(S, S)>& f)
```
$pos$ 番目の要素に $x$ を作用させる.
- $O(\log N)$ time
## fold
```cpp
S fold(int l, int r)
```
区間 $[l, r)$ における演算結果を返す.
- $O(\log N)$ time
## all_fold
```cpp
S all_fold()
```
全要素での演算結果を返す.
- $O(1)$ time
## operator[]
```cpp
S operator[](int pos)
```
$pos$ 番目の要素の値を返す.
- $O(1)$ time
## max_right
```cpp
int max_right(int l, const std::function<bool(S)>& f)
```
