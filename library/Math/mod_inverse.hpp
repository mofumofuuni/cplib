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
