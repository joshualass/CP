#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int maxn = 100000;
const int sqrtn = sqrt(maxn);

ll w[maxn + 1];
ll parents[maxn + 1];
int nodedepth[maxn + 1];
int ids[maxn + 1];
vector<ll> c[maxn + 1];
vector<int> atdepth[maxn + 1];
vector<vector<ll>> precalc[maxn + 1];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void assign_depths(int i, int d) {
    queue<pair<int,int>> q;
    q.push({i,d});
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        nodedepth[p.first] = p.second;
        atdepth[p.second].push_back(p.first);
        for(int child : c[p.first]) {
            q.push({child,p.second + 1});
        }
    }
}

ll query(int a, int b) {
    stack<pair<int,int>> s2;
    ll res = 0;
    while(1) {
        if(a > b) swap(a,b);
        int currdepth = nodedepth[a];
        if(atdepth[currdepth].size() <= sqrtn && precalc[currdepth][ids[a]][ids[b]] != -1) {
            res = precalc[currdepth][ids[a]][ids[b]];
            break;
        }
        s2.push({a,b});
        if(a == 1) break;
        a = parents[a], b = parents[b];
    }
    
    while(s2.size()) {
        pair<int,int> p = s2.top();
        s2.pop();
        a = p.first, b = p.second;
        if(a > b) swap(a,b);
        int currdepth = nodedepth[a];
        res += w[a] * w[b];
        if(atdepth[currdepth].size() <= sqrtn) {
            precalc[currdepth][ids[a]][ids[b]] = res;
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for(int i = 2; i <= n; i++) {
        int num; cin >> num;
        c[num].push_back(i);
        parents[i] = num;
    }

    assign_depths(1,0);

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < atdepth[i].size(); j++) {
            ids[atdepth[i][j]] = j;
        }
        if(atdepth[i].size() <= sqrtn) {
            int sz = atdepth[i].size();
            precalc[i].resize(sz);
            for(int j = 0; j < sz; j++) {
                precalc[i][j].assign(sz,-1);
            }
        }
    }

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << query(a,b) << '\n';
    }

    return 0;
}