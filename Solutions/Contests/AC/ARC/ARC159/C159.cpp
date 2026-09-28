#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    if((n * 50 - accumulate(a.begin(), a.end(), 0)) % n % gcd(n,n * (n + 1) / 2)) {
        cout << "No\n";
        return 0;
    }
    
    vector<vector<int>> ops;

    auto add_perm = [&](vector<int> perm) -> void {
        ops.push_back(perm);
        for(int i = 0; i < n; i++) {
            a[i] += perm[i];
        }
    };

    while(accumulate(a.begin(), a.end(), 0) % n) {
        assert(ops.size() < 1000); //sanity check. this is bad. should not trigger though
        vector<array<int,2>> order(n);
        for(int i = 0; i < n; i++) {
            order[i] = {a[i], i};
        }
        sort(order.rbegin(),order.rend());
        vector<int> perm(n);
        for(int i = 1; i <= n; i++) {
            perm[order[i-1][1]] = i;
        }
        add_perm(perm);
    }

    auto moveone = [&](int lo, int hi) -> void {
        if(n == 2) {
            vector<int> perm(2);
            perm[lo] = 1;
            perm[hi] = 2;
            add_perm(perm);
        } else {
            int t = -1;
            for(int i = 0; i < n; i++) {
                if(i != lo && i != hi) {
                    t = i;
                    break;
                }
            }
            vector<int> p1(n), p2(n);
            int p1v = 2, p2v = n - 1;
            for(int i = 0; i < n; i++) {
                if(i != lo && i != hi && i != t) {
                    p1[i] = p1v++;
                    p2[i] = p2v--;
                }
            }

            p1[hi] = n;
            p1[t] = 1;
            p1[lo] = n - 1;

            p2[hi] = 2;
            p2[t] = n;
            p2[lo] = 1;
            add_perm(p1);
            add_perm(p2);
        }
    };

    while(count(a.begin(), a.end(), a[0]) != n) {
        assert(ops.size() < 10000);
        int loidx = 0, hiidx = 0;
        for(int i = 1; i < n; i++) {
            if(a[i] > a[hiidx]) {
                hiidx = i;
            }
            if(a[i] < a[loidx]) {
                loidx = i;
            }
        }
        moveone(hiidx, loidx);
    }

    cout << "Yes\n";

    cout << ops.size() << '\n';
    for(auto op : ops) {    
        for(int p : op) cout << p << " ";
        cout << '\n';
    }

    return 0;
}