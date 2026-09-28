#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<int> scores(m);
    for(auto &x: scores) cin >> x;
    vector<pair<int,string>> v(n);
    int hi = -1;
    for(int i = 0; i < n; i++) {
        string str; cin >> str;
        int s = i + 1;
        for(int j = 0; j < m; j++) {
            if(str[j] == 'o') s += scores[j];
        }
        v[i] = {s,str};
        hi = max(hi,s);
    }
    for(int i = 0; i < n; i++) {
        int probs = 0;
        int score = v[i].first;
        while(score < hi) {
            probs++;
            int add = -1;
            int addidx = -1;
            for(int j = 0; j < n; j++) {
                if(v[i].second[j] == 'x' && scores[j] > add) {
                    add = scores[j];
                    addidx = j;
                }
            }
            score += add;
            v[i].second[addidx] = 'o';
        }
        cout << probs << "\n";
    }

    return 0;
}