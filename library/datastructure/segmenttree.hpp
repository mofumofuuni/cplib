template <typename S, auto op, auto e>
class segmenttree {
    private:
    std::vector<S> M_dat;
    unsigned int M_n, M_sz;

    public:
    segmenttree() : segmenttree(0) {}
    explicit segmenttree(unsigned n) : segmenttree(std::vector<S>(n, e())) {}
    explicit segmenttree(unsigned n, S i) : segmenttree(std::vector<S>(n, i)) {}
    explicit segmenttree(const std::vector<S>& v) : M_n(v.size()) {
        M_sz = 1;
        while (M_sz < v.size()) M_sz <<= 1;
        M_dat.assign(M_sz << 1, e());
        for (int i = 0; i < M_n; ++i) M_dat[M_sz + i] = v[i];
        for (int i = M_sz - 1; i >= 1; --i) M_dat[i] = op(M_dat[i << 1], M_dat[i << 1 | 1]);
    }
    explicit segmenttree(std::vector<S>&& v) : segmenttree(std::move<std::vector<S>>(v)) {}

    void set(int pos, S x) {
        pos += M_sz;
        M_dat[pos] = x;
        while (pos > 1) {
            pos >>= 1;
            M_dat[pos] = op(M_dat[pos << 1], M_dat[pos << 1 | 1]);
        }
    }

    void add(int pos, S x) {
        pos += sz;
        M_dat[pos] += x;
        while (pos > 1) {
            pos >>= 1;
            M_dat[pos] = op(M_dat[pos << 1], M_dat[pos << 1 | 1]);
        }
    }

    void apply(int pos, S x, const std::function<S(S, S)>& f) {
        pos += M_sz;
        M_dat[pos] = f(x, M_dat[pos]);
        while (pos > 1) {
            pos >>= 1;
            M_dat[pos] = op(M_dat[pos << 1], M_dat[pos << 1 | 1]);
        }
    }

    S fold(int l, int r) const {
        l += M_sz, r += M_sz;
        S resl = e(), resr = e();
        while (l < r) {
            if (l & 1) resl = op(resl, M_dat[l++]);
            if (r & 1) resr = op(M_dat[--r], resr);
            l >>= 1;
            r >>= 1;
        }
    }
    S all_fold() const { return M_dat[1]; }

    S operator[](int pos) { return M_dat[M_sz + pos]; }

    int max_right(int l, const std::function<bool(S)>& f) const {
        if (l == M_n) return M_n;
        l += M_sz;
        S t = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!f(op(t, M_dat[l]))) {
                while (l < M_sz) {
                    l <<= 1;
                    if (f(op(t, M_dat[l]))) t = op(t, M_dat[l++]);
                }
                return l - M_sz;
            }
            t = op(t, M_dat[l]);
            ++l;
        } while ((l & -l) != l);
        return M_n;
    }

    int min_left(int r, const std::function<bool(S)>& f) const {
        if (r == 0) return 0;
        r += M_sz;
        S t = e();
        do {
            --r;
            while (r > 1 && (r & 1) == 0) r >>= 1;
            if (!(f(op(M_dat[r], t)))) {
                while (r < M_sz) {
                    r = r << 1 | 1;
                    if (f(op(M_dat[r], t))) t = op(M_dat[r--], t);
                }
                return r - M_sz + 1;
            }
        } while ((r & -r) != r);
        return 0;
    }
};
