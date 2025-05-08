#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    ll n, m, k; cin >> n >> m >> k;

    vector<ll> a(n), used(n);

    for (auto& x : a)
        cin >> x;
    
    int le = -m+1;
    ll curr = 0;
    stack<pair<ll, ll>> st; // {val, idx}
    ll cnt = 0;
    while (le < n) {
        int ri = le + m - 1;
        if (ri < n) {
            st.push({a[ri], ri});
        }

        // cerr << "le : " << le << " ri : " << ri << " curr : " << curr << endl;


        while (curr < k && st.size()) {
            auto p = st.top();
            st.pop();
            if (p.second < le)
                continue;
            ll diff = k - curr;
            ll tmp = min(diff, p.first);
            // cerr << "idx : " << p.second << " buying : " << tmp << endl;
            curr += tmp;
            used[p.second] += tmp;
            p.first -= tmp;
            // cnt += tmp;
            if (p.first)
                st.push(p);
        }

        
        if (le >= 0) {
            curr -= used[le];
        }
        le++;
    }

    for (auto x : used)
        cnt += x;

    cout << cnt << endl;

    return 0;
}