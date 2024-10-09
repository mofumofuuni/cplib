class unionfind {
    private:std::vector<int> M_tree;

    public:
    unionfind() {}
    explicit unionfind(unsigned int n) : M_tree(n, -1) {}

    int root(int x) {
        int res = x;
        while (M_tree[res] >= 0) res = M_tree[res];
        int now;
        while (M_tree[x] >= 0) {
            now = x;
            x = M_tree[x];
            M_tree[now] = res;
        }return res;
    }
    
    bool merge(int u, int v) {
        u = root(u), v = root(v);
        if (u == v) return false;
        if (M_tree[u] > M_tree[v]) std::swap(u, v);
        M_tree[u] += M_tree[v];
        M_tree[v] = u;
        return true;
    }
    
    bool same(int u, int v) { return root(u) == root(v); }
    
    int size(int x) { return -M_tree[root(x)]; }
    
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> mem(M_tree.size()), res;
        for (int i = 0; i < M_tree.size(); ++i) mem[root(i)].push_back(i);
        for (int i = 0; i < M_tree.size(); ++i) {
            if (!mem[i].empty()) res.emplace_back(mem[i]);
        }
        return res;
    }
};
