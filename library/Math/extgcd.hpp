// Extended Euclidian Algorithm (ax+by=gcd(a,b))
long long extgcd(long long a, long long b, long long& x, long long& y) {
    x = 1, y = 0;
    long long u = 0, v = 1, q, tmp;
    while (b) {
        q = a / b;
        a -= q * b, swap(a, b);
        x -= q * u, swap(x, u);
        y -= q * v, swap(y, v);
    }
    return a;
}
