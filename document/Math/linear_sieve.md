# linear_sieve
```cpp
std::vector<int> lpfsieve(int n)
```
長さ $N+1$ の $\mathrm{lpf}$ (最小素因数)が格納された配列を返す. 実装は線形篩.
$N$ の値がある程度小さければ $N$ 以下の数をクエリ $O(\log N)$ time で素因数分解できる.
約数列挙はDFSで $O(\prod (素因数の指数))$ time でできそう.
- $O(N)$ time
