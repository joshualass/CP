#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<pair<int,int>> pc[100001];
ll prefs[100001];

void get_attacks(int n) {
    pc[n].push_back({1,n});
    while(pc[n].back().first != n) {
        int lo = pc[n].back().first + 1, hi = n;
        while(lo != hi) {
            int m = (lo + hi) / 2;
            if((n + m - 1) / m != pc[n].back().second) {
                hi = m;
            } else {
                lo = m + 1;
            }
        }
        pc[n].push_back({lo, (n + lo - 1) / lo});
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(prefs,0,sizeof(prefs));

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int m = *max_element(a.begin(), a.end());

    for(int i = 1; i <= 100000; i++) {
        // if(i % 10000 == 0) {
        //     cout << "i : " << i << endl;
        // }
        get_attacks(i);
    }

    //for the attack power, how many attacks are done
    int p = 0;
    pc[0] = {{0,0}};
    for(int i = 0; i < n; i++) {
        int num = a[i];
        // cout << "curr :( " << curr << '\n';
        // cout << pc[num] << endl;
        if(num > p) {
            // prefs[1] -= prev[0].second;
            prefs[1] -= pc[p][0].second;
            for(int i = 1; i < pc[p].size(); i++) {
                prefs[pc[p][i].first] += pc[p][i-1].second - pc[p][i].second;
            }

            // prefs[1] += curr[0].second;
            prefs[1] += pc[num][0].second;
            for(int i = 1; i < pc[num].size(); i++) {
                prefs[pc[num][i].first] += pc[num][i].second - pc[num][i-1].second;
            }

        }
        p = num;
    }

    for(int i = 1; i <= m; i++) {
        prefs[i] += prefs[i-1];
        cout << prefs[i] << " \n"[i == m];
    }

    return 0;
}