// https://codeforces.com/contest/86/problem/D

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void expand_score(ll num, ll &curr_score, vector<ll> &m) {

    curr_score -= m[num] * m[num] * num;

    m[num]++;

    curr_score += m[num] * m[num] * num;

}

void shrink_score(ll num, ll& curr_score, vector<ll> &m) {

    curr_score -= m[num] * m[num] * num;

    m[num]--;

    curr_score += m[num] * m[num] * num;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    vector<array<ll,3>> queries(q);

    for(int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][0]--;
        queries[i][2] = i;
    }

    int block_size = sqrt(n);

    sort(queries.begin(), queries.end(), [&block_size](const array<ll,3> &lhs, const array<ll,3> &rhs) -> bool {
        
        //check if in the same block
        int lhs_block_idx = lhs[0] / block_size;
        int rhs_block_idx = rhs[0] / block_size;

        if(lhs_block_idx != rhs_block_idx) {
            return lhs_block_idx < rhs_block_idx;
        }
        if(lhs_block_idx & 1) {
            return lhs[1] > rhs[1];
        } else {
            return lhs[1] < rhs[1];
        }

    });

    vector<ll> ans(q);
    ll curr_score = 0;
    // map<ll,ll> m; // {the value, the frequency}
    vector<ll> m(1e6 + 1);
    ll lidx = 0, ridx = 0;
    for(int i = 0; i < q; i++) {
        
        while(queries[i][1] > ridx) {

            expand_score(v[ridx++], curr_score, m);

        }

        while(queries[i][0] < lidx) {

            expand_score(v[--lidx], curr_score, m);

        }

        while(queries[i][1] < ridx) {

            shrink_score(v[--ridx], curr_score, m);

        }

        while(queries[i][0] > lidx) {
            shrink_score(v[lidx++], curr_score, m);
        }

        ans[queries[i][2]] = curr_score;

    }

    for(auto &x: ans) cout << x << '\n';

    return 0;
}