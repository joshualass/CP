#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pii> a(n);
    set<int> l, r;
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
        if(a[i].first % 2 == 0){
            l.insert(a[i].first);
        }
        if(a[i].second % 2 == 0){
            r.insert(a[i].second);
        }
    }
    if(n == 1){
        cout << "NO\n";
        return 0;
    }
    if(l.size() != n){
        int x = -1;
        for(int i = 1; i <= n; i++){
            if(!l.count(i * 2)){
                x = i;
                break;
            }
        }
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << x << " " << (i + 1) << "\n";
        }
        return 0;
    }
    else if(r.size() != n){
        int x = -1;
        for(int i = 1; i <= n; i++){
            if(!r.count(i * 2)) {
                x = i;
                break;
            }
        }
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << (i + 1) << " " << x << "\n";
        }
        return 0;
    }
    int maxl = -1;
    for(int i = 0; i < n; i++){
        if(a[i].second == n * 2){
            maxl = a[i].first;
            break;
        }
    }
    vector<pii> ans(0);
    for(int i = 1; i < n; i++){
        ans.push_back({maxl / 2, i});
    }
    int parl = -1;
    for(int i = 0; i < n; i++){
        if(abs(a[i].first / 2 - maxl / 2) % 2 == 1){
            if(a[i].second == 2){
                ans.push_back({a[i].first / 2, 2});
            }
            else {
                ans.push_back({a[i].first / 2, 1});
            }
            break;
        }
    }

    // {
    //     assert(ans.size() == n);
    //     set<pii> as;
    //     for(int i = 0; i < n; i++){
    //         as.insert(a[i]);
    //     }
    //     set<pii> bs;
    //     for(int i = 0; i < n; i++){
    //         assert(bs.count(ans[i]) == 0);
    //         bs.insert(ans[i]);
    //         for(int j = i; j < n; j++){
    //             pii cur = {ans[i].first + ans[j].first, ans[i].second + ans[j].second};
    //             // assert(as.count(cur) == 0);
    //             if(as.count(cur)) {
    //                 cout << "cur : " << cur << '\n';
    //                 cout << "i : " << i << " pi : " << ans[i] << '\n';
    //                 cout << "j : " << j << " pj : " << ans[j] << '\n';
    //                 return 0;
    //             }
    //         }
    //         assert(1 <= ans[i].first && ans[i].first <= n);
    //         assert(1 <= ans[i].second && ans[i].second <= n);
    //     }
    // }


    cout << "YES\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}