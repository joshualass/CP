#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, s, d; cin >> n >> m >> s >> d;

    vector<pair<int,int>> v(s);

    for(int i = 0; i < s; i++) {
        int num; cin >> num;
        v[i] = {num,i};
    }
    sort(v.begin(), v.end());
    vector<int> puts(s);
    int left = 0;
    for(int i = 0; i < s; i++) {
        int put = min(n,d - v[i].first);
        n -= put;
        puts[v[i].second] = put;
        // cout << "i : " << i << " put : " << put << " first : " << v[i].first << '\n';
        if(put == 0) {
            left += v[i].first;
        }
    }
    if(left >= m) {
        for(auto x : puts) cout << x << " ";
        cout << '\n';
    } else {
        cout << "impossible\n";
    }
    return 0;
}