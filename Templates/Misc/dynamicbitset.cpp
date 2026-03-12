const int MAXLEN = 500001;
template <int len = 1>
int solve(int n) {
    if(n > len) {
        return solve<min(len * 2, MAXLEN)>(n);
    }
    bitset<len> dp {};
    //solve this way
}
