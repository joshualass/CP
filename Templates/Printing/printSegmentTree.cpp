std::ostream& operator<<(std::ostream& os, const Tree &t) {
    for(auto x : t.s) os << x << " ";
    return os;
}