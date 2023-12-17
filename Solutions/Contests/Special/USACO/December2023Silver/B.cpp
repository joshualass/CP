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
    
    int n, k; cin >> n >> k;

    set<int> incycle;
    map<int,int> cycleidxs;
    vector<int> cyclecnts1(k);
    vector<int> cyclecnts2(k);
    for(int i = 0; i < k; i++) {
        int a; cin >> a;
        a--;
        cycleidxs[a] = i;
        incycle.insert(a);
    }

    for(int i = 0; i < k; i++) {
        int b; cin >> b;
        b--;

        if(cycleidxs.find(b) != cycleidxs.end()) {
            int shift1 = k + i - cycleidxs[b];
            cyclecnts1[shift1 % k]++;
            
            int idx = k - 1 - cycleidxs[b];
            int shift2 = k + i - idx;
            cyclecnts2[shift2 % k]++;
        }

        incycle.insert(b);

    }

    // cout << "c1 : " << cyclecnts1 << '\n';
    // cout << "c2 : " << cyclecnts2 << '\n';

    int m1 = *max_element(cyclecnts1.begin(), cyclecnts1.end());
    int m2 = *max_element(cyclecnts2.begin(), cyclecnts2.end());

    cout << max(m1,m2) + (n - incycle.size()) << '\n';

    return 0;
}