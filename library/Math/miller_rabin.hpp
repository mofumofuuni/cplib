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
