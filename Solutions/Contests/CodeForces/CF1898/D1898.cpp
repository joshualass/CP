#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll tester(vector<ll> a, vector<ll> b, ll one, ll two) {
    ll loidx = -1;
    ll hiidx = -1;
    ll lo = LLONG_MAX;
    ll hi = LLONG_MIN;
    for(ll i = 0; i < a.size(); i++) {
        if(one == 0) {
            if(a[i] + b[i] + (a[i] - b[i]) < lo) {
                lo = a[i] + b[i] + (a[i] - b[i]) ;
                loidx = i;
            }
        } else if(one == 1) {
            if(a[i] + b[i] + (b[i] - a[i]) < lo) {
                lo = a[i] + b[i] + (b[i] - a[i]);
                loidx = i;                
            }
        } else {
            if(a[i] + b[i] + abs(b[i] - a[i]) < lo) {
                lo = a[i] + b[i] + abs(b[i] - a[i]);
                loidx = i;                
            }            
        }
        if(two == 0) {
            if(a[i] + b[i] - (a[i] - b[i]) > hi) {
                hi = a[i] + b[i] - (a[i] - b[i]);
                hiidx = i;
            }
        } else if(two == 1) {
            if(a[i] + b[i] - (b[i] - a[i]) > hi) {
                hi = a[i] + b[i] - (b[i] - a[i]);
                hiidx = i;                
            }
        } else {
            if(a[i] + b[i] - abs(b[i] - a[i]) > hi) {
                hi = a[i] + b[i] - abs(b[i] - a[i]);
                hiidx = i;                
            }            
        }
    }
    swap(b[loidx],b[hiidx]);
    ll ans = 0;
    for(ll i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
    }
    return ans;
}

ll tester1(vector<ll> a, vector<ll> b, ll one, ll two) {
    ll loidx = -1;
    ll hiidx = -1;
    ll lo = LLONG_MAX;
    ll hi = LLONG_MIN;
    for(ll i = 0; i < a.size(); i++) {
        if(one == 0) {
            if(a[i] + b[i] + (a[i] - b[i]) < lo) {
                lo = a[i] + b[i] + (a[i] - b[i]) ;
                loidx = i;
            }
        } else if(one == 1) {
            if(a[i] + b[i] + (b[i] - a[i]) < lo) {
                lo = a[i] + b[i] + (b[i] - a[i]);
                loidx = i;                
            }
        } else {
            if(a[i] + b[i] + abs(b[i] - a[i]) < lo) {
                lo = a[i] + b[i] + abs(b[i] - a[i]);
                loidx = i;                
            }            
        }
        if(two == 0) {
            if(a[i] + b[i] + (a[i] - b[i]) > hi) {
                hi = a[i] + b[i] + (a[i] - b[i]);
                hiidx = i;
            }
        } else if(two == 1) {
            if(a[i] + b[i] + (b[i] - a[i]) > hi) {
                hi = a[i] + b[i] + (b[i] - a[i]);
                hiidx = i;                
            }
        } else {
            if(a[i] + b[i] + abs(b[i] - a[i]) > hi) {
                hi = a[i] + b[i] + abs(b[i] - a[i]);
                hiidx = i;                
            }            
        }
    }
    swap(b[loidx],b[hiidx]);
    ll ans = 0;
    for(ll i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
    }
    return ans;
}

ll tester2(vector<ll> a, vector<ll> b, ll one, ll two) {
    ll loidx = -1;
    ll hiidx = -1;
    ll lo = LLONG_MAX;
    ll hi = LLONG_MIN;
    for(ll i = 0; i < a.size(); i++) {
        if(one == 0) {
            if(a[i] + b[i] - (a[i] - b[i]) < lo) {
                lo = a[i] + b[i] - (a[i] - b[i]) ;
                loidx = i;
            }
        } else if(one == 1) {
            if(a[i] + b[i] - (b[i] - a[i]) < lo) {
                lo = a[i] + b[i] - (b[i] - a[i]);
                loidx = i;                
            }
        } else {
            if(a[i] + b[i] - abs(b[i] - a[i]) < lo) {
                lo = a[i] + b[i] - abs(b[i] - a[i]);
                loidx = i;                
            }            
        }
        if(two == 0) {
            if(a[i] + b[i] + (a[i] - b[i]) > hi) {
                hi = a[i] + b[i] + (a[i] - b[i]);
                hiidx = i;
            }
        } else if(two == 1) {
            if(a[i] + b[i] + (b[i] - a[i]) > hi) {
                hi = a[i] + b[i] + (b[i] - a[i]);
                hiidx = i;                
            }
        } else {
            if(a[i] + b[i] + abs(b[i] - a[i]) > hi) {
                hi = a[i] + b[i] + abs(b[i] - a[i]);
                hiidx = i;                
            }            
        }
    }
    swap(b[loidx],b[hiidx]);
    ll ans = 0;
    for(ll i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
    }
    return ans;
}

ll tester3(vector<ll> a, vector<ll> b, ll one, ll two) {
    ll loidx = -1;
    ll hiidx = -1;
    ll lo = LLONG_MAX;
    ll hi = LLONG_MIN;
    for(ll i = 0; i < a.size(); i++) {
        if(one == 0) {
            if(a[i] + b[i] - (a[i] - b[i]) < lo) {
                lo = a[i] + b[i] - (a[i] - b[i]) ;
                loidx = i;
            }
        } else if(one == 1) {
            if(a[i] + b[i] - (b[i] - a[i]) < lo) {
                lo = a[i] + b[i] - (b[i] - a[i]);
                loidx = i;                
            }
        } else {
            if(a[i] + b[i] - abs(b[i] - a[i]) < lo) {
                lo = a[i] + b[i] - abs(b[i] - a[i]);
                loidx = i;                
            }            
        }
        if(two == 0) {
            if(a[i] + b[i] - (a[i] - b[i]) > hi) {
                hi = a[i] + b[i] - (a[i] - b[i]);
                hiidx = i;
            }
        } else if(two == 1) {
            if(a[i] + b[i] - (b[i] - a[i]) > hi) {
                hi = a[i] + b[i] - (b[i] - a[i]);
                hiidx = i;                
            }
        } else {
            if(a[i] + b[i] - abs(b[i] - a[i]) > hi) {
                hi = a[i] + b[i] - abs(b[i] - a[i]);
                hiidx = i;                
            }            
        }
    }
    swap(b[loidx],b[hiidx]);
    ll ans = 0;
    for(ll i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
    }
    return ans;
}

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);

    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    vector<pair<ll,ll>> diffs(n);
    ll ans1 = 0;
    for(ll i = 0; i < n; i++) {
        diffs[i] = {b[i] - a[i], i};
        ans1 += abs(b[i] - a[i]);
    }

    sort(diffs.begin(), diffs.end());
    ll lptr = 0, rptr = n - 1;
    ll best = -1;
    pair<ll,ll> idxs = {-1,-1};
    while(lptr != rptr) {
        if(diffs[rptr].first - diffs[lptr].first > best) {
            best = diffs[rptr].first - diffs[lptr].first;
            idxs = {diffs[rptr].second,diffs[lptr].second};
        }
        if(abs(lptr) > rptr) {
            lptr++;
        } else {
            rptr--;
        }
    }
    swap(b[idxs.first], b[idxs.second]);
    ll ans = 0;
    for(ll i = 0; i < n; i++) {
        ans += abs(b[i] - a[i]);
    }
    swap(b[idxs.first], b[idxs.second]);
    // cout << max({ans,ans1,tester(a,b,0,0),tester(a,b,1,0),tester(a,b,0,1),tester(a,b,1,1),tester(a,b,2,1),tester(a,b,1,2),tester(a,b,2,2),tester(a,b,0,2),tester(a,b,2,0)}) << '\n';
    ans = max({ans,ans1,tester(a,b,0,0),tester(a,b,1,0),tester(a,b,0,1),tester(a,b,1,1),tester(a,b,2,1),tester(a,b,1,2),tester(a,b,2,2),tester(a,b,0,2),tester(a,b,2,0)});
    ans = max({ans,tester1(a,b,0,0),tester1(a,b,1,0),tester1(a,b,0,1),tester1(a,b,1,1),tester1(a,b,2,1),tester1(a,b,1,2),tester1(a,b,2,2),tester1(a,b,0,2),tester1(a,b,2,0)});
    ans = max({ans,tester2(a,b,0,0),tester2(a,b,1,0),tester2(a,b,0,1),tester2(a,b,1,1),tester2(a,b,2,1),tester2(a,b,1,2),tester2(a,b,2,2),tester2(a,b,0,2),tester2(a,b,2,0)});
    ans = max({ans,tester3(a,b,0,0),tester3(a,b,1,0),tester3(a,b,0,1),tester3(a,b,1,1),tester3(a,b,2,1),tester3(a,b,1,2),tester3(a,b,2,2),tester3(a,b,0,2),tester3(a,b,2,0)});
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}