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
