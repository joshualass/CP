#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Tree {
    typedef ll T; //update the data type, currently int. often update to ll
    static constexpr T base = 0;
    T f(T a, T b) {
        return (a + b) % MOD; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

struct custom_sort {
    template<typename T>
    bool operator()(const T &left, const T &right) { //define how to sort these elements
        if(left.first == right.first) {
            return left.second > right.second;
        } else {
            return left.first < right.first;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> order(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        order[i] = {num,i};

    }
    Tree tree(n);
    sort(order.begin(),order.end(), custom_sort());
    for(int i = 0; i < n; i++) {
        // cout << "order: " << order[i].second << "\n";
        tree.update(order[i].second, tree.query(0,order[i].second) + 1);
    }
    cout << tree.query(0,n) << "\n";
    return 0;
}