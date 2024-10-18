static constexpr const unsigned int BUF_SIZE = 1 << 17;

class Cinstream {
    private:
    unsigned int p = BUF_SIZE;
    static char Q[BUF_SIZE];

    template <typename T, int sp = 1>
    T nextUint() {
        if constexpr (sp) skipspace();
        T buf = 0;
        while (true) {
            char tmp = seekchar();
            if ('9' < tmp || tmp < '0') break;
            buf = buf * 10 + (tmp - ('0'));
            ++p;
        }
        return buf;
    }

    public:
    char seekchar() {
        if (p == BUF_SIZE) {
            size_t len = fread(Q, 1, BUF_SIZE, stdin);
            if (len != BUF_SIZE) Q[len] = '\0';
            p = 0;
        }
        return Q[p];
    }

    void skipspace() { while (isspace(seekchar())) ++p; }

    uint32_t nextU32() { return nextUint<uint32_t>(); }
    int32_t nextI32() {
        skipspace();
        if (seekchar() == '-') { ++p; return (int32_t)(-nextUint<uint32_t, 0>()); }
        return (int32_t)nextUint<uint32_t, 0>();
    }

    uint64_t nextU64() { return nextUint<uint64_t>(); }
    int64_t nextI64() {
        skipspace();
        if (seekchar() == '-') { ++p; return (int64_t)(-nextUint<int64_t, 0>()); }
        return (int64_t)nextUint<int64_t, 0>();
    }

    template <typename T>
    T nextInt() {
        skipspace();
        if (seekchar() == '-') { ++p; return -nextUint<T, 0>(); }
        return nextUint<T, 0>();
    }

    char nextchar() { skipspace(); char buf = seekchar(); ++p; return buf; }

    std::string nextToken() {
        skipspace();
        std::string buf;
        while (true) {
            char c = seekchar();
            if (isspace(c) || c == '\0') break;
            buf.push_back(c);
            ++p;
        }
        return buf;
    }

    double nextDouble() {
        skipspace();
        char buf[32];
        char *ptr = buf;
        while (true) {
            char c = seekchar();
            if (isspace(c) || c == '\0') break;
            *ptr++ = c;
            ++p;
        }
        *ptr = '\0';
        return std::atof(buf);
    }

    long double nextLdouble() {
        skipspace();
        char buf[32];
        char *ptr = buf;
        while (true) {
            char c = seekchar();
            if (isspace(c) || c == '\0') break;
            *ptr++ = c;
            ++p;
        }
        *ptr = '\0';
        return std::strtold(buf, nullptr);
    }

    Cinstream& operator>>(unsigned int& dest) { dest = nextU32(); return *this; }
    Cinstream& operator>>(int& dest) { dest = nextI32(); return *this; }
    Cinstream& operator>>(unsigned long& dest) { dest = nextU64(); return *this; }
    Cinstream& operator>>(long& dest) { dest = nextI64(); return *this; }
    Cinstream& operator>>(unsigned long long& dest) { dest = nextU64(); return *this; }
    Cinstream& operator>>(long long& dest) { dest = nextU64(); return *this; }
    Cinstream& operator>>(double& dest) { dest = nextDouble(); return *this; }
    Cinstream& operator>>(long double& dest) { dest = nextLdouble(); return *this; }
    Cinstream& operator>>(std::string& dest) { dest = nextToken(); return *this; }
    Cinstream& operator>>(char& dest) { dest = nextchar(); return *this; }
} cin;

struct fastoutputtable {
    char LZ[1000][4] = {};
    char NLZ[1000][4] = {};
    constexpr fastoutputtable() {
        using u32 = uint_fast32_t;
        for (u32 i = 0; i < 1000; ++i) {
            LZ[i][0] = ('0' + i / 100 % 10);
            LZ[i][1] = ('0' + i / 10 % 10);
            LZ[i][2] = ('0' + i % 10);
            LZ[i][3] = '\0'; 
        }
        for (u32 i = 0; i < 1000; ++i) {
            u32 j = 0;
            if (i >= 100) NLZ[i][j++] = ('0' + i / 100 % 10);
            if (i >= 10) NLZ[i][j++] = ('0' + i / 10 % 10);
            if (i >= 1) NLZ[i][j++] = ('0' + i % 10);
            NLZ[i][j++] = '\0';
        }
    }
};

class Coutstream {
    private:
    using u32 = uint32_t;
    using u64 = uint64_t;
    static char Q[BUF_SIZE];
    static constexpr fastoutputtable TB = fastoutputtable();
    u32 P10[10];
    u64 P10L[19];
    u32 p = 0;
    
    template <typename T, typename U>
    static void Fil(T& m, U& l, U x) { m = l / x; l -= m * x; }

    public:
    void next_dig9(u32 x) {
        u32 y;
        Fil(y, x, P10[6]);
        nextcstr(TB.LZ[y]);
        Fil(y, x, P10[3]);
        nextcstr(TB.LZ[y]), nextcstr(TB.LZ[x]);
    }

    void nextchar(char c) {
        Q[p++] = c;
        if (p == BUF_SIZE) { fwrite(Q, p, 1, stdout); p = 0; }
    }

    void nexteoln() { nextchar('\n'); }

    void nextcstr(const char* s) { while (*s) nextchar(*(s++)); }

    void nextU32(uint32_t x) {
        u32 y = 0;
        if (x >= P10[9]) {
            Fil(y, x, P10[9]);
            nextcstr(TB.NLZ[y]), next_dig9(x);
        }
        else if (x >= P10[6]) {
            Fil(y, x, P10[6]);
            nextcstr(TB.NLZ[y]);
            Fil(y, x, P10[3]);
            nextcstr(TB.LZ[y]), nextcstr(TB.LZ[x]);
        }
        else if (x >= P10[3]) {
            Fil(y, x, P10[3]);
            nextcstr(TB.NLZ[y]), nextcstr(TB.LZ[x]);
        }
        else if (x >= 1) nextcstr(TB.NLZ[x]);
        else nextchar('0');
    }

    void nextI32(int32_t x) {
        if (x >= 0) nextU32(x);
        else nextchar('-'), nextU32((u32)-x);
    }

    void nextU64(uint64_t x) {
        u32 y = 0;
        if (x >= P10L[18]) {
            Fil(y, x, P10L[18]);
            nextU32(y);
            Fil(y, x, P10L[9]);
            next_dig9(y), next_dig9(x);
        }
        else if (x >= P10L[9]) {
            Fil(y, x, P10L[9]);
            nextU32(y), next_dig9(x);
        }
        else nextU32(x);
    }

    void nextI64(int64_t x) {
        if (x >= 0) nextU64(x);
        else nextchar('-'), nextU64((u64)-x);
    }

    template <typename T>
    void nextInt(T x) {
        if (x < 0) nextchar('-'), x = -x;
        if (!(0 < x)) { nextchar('0'); return; }
        std::string buf;
        while (0 < x) {
            buf.push_back('0' + (int)(x % 10));
            x /= 10;
        }
        for (int i = (int)buf.size() - 1; i >= 0; --i) nextchar(buf[i]);
    }

    void nextDouble(double x) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%.12f", x);
        nextcstr(buf);
    }

    void nextLdouble(long double x) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%.12Lf", x);
        nextcstr(buf);
    }

    void writetoFile(bool flush = false) {
        fwrite(Q, p, 1, stdout);
        if (flush) fflush(stdout);
        p = 0;
    }

    Coutstream() {
        Q[0] = 0;
        P10[0] = P10L[0] = 1;
        for (int i = 1; i <= 9; ++i) P10[i] = P10[i - 1] * 10;
        for (int i = 1; i <= 18; ++i) P10L[i] = P10L[i - 1] * 10;
    }
    ~Coutstream() { writetoFile(); }

    Coutstream& operator<<(unsigned int tg) { nextU32(tg); return *this; }
    Coutstream& operator<<(int tg) { nextI32(tg); return *this; }
    Coutstream& operator<<(unsigned long tg) { nextU64(tg); return *this; }
    Coutstream& operator<<(long tg) { nextI64(tg); return *this; }
    Coutstream& operator<<(unsigned long long tg) { nextU64(tg); return *this; }
    Coutstream& operator<<(long long tg) { nextI64(tg); return *this; }
    Coutstream& operator<<(const std::string& tg) { nextcstr(tg.c_str()); return *this; }
    Coutstream& operator<<(const char* tg) { nextcstr(tg); return *this; }
    Coutstream& operator<<(char tg) { nextchar(tg); return *this; }
    Coutstream& operator<<(double tg) { nextDouble(tg); return *this;}
    Coutstream& operator<<(long double tg) { nextLdouble(tg); return *this; }
} cout;

char Cinstream::Q[BUF_SIZE];
char Coutstream::Q[BUF_SIZE];
