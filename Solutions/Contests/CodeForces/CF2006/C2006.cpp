#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//64 priority queues is needed to solve this problem. 

priority_queue<int> one;
priority_queue<int> two;
priority_queue<int> three;
priority_queue<int> four;
priority_queue<int> five;
priority_queue<int> six;
priority_queue<int> seven;
priority_queue<int> eight;
priority_queue<int> nine;
priority_queue<int> ten;
priority_queue<int> eleven;
priority_queue<int> twelve;
priority_queue<int> thirteen;
priority_queue<int> fourteen;
priority_queue<int> fifteen;
priority_queue<int> sixteen;
priority_queue<int> seventeen;
priority_queue<int> eighteen;
priority_queue<int> nineteen;
priority_queue<int> twenty;
priority_queue<int> twentyone;
priority_queue<int> twentytwo;
priority_queue<int> twentythree;
priority_queue<int> twentyfour;
priority_queue<int> twentyfive;
priority_queue<int> twentysix;
priority_queue<int> twentyseven;
priority_queue<int> twentyeight;
priority_queue<int> twentynine;
priority_queue<int> thirty;
priority_queue<int> thirtyone;
priority_queue<int> thirtytwo;
priority_queue<int> thirtythree;
priority_queue<int> thirtyfour;
priority_queue<int> thirtyfive;
priority_queue<int> thirtysix;
priority_queue<int> thirtyseven;
priority_queue<int> thirtyeight;
priority_queue<int> thirtynine;
priority_queue<int> forty;
priority_queue<int> fortyone;
priority_queue<int> fortytwo;
priority_queue<int> fortythree;
priority_queue<int> fortyfour;
priority_queue<int> fortyfive;
priority_queue<int> fortysix;
priority_queue<int> fortyseven;
priority_queue<int> fortyeight;
priority_queue<int> fortynine;
priority_queue<int> fifty;
priority_queue<int> fiftyone;
priority_queue<int> fiftytwo;
priority_queue<int> fiftythree;
priority_queue<int> fiftyfour;
priority_queue<int> fiftyfive;
priority_queue<int> fiftysix;
priority_queue<int> fiftyseven;
priority_queue<int> fiftyeight;
priority_queue<int> fiftynine;
priority_queue<int> sixty;
priority_queue<int> sixtyone;
priority_queue<int> sixtytwo;
priority_queue<int> sixtythree;
priority_queue<int> sixtyfour;

// Sparse Table template. Fresh off the press. 

template<typename T>
struct sparse {

    vector<vector<T>> sparsetable;
    int n, d;

    sparse() {}

    sparse(vector<T> a) {
        buildTable(a);
    }

    T op(T a, T b) {
        return gcd(a,b);
    }

    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));

        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }

    }

    //[l,r) always. 
    T query(int l, int r) {
        assert(r > l && l >= 0 && r <= n);
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }

};

void solve() {
    
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> d(n-1);
    for(int i = 1; i < n; i++) {
        d[i - 1] = abs(a[i] - a[i-1]);
    }
    
    sparse<int> table(d);

    ll res = 0;
    int same = -1;
    int g = 0;
    for(int i = 0; i < n; i++) {
        same = max(same, i);
        while(same != n - 1 && a[same + 1] == a[same]) {
            same++;
        }

        int l = i, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(__builtin_popcount(table.query(i, m)) != 1) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        res += (n - l - 1) + (same - i + 1);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}