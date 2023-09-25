#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<set<int>> v(n);
    vector<bool> unions(51);
    for(int i = 0; i < n; i++) {
        int N; cin >> N;
        for(int j = 0; j < N; j++) {
            int num; cin >> num;
            v[i].insert(num);
            unions[num] = true;
        }
    }
    size_t most = 0;
    for(int i = 1; i <= 50; i++) {
        if(unions[i]) {
            set<int> s;
            for(int j = 0; j < n; j++) {
                if(v[j].find(i) == v[j].end()) {
                    for(auto x : v[j]) s.insert(x);
                }
            }
            most = max(most,s.size());
        }
    }
    cout << most << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}