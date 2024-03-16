#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> as(int n, int k, int s) {
    int ms = k / 2 + 1;
    vector<int> a(n);
    set<int> nums;
    set<int> idxs;
    for(int i = 0; i < n; i++) {
        nums.insert(i);
        idxs.insert(i);
    }
    int i = 0;
    while(nums.size()) {
        if(i & 1) {
            int startnum = (*--nums.end());
            int startidx = max((*--idxs.end() - ms + 1), *idxs.begin());
            while(idxs.count(startidx)) {
                a[startidx] = startnum;
                idxs.erase(startidx++);
                nums.erase(startnum--);
            }
        } else {
            int startnum = *nums.begin();
            int startidx = min((*--idxs.end()), (*idxs.begin()) + ms - 1);
            while(idxs.count(startidx)) {
                a[startidx] = startnum;
                idxs.erase(startidx--);
                nums.erase(startnum++);
            }
        }
        i++;
    }
    // cout << "n : " << n << " k : " << k << " a : " << a << '\n';
    for(int i = 0; i < n; i++) {
        a[i] += s;
    }
    return a;
}

bool bc(int n, int k) {
    vector<int> res = as(n,k,0);
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(j - i + abs(res[j]-res[i]) > k) return 0;
        }
    }
    return 1;
}

void solve() {
    int n, k; cin >> n >> k;
    int sz = 0;
    for(int i = 1; i <= n; i++) {
        if(bc(i,k)) sz = i;
    }
    vector<int> ans(n);
    for(int i = 0; i < n; i += sz) {
        int s = min(sz, n - i);
        vector<int> v = as(s,k,i+1);
        for(int j = 0; j < s; j++) {
            ans[i+j] = v[j];
        }
    }
    cout << "sz : " << sz << '\n';
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
    cout << ((n + sz - 1) / sz) << '\n';
    for(int i = 0; i < n; i += sz) {
        for(int j = 0; j < sz && j + i < n; j++) {
            cout << i / sz + 1 << " ";
        }
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}