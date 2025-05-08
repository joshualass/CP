#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, k; cin >> n >> k;

    k++;
    if(k < 0) {
        cout << "No\n";
        return;
    }

    vector<array<int,2>> a;

    priority_queue<array<int,4>> pq;
    pq.push({(int) (n - 1), 1, (int) n, 0});
    while(pq.size()) {
        auto [d, l, r, p] = pq.top();
        pq.pop();
        if(l == r) continue;
        a.push_back({p, l});

        int num_children = min(r - l - 1, ((int) sqrt(k * 2)));
        while(1LL * num_children * (num_children + 1) / 2 > k) num_children--;
        while(1LL * (num_children + 1) * (num_children + 2) / 2 <= k && num_children < r - l - 1) num_children++;

        k -= 1LL * num_children * (num_children + 1) / 2;
        l++;
        int m = l + num_children;
        pq.push({m - l, l, m, l - 1});
        pq.push({r - m, m, r, p});
    }

    if(k <= 2) {
        cout << "Yes\n";
        for(auto edge : a) cout << edge[0] + 1 << " " << edge[1] + 1 << '\n';
    } else {
        cout << "No\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}