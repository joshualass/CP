#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
we want to work in reverse order and kind of gives highest probability to road with highest calculated probability. It will be calculated because the graph is a DAG.
One can see that it is optimal to select the road with the highest calculated probability first because we want to minimize the EV of the destroyed random road. 
We will always pick the best probability road, and that will have probability 1 / n, but what about other roads? If the operation misses, there will be n - 2 roads remaining, so 
we just look at the probabilities from 2 less. Looking at these probabilities could take a factor of n, for each element, but we can optimize by noticing that the position of each element will be in 
one of 2 positions for each of the random road destructions. We can compute these probabilities in linear time. We precompute these values. And use these values to easily solve the problem. 
*/

ld pc[5000][5000];

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vector<ld> p(n);

    p[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--) {
        vector<ld> probs;
        for(int to : adj[i]) {
            probs.push_back(p[to]);
        }
        sort(probs.begin(), probs.end());
        for(int j = 1; j <= probs.size(); j++) {
            p[i] += probs[j - 1] * pc[probs.size()][j];
        }
    }

    cout << p[0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 1; i < 5000; i++) {
        pc[i][i] = 1 / (ld) i;
        for(int j = 1; j < i; j++) {
            pc[i][j] = (pc[i - 2][j - 1] * (j - 1) + pc[i - 2][j] * (i - j - 1)) / i;
        }
    }

    cout << fixed << setprecision(20);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}