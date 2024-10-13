# floyd_warshall
```cpp
template <typename T = long long>
class floyd_warshall
```
重み付き有向グラフにおける全点間最短経路問題を $O(N^3)$ で解く.
# method
## constructer
```cpp
(1) floyd_warshall(int n)
(2) floyd_warshall(int n, const T& Inf)
```
(1)はグラフの頂点数のみを指定し， $\infty$ として`std::numeric_limits<T>::max()`が使われる. (2)は $\infty$ の値を自分で指定する.
- $O(N)$ time
## static_addedge
```cpp
void static_addedge(int u, int v, const T& cost)
```
$(u, v)$ 間に重み $cost$ の有向辺の追加を行う. 更新は行わないので，`build()`を呼んだ後は使わないこと.
- $O(1)$ time
## build
```cpp
void build()
```
Floyd-Warshall Algorithm により全点間の最短距離を求める.
- $O(N^3)$ time
## dynamic_addedge
```cpp
void dymainc_addedge(int u, int v, const T& cost)
```
$(u, v)$ 間に重み $cost$ の有向辺を追加し最短距離の更新を行う.
- $O(N^2)$ time
