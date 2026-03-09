template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

