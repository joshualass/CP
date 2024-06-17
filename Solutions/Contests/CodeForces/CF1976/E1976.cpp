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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> lq(q), rq(q);
    for(int &x : lq) cin >> x;
    for(int &x : rq) cin >> x;
    vector<bool> vis(n);
    vector<int> lefts(n,-1), rights(n,-1);
    for(int i = 0; i < q; i++) {
        int l = lq[i] - 1;
        int r = rq[i] - 1;
        // cout << "ok at query : " << i << endl;
        if(lefts[r] != -1) {
            int ll = lefts[r];
            rights[ll] = l;
            rights[l] = r;
            lefts[l] = ll;
            lefts[r] = l;
        } else if(rights[l] != -1) {
            int rr = rights[l];
            rights[l] = r;
            rights[r] = rr;
            lefts[rr] = r;
            lefts[r] = l;
        } else {
            rights[l] = r;
            lefts[r] = l;
        }
        vis[l] = 1;
        vis[r] = 1;
        // cout << "success" << endl;
    }

    int startidx = -1;
    for(int i = 0; i < n; i++) {
        if(vis[i] && lefts[i] == -1) startidx = i;
    }

    // cout << "lefts : " << lefts << endl;
    // cout << "rights : " << rights << endl;

    vector<int> buckets;
    buckets.push_back(startidx);
    while(rights[startidx] != -1) {
        // cout << "next pair : " << startidx << ", " << rights[startidx];
        buckets.push_back(max(startidx, rights[startidx]));
        startidx = rights[startidx];
    }
    buckets.push_back(startidx);
    sort(buckets.begin(), buckets.end());
    // cout << "buckets : " << buckets << endl;

    ll res = 1;

    ll spots = 0;
    int bucketsptr = buckets.size() - 1;
    for(int i = n - 1; i >= 0; i--) {
        while(bucketsptr != -1 && i <= buckets[bucketsptr]) {
            // cout << "inequality ? i : " << i << " buckets[ptr] : " << buckets[bucketsptr] << '\n';
            bucketsptr--;
            spots++;
        }
        // cout << "i : " << i << " spots : " << spots << " ptr : " << bucketsptr << '\n';
        if(vis[i] == 0) {
            res = res * spots % MOD;
            spots++;
        }
    }
    cout << res << '\n';
    // cerr << "ended" << endl;
    return 0;
}