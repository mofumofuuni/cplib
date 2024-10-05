namespace Math {
    
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

// Linear Sieve
std::vector<int> lpfsieve(int n) {
    std::vector<int> lpf(n + 1), primes;
    std::iota(lpf.begin(), lpf.end(), 0);
    for (int i = 2; i <= n; ++i) {
        if (lpf[i] == i) primes.push_back(i);
        int lpf_i = lpf[i];
        for (int j : primes) {
            if (i * j > n) break;
            lpf[i * j] = j;
        }
    }
    return lpf;
}

// a^{-1} (mod m)
long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0, q;
    while (b) {
        q = a / b;
        a -= q * b, std::swap(a, b);
        u -= q * v, std::swap(u, v);
    }
    u %= m;
    return u >= 0 ? u : u + m;
}

};

using namespace Math;
