template <typename S, typename T, typename U>
struct trio {
    public:
    S first;
    T second;
    U third;

    trio() {}
    trio(const S& f, const T& s, const U& t) : first(f), second(s), third(t) {}
    trio(S&& f, T&& s, U&& t) : first(std::move<S>(f)), second(std::move<T>(s)), third(std::move<U>(t)) {}

    trio& operator=(const trio& rhs) { first = rhs.first; second = rhs.second; third = rhs.third; return *this; }
    trio& operator=(trio&& rhs) { first = rhs.first; second = rhs.second; third = rhs.third; return *this; }

    bool operator<(const trio& rhs) const {
        return first < rhs.first || (first == rhs.first && second < rhs.second) || (first == rhs.first && second == rhs.second && third < rhs.third);
    }
    bool operator<=(const trio& rhs) const {
        return first < rhs.first || (first == rhs.first && second < rhs.second) || (first == rhs.first && second == rhs.second && third <= rhs.third);
    }
    bool operator>(const trio& rhs) const {
        return first > rhs.first || (first == rhs.first && second > rhs.second) || (first == rhs.first && second == rhs.second && third > rhs.third);
    }
    bool operator>=(const trio& rhs) const {
        return first > rhs.first || (first == rhs.first && second > rhs.second) || (first == rhs.first && second == rhs.second && third >= rhs.third);
    }
    bool operator==(const trio& rhs) const {
        return first == rhs.first && second == rhs.second && third == rhs.third;
    }
    bool operator!=(const trio& rhs) const {
        return first != rhs.first || second != rhs.second || third != rhs.third;
    }
};
