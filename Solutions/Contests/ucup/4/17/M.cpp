#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
spent an extraneous amount of time trying to solve this problem on not the best sleep. 

sleep helps
otherwise, try making observations
formalizing things
defining things
doing better ._.
*/

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<class T> T edmondsKarp(vector<unordered_map<int, T>>&
		graph, int source, int sink) {
	assert(source != sink);
	T flow = 0;
	vi par(sz(graph)), q = par;

	for (;;) {
		fill(all(par), -1);
		par[source] = 0;
		int ptr = 1;
		q[0] = source;

		rep(i,0,ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) goto out;
				}
			}
		}
		return flow;
out:
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}

void solve() {
    
    int sober, drunk, m; cin >> sober >> drunk >> m;
    vector<vector<int>> p(2, vector<int>(m * 2 + 1));
    vector<array<int,2>> a;

    int f = 0;
    for(int i = 0; i < m; i++) {
        int t, s, fin; cin >> t >> s >> fin;
        t--; s--;
        p[t][s]++;
        p[t][fin]--;
        if(t == 0) {
            a.push_back({s, fin});
        }
    }

    vector<int> lb(m * 2), ub(m * 2);
    int cur = 0;
    for(int i = 0; i < m * 2; i++) {
        cur += p[0][i];
        lb[i] = max(0, cur - drunk);
    }
    cur = 0;
    int ok = 1;
    for(int i = 0; i < m * 2; i++) {
        cur += p[1][i];
        ub[i] = sober - cur;
        if(cur > sober) ok = 0;
        if(ub[i] < lb[i]) ok = 0;
    }

    // cout << "p2 : " << p[1] << endl;
    // cout << "lb : " << lb << endl;
    // cout << "ub : " << ub << endl;

    if(ok) {
        vector<unordered_map<int,int>> g(m * 2 + 3);
        int s = m * 2 + 1, t = m * 2 + 2;
        int f = sober;
        int tf = f;
        g[s][0] = f;
        g[m*2][t] = f;
        for(int i = 0; i < m * 2; i++) {
            int down = f - ub[i];
            int side = (f - lb[i]) - down;
            // cout << "i : " << i << " down : " << down << " side : " << side << endl;
            g[i][t] = down;
            g[s][i+1] = down;
            g[i][i+1] = side;
            tf += down;
        }
        for(auto [l, r] : a) g[l][r] += 1;
        int flow = edmondsKarp(g, s, t);
        // cout << "flow : " << flow << " tf : " << tf << endl;
        if(flow != tf) ok = 0;
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}