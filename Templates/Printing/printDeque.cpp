template<typename T>
ostream& operator<<(ostream& os, const deque<T>& d) {
    for (auto x : d) os << x << " ";
    return os;
}