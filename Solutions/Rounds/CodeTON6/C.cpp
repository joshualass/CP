#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    set<int> s;
    for(int i = 0; i < n; i++) {
        s.insert(i);
    }
    vector<pair<int,int>> v(0);
    vector<int> ans(k+1);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v.push_back({num,i});
    }
    sort(v.begin(),v.end());
    for(int i = 0; i < n; i++) {
        pair<int,int> p = v[i];
        int low = *s.begin();
        int high = *--s.end();
        // cout << "low: " << low << " high: " << high << "\n";
        ans[p.first] = max((high - low + 1) * 2,ans[p.first]);
        s.erase(p.second);
    }
    for(int i = 1; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}