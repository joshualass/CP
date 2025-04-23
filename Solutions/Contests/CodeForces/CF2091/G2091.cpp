#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {

    int s, k; cin >> s >> k;
    int res = 1;



    auto get_next = [&](vector<int> a) -> vector<int> {
        int nxk = max(1, k - 1);
        vector<int> b(nxk, -1);

        priority_queue<array<int,2>> pq;
        for(int i = 0; i < a.size(); i++) {
            if(a[i] != -1) {
                pq.push({i + (s - i) / k * k, a[i] + k});
            }
        }

        while(pq.size()) {
            auto [idx, stop] = pq.top();
            pq.pop();
            if(b[idx % (nxk)] != -1) continue;
            b[idx % (nxk)] = idx;
            if(idx - k >= stop) pq.push({idx - k, stop});
        }

        // cout << "k : " << k << " a : " << a << '\n';
        // cout << "nxk : " << nxk << " b : " << b << '\n';

        vector<int> res(nxk, -1);
        for(int i = 0; i < nxk; i++) {
            if(b[i] != -1) {
                res[(s - b[i]) % (nxk)] = s - b[i];
            }
        }
        return res;
    };

    vector<int> a(k, -1);
    a[0] = 0;

    while(1) {
        a = get_next(a);
        if(a[0] == 0) {
            cout << k << '\n';
            return;
        }
        k = max(1, k - 1);
        a = get_next(a);
        k = max(1, k - 1);
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}