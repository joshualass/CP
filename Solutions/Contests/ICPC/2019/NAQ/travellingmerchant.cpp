#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve(vector<ll>& v, vector<ll>& d, vector<pair<int, pair<int, int>>>& q, vector<ll>& ans) {
    int block = (int) (sqrt(v.size()) + 1e-9);
    int n = v.size();
    vector<ll> coeff = {0, 1, 2, 3, 2, 1, 0};
    vector<vector<ll>> val(7, vector<ll>(n, 0));
    vector<vector<ll>> p_max(7, vector<ll>(block, 0)), b_min(7, vector<ll>(block, 1e18)), s_max(7, vector<ll>(block, 0));
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < n; j++){
            ll c = coeff[(j + 7 - i) % 7];
            val[i][j] = v[j] + c * d[j];
        }
        for(int j = 0; j < block; j++){
            for(int k = 0; k < block; k++){
                int ind = j * block + k;
                b_min[i][j] = min(b_min[i][j], val[i][ind]);
                s_max[i][j] = max(s_max[i][j], val[i][ind]);
                p_max[i][j] = max(p_max[i][j], val[i][ind] - b_min[i][j]);
            }
        }
    }
    for(int i = 0; i < q.size(); i++){
        int ans_ind = q[i].first;
        int s = q[i].second.first;
        int t = q[i].second.second;
        int mod = s % 7;
        ll min_b = 1e18;
        ll cur_ans = 0;
        int ptr = s;
        while(ptr % block != 0 && ptr != t){
            min_b = min(min_b, val[mod][ptr]);
            cur_ans = max(cur_ans, val[mod][ptr] - min_b);
            ptr ++;
        }
        while(ptr + block <= t) {
            int block_ind = ptr / block;
            cur_ans = max(cur_ans, p_max[mod][block_ind]);
            cur_ans = max(cur_ans, s_max[mod][block_ind] - min_b);
            min_b = min(min_b, b_min[mod][block_ind]);
            ptr += block;
        }
        while(ptr <= t) {
            min_b = min(min_b, val[mod][ptr]);
            cur_ans = max(cur_ans, val[mod][ptr] - min_b);
            ptr ++;
        }
        ans[ans_ind] = cur_ans;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> v(n), d(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        cin >> d[i];
    }
    int n_ps = 1;
    while(n_ps * n_ps < n){
        n_ps ++;
    }
    n_ps *= n_ps;
    while(n != n_ps) {
        v.push_back(0);
        d.push_back(0);
        n ++;
    }
    int q;
    cin >> q;
    vector<pair<int, pair<int, int>>> fq(0), rq(0);
    for(int i = 0; i < q; i++){
        int s, t;
        cin >> s >> t;
        s --;
        t --;
        if(s < t) {
            fq.push_back({i, {s, t}});
        }
        else {
            rq.push_back({i, {n - 1 - s, n - 1 - t}});
        }
    }
    vector<ll> ans(q);
    solve(v, d, fq, ans);
    reverse(v.begin(), v.end());
    reverse(d.begin(), d.end());
    solve(v, d, rq, ans);
    for(int i = 0; i < q; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}