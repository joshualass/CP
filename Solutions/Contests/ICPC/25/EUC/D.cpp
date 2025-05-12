#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<ld> vd;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

struct node {
    int c1 = -1, c2 = -1;   //{dot dash}
    int par = -1;
    ld p;
    node () {p = 0;}
    node(ld _p) {p = _p;}
    node(int _c1, int _c2, ld _p) {
        c1 = _c1;
        c2 = _c2;
        p = _p;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vd f(n);
    for(int i = 0; i < n; i++) cin >> f[i];
    vector<node> a(n);
    for(int i = 0; i < n; i++){
        a[i].p = f[i];
    }
    set<pair<ld, int>> s;   //{p, node index}
    for(int i = 0; i < n; i++){
        s.insert({a[i].p, i});
    }
    while(s.size() > 1){
        int find = s.begin()->second;
        ld fp = s.begin()->first;
        s.erase({fp, find});
        int sind;
        ld sp;
        if(s.lower_bound({fp, -1}) != s.end()) {
            sind = s.lower_bound({fp, -1})->second;
            sp = a[sind].p;
        }
        else {
            sind = s.rbegin()->second;
            sp = a[sind].p;
        }   
        // cout << "FP SP : " << find << " " << sind << " " << fp << " " << sp << "\n";
        s.erase({sp, sind});
        node x = node(sind, find, fp + sp);
        a[sind].par = a.size();
        a[find].par = a.size();
        s.insert({fp + sp, a.size()});
        a.push_back(x);
    }
    vector<string> ans(n);
    for(int i = 0; i < n; i++){
        int ptr = i;
        string str = "";
        while(ptr != a.size() - 1) {
            int nptr = a[ptr].par;
            if(a[nptr].c1 == ptr) str.push_back('.');
            else str.push_back('-');
            ptr = nptr;
        }
        reverse(str.begin(), str.end());
        ans[i] = str;
    }
    for(string &str : ans) cout << str << "\n";

    return 0;
}