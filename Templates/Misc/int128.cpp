//orz Wobert nice int128 code
using i128 = __int128;
istream& operator>>(istream &is, i128 &x) {
    ll y; is >> y;
    x = y;
    return is;
}
// modified from https://codeforces.com/blog/entry/75044?#comment-1106835
ostream &operator<<(ostream &os, i128 x) {
    if (x == 0) return os << '0';
    if (x < 0) os << '-', x = -x;
    string s;
    while (x) s += char(x%10) + '0', x /= 10;
    reverse(s.begin(), s.end());
    return os << s;
}