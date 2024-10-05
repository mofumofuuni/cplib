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

// Prime Judge
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    if (n < 4759123141LL) return miller_rabin(n, {2, 7, 61});
    else return miller_rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
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

// Miller-Rabin primality test
bool miller_rabin(long long n, std::vector<long long>&& vec) {
    std::vector<long long> A = std::move(vec);
    long long s = 0, d = n - 1;
    while (!(d & 1)) ++s, d >>= 1;
    for (auto a : A) {
        if (n <= a) return true;
        long long t, x = pow_mod<__int128_t>(a, d, n);
        if (x != 1) {
            for (t = 0; t < s; ++t) {
                if (x == n - 1) break;
                x = __int128_t(x) * x % n;
            }
            if (t == s) return false;
        }
    }
    return true;
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

//Fast a^n (mod m)
template <typename T = long long>
T pow_mod(T a, T n, T m) {
    T res = 1;
    a %= m;
    while (n) {
        if (n & 1) res = res * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return res;
}

};

using namespace Math;
