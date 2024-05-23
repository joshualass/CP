// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// const int maxn = 100000;
// const int sqrtn = sqrt(maxn + 1);

// vector<vector<ll>> precalc[maxn + 1];
// ll w[maxn + 1];
// ll parents[maxn + 1];
// vector<ll> c[maxn + 1];
// vector<int> atdepth[maxn + 1];
// int nodedepth[maxn + 1];
// int ids[maxn + 1];

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void assign_depths(int i, int d) {
//     cout << "i : " << i << " d : " << d << endl;
//     nodedepth[i] = d;
//     atdepth[d].push_back(i);
//     // cout << "c[i] : " << c[i] << endl;
//     for(int child : c[i]) {
//         assign_depths(child,d+1);
//     }
//     // queue<pair<int,int>> q;
//     // q.push({i,d});
//     // while(q.size()) {
//     //     pair<int,int> p = q.front();
//     //     q.pop();
//     //     nodedepth[p.first] = p.second;
//     //     atdepth[p.second].push_back(p.first);
//     //     for(int child : c[p.first]) {
//     //         q.push({child,p.second + 1});
//     //     }
//     // }
// }

// ll query(int a, int b) {
//     // cout << "a : " << a << " b : " << b << endl;
//     stack<pair<int,int>> s1;
//     s1.push({a,b});
//     stack<pair<int,int>> s2;
//     ll res = 0;
//     for(int i = 0; i < 5'000'000; i++) {
//         i++;
//         i--;
//         i <<= 1;
//         i >>= 1;
//     }
//     while(s1.size()) {
//         pair<int,int> p = s1.top();
//         s1.pop();
//         a = p.first, b = p.second;
//         if(a > b) swap(a,b);
//         int currdepth = nodedepth[a];
//         if(precalc[currdepth][ids[a]][ids[b]] != -1) {
//             res = precalc[currdepth][ids[a]][ids[b]];
//             break;
//         }
//         s2.push({a,b});
//         if(a == 1) break;
//         s1.push({parents[a],parents[b]});
//     }

//     while(s2.size()) {
//         pair<int,int> p = s2.top();
//         s2.pop();
//         a = p.first, b = p.second;
//         if(a > b) swap(a,b);
//         int currdepth = nodedepth[a];
//         res += w[a] * w[b];
//         if(atdepth[currdepth].size() <= sqrtn) {
//             precalc[currdepth][ids[a]][ids[b]] = res;
//         }
//     }
//     return res;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     freopen("E.in","r",stdin);

//     for(int i = 0; i <= maxn; i++) {
//         precalc[i].clear();
//         w[i] = -1;
//         parents[i] = -1;
//         c[i].clear();
//         atdepth[i].clear();
//         nodedepth[i] = -1;
//         ids[i] = -1;
//     }
    
//     int n, q; cin >> n >> q;
//     for(int i = 1; i <= n; i++) {
//         cin >> w[i];
//     }

//     for(int i = 2; i <= n; i++) {
//         int num; cin >> num;
//         c[num].push_back(i);
//         parents[i] = num;
//     }

//     assign_depths(1,0);

//     for(int i = 0; i <= maxn; i++) {
//         for(int j = 0; j < atdepth[i].size(); j++) {
//             ids[atdepth[i][j]] = j;
//         }
//         if(atdepth[i].size() <= sqrtn) {
//             int sz = atdepth[i].size();
//             precalc[i].resize(sz);
//             for(int j = 0; j < sz; j++) {
//                 precalc[i][j].assign(sz,-1);
//             }
//         }
//     }

//     for(int i = 0; i < q; i++) {
//         int a, b; cin >> a >> b;
//         cout << query(a,b) << '\n';
//     }

//     cout << "ENDED" << endl;

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

map<ll,ll> m[100001];

ll dfs(int a, int b, vector<int> &parents, vector<ll> &w) {
    if(!a) return 0;
    if(m[a][b]) return m[a][b];
    return m[a][b] = dfs(parents[a],parents[b],parents,w) + w[a] * w[b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> parents(n+1);
    vector<ll> w(n+1);

    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for(int i = 2; i <= n; i++) {
        cin >> parents[i];
    }

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        ll res = 0;
        for(int i = 0; i < 1000 && a; i++) {
            res += w[a] * w[b];
            a = parents[a];
            b = parents[b];
        }
        cout << res + dfs(a,b,parents,w) << '\n';
    }

    return 0;
}