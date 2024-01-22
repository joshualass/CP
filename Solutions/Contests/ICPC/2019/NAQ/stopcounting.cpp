#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> v(n);

    for(int &x : v) cin >> x;

    vector<ld> suff(n);
    ld sum = 0;
    for(int i = n - 1; i >= 0; i--) {
        sum += v[i];
        if(i == n - 1) {
            suff[i] = max((ld)0,sum);
        } else {
            suff[i] = max(suff[i+1], sum / (n - i));
        }
    }

    ld ans = 0;
    sum = 0;
    vector<ld> pref(n);
    for(int i = 0; i < n; i++) {
        sum += v[i];
        if(i == 0) {
            pref[i] = max((ld)0,sum);
        } else {
            pref[i] = max(pref[i-1], sum / (i + 1));
        }
    }
    // cout << "prefs : " << pref << '\n';
    // cout << "suffs : " << suff << '\n';
    cout << fixed << setprecision(15) << max(suff.front(), pref.back()) << '\n';


    return 0;
}