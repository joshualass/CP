#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll max_score_disjoint_subarrays_with_cost(const vector<ll>& a, ll cost) {
    const ll NEG_INF = -(1LL << 60);

    ll out = 0;        // best score with no active segment
    ll in = NEG_INF;   // best score with an active segment

    for (ll x : a) {
        ll new_in = max(in + x, out + x - cost);
        ll new_out = max(out, in);

        in = new_in;
        out = new_out;
    }

    return max(out, in);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll cost;
    cin >> n >> cost;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << max_score_disjoint_subarrays_with_cost(a, cost) << '\n';
    return 0;
}