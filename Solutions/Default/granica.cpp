#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void find_divs(map<ll,ll>::iterator it, ll p, map<ll,ll> &facts, set<ll> &nums) {
    if(it == facts.end()) {
        if(p != 1) {
            nums.insert(p);
        }
        return;
    }
    for(int j = 0; j < (*it).second + 1; j++) {
        find_divs(++it, p, facts, nums);
        --it;
        p *= (*it).first;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    ll num = -1;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(num == -1) {
                num = abs(v[i] - v[j]);
            } else {
                num = gcd(num, abs(v[i] - v[j]));
            }
        }
    }

    map<ll,ll> factors;
    for(ll i = 2; i * i <= num; i++) {
        while(num % i == 0) {
            if(factors.find(i) == factors.end()) {
                factors[i] = 1;
            } else {
                factors[i]++;
            }
            num /= i;
        }
    }
    if(num != 1) {
        if(factors.find(num) == factors.end()) {
            factors[num] = 1;
        } else {
            factors[num]++;
        }
    }
    set<ll> ans;
    find_divs(factors.begin(), 1, factors, ans);
    for(auto x : ans) cout << x << " ";
    cout << "\n";

    return 0;
}