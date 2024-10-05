# extgcd
```cpp
long long extgcd(long long a, long long b, long long& x, long long& y)
```
不定方程式 $ax+by=\gcd(a,b)$ を拡張ユークリッドの互除法によって解く. 返り値は $\gcd(a,b)$ で， $x, y$ の値は整数解の1つ.
- $O((\log a)(\log b))$ time
