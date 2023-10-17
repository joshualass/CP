template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) os << x.first << " - " << x.second << "| ";
    return os;
}