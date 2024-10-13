template <typename T = long long>
class floyd_warshall {
    private:
    std::vector<std::vector<T>> M_dp;
    int M_size;

    public:
    floyd_warshall() {}
    explicit floyd_warshall(int n) : M_dp(n, std::vector<T>(n, std::numeric_limits<T>::max())), M_size(n) {
        for (int i = 0; i < M_size; ++i) M_dp[i][i] = 0;
    }
    explicit floyd_warshall(int n, const T& Inf) : M_dp(n, std::vector<T>(n, Inf)), M_size(n) {
        for (int i = 0; i < M_size; ++i) M_dp[i][i] = 0;
    }

    void static_addedge(int u, int v, const T& cost) { M_dp[u][v] = cost; }

    void build() {
        for (int k = 0; k < M_size; ++k) {
            for (int i = 0; i < M_size; ++i) {
                for (int j = 0; j < M_size; ++j) M_dp[i][j] = std::min(M_dp[i][j], M_dp[i][k] + M_dp[k][j]);
            }
        }
    }

    void dynamic_addedge(int u, int v, const T& cost) {
        if (M_dp[u][v] < cost) return;
        M_dp[u][v] = cost;
        for (int i = 0; i < M_size; ++i) {
            for (int j = 0; j < M_size; ++j) M_dp[i][j] = std::min(M_dp[i][j], M_dp[i][u] + cost + M_dp[v][j]);
        }
    }

    T dist(int u, int v) const { return M_dp[u][v]; }
};
