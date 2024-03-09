template<typename T>
std::ostream& operator<<(std::ostream& os, const list<T> l) {
    for(auto &x : l) os << x << " ";
    return os;
}