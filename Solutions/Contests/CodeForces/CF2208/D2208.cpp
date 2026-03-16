#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int N = 8e3;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}


void solve() {
    
    int n; cin >> n;
    dsubuild(n);
    vector<pair<array<int,2>,string>> a(n);
    vector<vector<int>> subtrees(n);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        a[i] = {array<int,2>{(int) count(s.begin(), s.end(), '1'), i}, s};
        for(int j = 0; j < n; j++) {
            if(s[j] == '1') {
                subtrees[i].push_back(j);
            }
        }
    }

    vector<int> ok(n), pars(n, -1);
    vector<vector<int>> ch(n);

    sort(a.begin(), a.end());

    auto mark_bad = [&](auto self, int i) -> void {
        if(i == -1 || ok[i] == 0) return;
        ok[i] = 0;
        self(self, pars[i]);
    };

    int tree_ok = 1;

    for(int i = 0; i < n && tree_ok; i++) {
        int x = a[i].first[1];
        if(a[i].first[0] > 1) {
            for(int j = 0; j < i; j++) {
                ok[a[j].first[1]] = 1;
            }
            for(int j = 0; j < i; j++) {
                if(a[i].second[a[j].first[1]] == '0') mark_bad(mark_bad, a[j].first[1]);
            }
            for(int j = 0; j < i; j++) {
                if(ok[a[j].first[1]]) {
                    for(int c : ch[a[j].first[1]]) {
                        ok[c] = 0;
                    }
                }
            }
            for(int j = 0; j < i; j++) {
                if(ok[a[j].first[1]]) {
                    for(int c : subtrees[a[j].first[1]]) {
                        if(a[i].second[c] == '1') {
                            a[i].second[c] = '0';
                        } else {
                            tree_ok = 0;
                        }
                    }
                    if(find(x) != find(a[j].first[1])) {
                        merge(x, a[j].first[1]);
                        ch[x].push_back(a[j].first[1]);
                    } else {
                        tree_ok = 0;
                    }
                }
            }   
            if(count(a[i].second.begin(), a[i].second.end(), '1') != 1 || a[i].second[a[i].first[1]] != '1') {
                tree_ok = 0;
            }
        } 
    }

    if(sizes[find(0)] != n) tree_ok = 0;

    if(tree_ok) {
        cout << "Yes\n";
        for(int i = 0; i < n; i++) {
            for(int c : ch[i]) {
                cout << i + 1 << " " << c + 1 << '\n';
            }
        }
    } else {
        cout << "No\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}