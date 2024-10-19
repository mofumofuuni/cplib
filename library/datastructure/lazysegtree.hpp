template <typename S, auto op, auto e, typename F, auto mapping, auto composition, auto id>
class lazysegtree {
    private:
    std::vector<S> M_dat;
    std::vector<F> M_lazy;
    int M_n, M_size, M_log;

    void all_apply(int pos, F f) {
        M_dat[pos] = mapping(f, M_dat[pos]);
        if (pos < M_size) M_lazy[pos] = composition(f, M_lazy[pos]);
    }

    void pushdown(int pos) {
        all_apply(pos << 1, M_lazy[pos]);
        all_apply(pos << 1 | 1, M_lazy[pos]);
        M_lazy[pos] = id();
    }

    void pushup(int pos) { M_dat[pos] = op(M_dat[pos << 1], M_dat[pos << 1 | 1]); }

    public:
    lazysegtree() = default;
    explicit lazysegtree(int n) : lazysegtree(std::vector<S>(n, e())) {}
    explicit lazysegtree(int n, S i) : lazysegtree(std::vector<S>(n, i)) {}
    explicit lazysegtree(const std::vector<S>& v) : M_n((int)v.size()) {
        M_size = 1;
        while (M_size < M_n) M_size <<= 1;
        M_log = __builtin_ctz((unsigned int)M_size);
        M_dat.assign(M_size << 1, e());
        M_lazy.assign(M_size << 1, id());
        for (int i = 0; i < M_n; ++i) M_dat[i + M_size] = v[i];
        for (int i = M_size - 1; i >= 1; --i) pushup(i);
    }

    void set(int pos, S x) {
        pos += M_size;
        for (int i = M_log; i >= 1; --i) pushdown(pos >> i);
        M_dat[pos] = x;
        for (int i = 1; i <= M_log; ++i) pushup(pos >> i);
    }

    void add(int pos, S x) {
        pos += M_size;
        for (int i = M_log; i >= 1; --i) pushdown(pos >> i);
        M_dat[pos] += x;
        for (int i = 1; i <= M_log; ++i) pushup(pos >> i);
    }

    void apply(int pos, F f) {
        pos += M_size;
        for (int i = M_log; i >= 1; --i) pushdown(pos >> i);
        M_dat[pos] = mapping(f, M_dat[pos]);
        for (int i = 1; i <= M_log; ++i) pushup(pos >> i);
    }

    void apply(int l, int r, F f) {
        if (l == r) return;
        l += M_size, r += M_size;
        for (int i = M_log; i >= 1; --i) {
            if (((l >> i) << i) != l) pushdown(l >> i);
            if (((r >> i) << i) != r) pushdown((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= M_log; ++i) {
            if (((l >> i) << i) != l) pushup(l >> i);
            if (((r >> i) << i) != r) pushup((r - 1) >> i);
        }
    }

    S operator[](int pos) {
        pos += M_size;
        for (int i = M_log; i >= 1; --i) pushdown(pos >> i);
        return M_dat[pos];
    }

    S fold(int l, int r) {
        if (l == r) return e();
        l += M_size, r += M_size;
        for (int i = M_log; i >= 1; --i) {
            if (((l >> i) << i) != l) pushdown(l >> i);
            if (((r >> i) << i) != r) pushdown((r - 1) >> i);
        }
        S resl = e(), resr = e();
        while (l < r) {
            if (l & 1) resl = op(resl, M_dat[l++]);
            if (r & 1) resr = op(M_dat[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return op(resl, resr);
    }
    S all_fold() { return M_dat[1]; }

    int max_right(int l, const std::function<bool(S)>& g) {
        if (l == M_n) return M_n;
        l += M_size;
        for (int i = M_log; i >= 1; --i) pushdown(l >> i);
        S t = e();
        do {
            while (!(l & 1)) l >>= 1;
            if (!g(op(t, M_dat[l]))) {
                while (l < M_size) {
                    pushdown(l);
                    l <<= 1;
                    if (g(op(t, M_dat[l]))) t = op(t, M_dat[l++]);
                }
                return l - M_size;
            }
            t = op(t, M_dat[l]);
            ++l;
        } while ((l & -l) != l);
        return M_n;
    }

    int min_left(int r, const std::function<bool(S)>& g) {
        if (r == 0) return 0;
        r += M_size;
        for (int i = M_log; i >= 1; --i) pushdown((r - 1) >> i);
        S t = e();
        do {
            --r;
            while (r > 1 && !(r & 1)) r >>= 1;
            if (!g(op(M_dat[r], t))) {
                while (r < M_size) {
                    pushdown(r);
                    r = r << 1 | 1;
                    if (g(op(M_dat[r], t))) t = op(M_dat[r--], t);
                }
                return r - M_size + 1;
            }
            t = op(M_dat[r], t);
        } while((r & -r) != r);
        return 0;
    }
};
