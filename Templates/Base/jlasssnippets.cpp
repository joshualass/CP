template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int MAXLEN = 500001;
template <int len = 1>
int solve(int n) {
    if(n > len) {
        return solve<min(len * 2, MAXLEN)>(n);
    }
    bitset<len> dp {};
    //solve this way
}
