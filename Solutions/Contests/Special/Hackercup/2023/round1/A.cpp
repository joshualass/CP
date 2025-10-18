#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

double best(vector<int> &v) {
    double m1 = ((double)v[0] + v[1]) / 2.0;
    double m2 = ((double)v[v.size()-1] + v[v.size()-2]) /2.0;
    return m2 - m1;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    sort(v.begin(),v.end());
    if(v.size() == 5) {
        vector<int> copy = v;
        copy.erase(copy.begin() + 1);
        vector<int> copy2 = v;
        copy2.pop_back(); copy2.pop_back();
        copy2.push_back(copy.back());
        cout << max(best(copy),best(copy2)) << "\n";
    } else {
        cout << best(v) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("A.in","r",stdin);
    freopen("A.txt","w",stdout);
    cout << fixed << setprecision(2);
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}