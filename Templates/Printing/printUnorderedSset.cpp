template<typename T>
std::ostream& operator<<(std::ostream& os, unordered_set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}