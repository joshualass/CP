#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int maxn = 100000;
const int sqrtn = sqrt(maxn + 1);

ll p[maxn + 1];
vector<ll> c[maxn + 1];
vector<int> atdepth[maxn + 1];
int nodedepth[maxn + 1];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void assign_depths(int i, int d) {
    cout << "i : " << i << " d : " << d << endl;
    nodedepth[i] = d;
    atdepth[d].push_back(i);
    cout << "c[i] : " << c[i] << endl;
    for(int child : c[i]) {
        assign_depths(child,d+1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("E.in","r",stdin);

    for(int i = 0; i <= maxn; i++) {
        // precalc[i].clear();
        // w[i] = -1;
        p[i] = -1;
        c[i].clear();
        atdepth[i].clear();
        nodedepth[i] = -1;
        // ids[i] = -1;
    }
    
    int n, q; cin >> n >> q;
    int trash;
    for(int i = 1; i <= n; i++) {
        cin >> trash;
    }

    for(int i = 2; i <= n; i++) {
        int num; cin >> num;
        c[num].push_back(i);
        p[i] = num;
    }

    assign_depths(1,0);

    cout << "ENDED" << endl;

    return 0;
}