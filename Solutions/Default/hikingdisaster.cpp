#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void prllV(const vector<ll> &x) {
    cout << " --- vector --- \n";
    for(auto y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

ll solve(vector<ll> v, ll k) {
    // prllV(v);
    
    ll n = v.size();
    if(n + 1 < k) {
        return 0;
    }
    vector<set<ll>> idxs(k);
    for(ll i = 0; i < n; i++) {
        if(v[i] < k) {
            idxs[v[i]].insert(i);
        }
    }

    map<ll,ll> m;
    ll hi = -1;
    for(ll i = 0; i < n; i++) {
        if(v[i] < k) {
            if(m.find(v[i]) == m.end()) {
                // m[v[i]] = 1;
                m.insert({v[i],1});
            } else {
                m[v[i]]++;
            }
        }
        if(m.size() == k) {
            hi = i;
            break;
        }
    }
    if(m.size() != k) {
        return 0;
    }
    ll cnt = n - hi;
    // cout << "make it here?" << "\n";
    for(ll i = 0; i < n - 1; i++) {
        ll remove = v[i];
        if(remove > k) {
            cnt += n - hi;
            continue;
        }
        if(m[remove] == 1) {
            if(idxs[remove].upper_bound(hi) == idxs[remove].end()) {
                return cnt;
            } else {
                ll new_hi = (*idxs[remove].upper_bound(hi));
                for(ll i = hi + 1; i < new_hi; i++) {
                    if(m.find(v[i]) == m.end()) {
                        m[v[i]] = 1;
                    } else {
                        m[v[i]]++;
                    }                 
                }
                hi = new_hi;
                cnt += n - hi;
            }
        } else {
            m[remove]--;
            cnt += n - hi;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    vector<ll> temp(0);
    ll ans = 0;
        for(ll i = 0; i < n; i++) {
        if(v[i] == k) {
            if(temp.size() > 0) {
                ans += solve(temp,k);
            }
            temp.clear();
        } else {
            temp.push_back(v[i]);
        }
    }
    if(temp.size() != 0) {
        ans += solve(temp,k);
    }
    cout << ans << "\n";
    return 0;
}