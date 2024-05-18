#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<string,int>> a(n);
    ll sum = 0;
    for(auto &x : a) {
        cin >> x.first >> x.second;
        sum += x.second;
    }
    sort(a.begin(), a.end());

    cout << a[sum % n].first << '\n';

    return 0;
}