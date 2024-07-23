#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void findsizes(int i, int p, vector<vector<int>> &adj, vector<int> &mole, vector<int> &molesizes) {
    int cnt = mole[i];
    for(int c : adj[i]) {
        if(c != p) {
            findsizes(c,i,adj,mole,molesizes);
            cnt += molesizes[c];
        }
    }
    molesizes[i] = cnt;
}

int findbest(vector<int> &mole, vector<int> &molesizes) {
    int n = mole.size();
    int totalmoles = accumulate(mole.begin(), mole.end(), 0);
    int best = -1;
    int curr = INT_MAX;
    for(int i = 0; i < n; i++) {
        int trydiff = (totalmoles + 1) / 2 - molesizes[i];
        if(trydiff >= 0 && trydiff < curr) {
            best = i;
            curr = trydiff;
        }
    }

    return best;

}

void push(int i, int p, vector<vector<int>> &adj, vector<int> &mole) {

    if(p != -1) {
        mole[p] |= mole[i];
        mole[i] = 0;
    }

    for(int c : adj[i]) {
        if(c != p) {
            push(c,i,adj,mole);
        }
    }

}

void clearmole(int i, int p, int clearnode, int clearing, vector<vector<int>> &adj, vector<int> &mole) {
    // cout << "i : " << i << " clearnode : " << clearnode << '\n';
    if(i == clearnode) {
        clearing ^= 1;
    }
    // cout << "clr ? " << clearing << '\n';
    if(clearing) {
        mole[i] = 0;
    }
    for(int c : adj[i]) {
        if(c != p) {
            clearmole(c,i,clearnode,clearing,adj,mole);
        }
    }
}

void solve() {
    int n; cin >> n;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> mole(n,1);
    vector<int> molesizes(n);

    // cerr << "ok1" << endl;

    while(accumulate(mole.begin(), mole.end(), 0) != 1) {

        findsizes(0,-1,adj,mole,molesizes);

        // cerr << "ok2" << endl;
        // cout << "mole : " << mole << endl;
        // cout << "sizes : " << molesizes << endl;

        int queryidx = findbest(mole,molesizes);

        cout << "? " << queryidx + 1 << endl;
        int found; cin >> found;
        if(found) {
            clearmole(0,-1,queryidx,1,adj,mole);
        } else {
            clearmole(0,-1,queryidx,0,adj,mole);
        }
        // cout << "mole after clear : " << mole << endl;
        if(found == 0) {
            push(0,-1,adj,mole);
        }
        // cout << "mole after push : " << mole << endl;
    }

    for(int i = 0; i < n; i++) {
        if(mole[i]) {
            cout << "! " << i + 1 << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}