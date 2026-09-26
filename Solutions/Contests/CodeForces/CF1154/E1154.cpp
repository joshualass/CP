#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    map<int,int> a, b;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
        b[x] = i;
    }
    vector<int> res(n);
    int turn = 0;
    while(!a.empty()) {

        int mx = (--b.end())->second;

        for(int i = 0; i < k + 1; i++) {
            auto it = a.lower_bound(mx);
            if(it == a.end()) break;
            int nx = a.lower_bound(mx)->first;
            res[nx] = turn + 1;
            b.erase(a[nx]);
            a.erase(nx);
        }

        for(int i = 0; i < k; i++) {
            auto it = a.lower_bound(mx);
            if(it == a.begin()) break;
            int nx = (--a.lower_bound(mx))->first;
            res[nx] = turn + 1;
            b.erase(a[nx]);
            a.erase(nx);
        }
        turn ^= 1;
    }

    for(int x : res) cout << x;
    cout << '\n';

    return 0;
}
